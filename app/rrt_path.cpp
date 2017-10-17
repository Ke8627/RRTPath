/**
 * @file RRTPath.cpp
 * @author Jessica Howard
 * @copyright GNU public license
 *
 * @brief Implementation of RRT path planning algorithm
 *
 * @section DESCRIPTION
 * The RRTPath class generates a path between a given starting point and a
 * goal point while avoiding obstacles. Class dependencies are the Vertex
 * class, and the Map class, which has a dependency of the Obstacle class.
 * This class only generates the first path it finds, which may not be the
 * most efficient.
 */

#include "rrt_path.h"
#include <random>   //needed for random point generation
#include <cmath>    //needed for finding closest point
#include <iostream>

RRTPath::RRTPath(Map map, int startXLocation, int startYLocation,
                 int goalXLocation, int goalYLocation, int epsilon,
                 int goalRadius) {
  RRTPath::map = map;
  RRTPath::startLocation.first = startXLocation;
  RRTPath::startLocation.second = startYLocation;
  RRTPath::goalLocation.first = goalXLocation;
  RRTPath::goalLocation.second = goalYLocation;
  RRTPath::epsilon = epsilon;
  RRTPath::goalRadius = goalRadius;

  Vertex *rootNode = new Vertex(startXLocation, startYLocation, nullptr);

  RRTPath::root = rootNode;

  RRTPath::vertexList.push_back(RRTPath::root);

}

std::list<std::pair<int,int>> RRTPath::findPath() {
  bool reachedGoal = true;
  while (!reachedGoal) {
    //First we get a random point within the map
    std::pair<int, int> randomPoint = RRTPath::getRandomPoint();

    //Next we find the closest vertex to that random point
    Vertex *closestVertex = RRTPath::getClosestPoint(randomPoint);

    //Then we try to make a move towards that point
    if (RRTPath::moveTowardsPoint(closestVertex, randomPoint)) {
      //Check if we've reached our goal
      Vertex *newVertex = RRTPath::vertexList.front();
      reachedGoal = RRTPath::reachedGoal(newVertex->getLocation());
    }
  } //end while loop

  //Rebuild our path and return
  RRTPath::overallPath = calculatePath(RRTPath::vertexList.front());
  return RRTPath::overallPath;
}

std::pair<int, int> RRTPath::getRandomPoint() {
  std::pair<int, int> randomPoint;

  //Get the size of the map so we know our bounds
  std::pair<int, int> mapSize = RRTPath::map.getSize();

  //Get a random point within the bounds of our map
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> x_random(0,mapSize.first);
  std::uniform_int_distribution<> y_random(0,mapSize.second);

  //Generate the random point
  randomPoint.first = x_random(gen);
  randomPoint.second = y_random(gen);

  //Return the random point
  return randomPoint;
}

Vertex* RRTPath::getClosestPoint(std::pair<int, int> randomPoint) {
  /**
   * TODO
   *    1. find closest vertex to random point and return it
   */
  Vertex* closest = RRTPath::root;
  float closestDistance = INFINITY;
  float currentDistance = INFINITY;

  std::list<Vertex*>::iterator it;
  for (it = RRTPath::vertexList.begin(); it != RRTPath::vertexList.end(); it++) {
    currentDistance = RRTPath::getDistance((*it)->getLocation(), randomPoint);
    if (currentDistance < closestDistance) {
      closest = *it;
      closestDistance = currentDistance;
    }
  }

  return closest;
}

float RRTPath::getDistance(std::pair<int, int> startPoint,
                           std::pair<int, int> endPoint) {
  int x1 = startPoint.first;
  int x2 = endPoint.first;
  int y1 = startPoint.second;
  int y2 = endPoint.second;
  float distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  return distance;
}

bool RRTPath::moveTowardsPoint(Vertex* closestVertex,
                               std::pair<int, int> randomPoint) {
  //Move epsilon distance from our closest point towards our random point
  std::pair<int, int> closestPoint = closestVertex->getLocation();
  float theta = atan2(randomPoint.second-closestPoint.second,
                      randomPoint.first-closestPoint.first);
  float newX = closestPoint.first + RRTPath::epsilon * cos(theta);
  float newY = closestPoint.second + RRTPath::epsilon * sin(theta);
  //Cast from float to int, should automatically round down which is what we
  //want
  std::pair<int, int> newPoint(static_cast<int>(newX), static_cast<int>(newY));

  //Check if the new path is safe
  if (RRTPath::isSafe(closestPoint, newPoint)) {
    Vertex *newVertex = new Vertex(newPoint.first, newPoint.second,
                                   closestVertex);
    RRTPath::vertexList.push_front(newVertex);
    return true;
  }
  return false;
}

bool RRTPath::reachedGoal(std::pair<int, int> newVertex) {
  //Check to see if our new vertex is within the designated radius of the goal
  float distance = RRTPath::getDistance(newVertex, RRTPath::goalLocation);
  if (distance <= RRTPath::goalRadius)
    return true;
  else
    return false;
}

std::list<std::pair<int, int> > RRTPath::calculatePath(Vertex* goal) {
  //Create an empty list for the path
  std::list<std::pair<int, int>> path;

  //Set our current vertex to our end point vertex (goal)
  Vertex *current = goal;

  //So long as our current vertex's parent isn't the nullptr (indicating the
  //root node) add the location to the beginning of the list, then set the
  //current vertex to be the parent
  while (current->getParent() != nullptr) {
    path.push_front(current->getLocation());
    current = current->getParent();
  }

  //Add the root node's location to the front of the list
  path.push_front(root->getLocation());
  return path;
}

bool RRTPath::isSafe(std::pair<int, int> startPoint,
                     std::pair<int, int> endPoint) {
  //Check to make sure our endpoint is within bounds of the map
  if (endPoint.first < 0 || endPoint.first > RRTPath::map.getSize().first ||
      endPoint.second < 0 || endPoint.second > RRTPath::map.getSize().second)
    return false;

  //Check to make sure endpoint isn't inside of an obstacle
  std::list<Obstacle> obstacles = RRTPath::map.getObstacleList();
  std::list<Obstacle>::iterator it;
  for (it = obstacles.begin(); it != obstacles.end(); it++) {
    if (RRTPath::getDistance(endPoint, it->getLocation()) < it->getSize())
      return false;
  }

  //Check the path at intervals for a total distance of epsilon for collisions
  float theta = atan2(endPoint.second - startPoint.second,
                      endPoint.first - startPoint.first);
  float currentX = startPoint.first;
  float currentY = startPoint.second;
  float step = static_cast<float>(epsilon)/10;
  //Move towards our next increment
  for (int i = 0; i < 10; i++) {
    currentX += step*cos(theta);
    currentY += step*sin(theta);
    //Check the next step for obstacles
    for (it = obstacles.begin(); it != obstacles.end(); it++) {
      if (RRTPath::getDistance(std::pair<int, int>(static_cast<int>(currentX),
                                                   static_cast<int>(currentY)),
                               it->getLocation()) < it->getSize())
        return false;
    }
  }

  return true;
}

void RRTPath::drawMap() {
  /**
   * TODO
   *    use matplotlib to draw a 2D graph of the map and obstacles, the RRT,
   *    and the path taken from start to goal
   */

}
