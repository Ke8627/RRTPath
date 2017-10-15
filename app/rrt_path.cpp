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
#include <random>

RRTPath::RRTPath(Map map, int startXLocation, int startYLocation,
                 int goalXLocation, int goalYLocation, int epsilon, int delta,
                 int goalRadius) {
  RRTPath::map = map;
  RRTPath::startLocation.first = startXLocation;
  RRTPath::startLocation.second = startYLocation;
  RRTPath::goalLocation.first = goalXLocation;
  RRTPath::goalLocation.second = goalYLocation;
  RRTPath::epsilon = epsilon;
  RRTPath::delta = delta;
  RRTPath::goalRadius = goalRadius;

  Vertex *rootNode = new Vertex(startXLocation, startYLocation, nullptr);

  RRTPath::root = rootNode;

  RRTPath::vertexList.push_back(RRTPath::root);
}

std::pair<int, int> RRTPath::getRandomPoint() {
  std::pair<int, int> randomPoint;

  //Get the size of the map so we know our bounds
  std::pair<int, int> mapSize = RRTPath::map.getSize();

  //Get a random point within the bounds of our map
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> x_random(0,randomPoint.first);
  std::uniform_int_distribution<> y_random(0,randomPoint.second);


  randomPoint.first = x_random(gen);
  randomPoint.second = y_random(gen);

  //Return the random point
  return randomPoint;
}

Vertex RRTPath::getClosestPoint(std::pair<int, int> randomPoint) {
  /**
   * TODO
   *    1. find closest vertex to random point and return it
   */
  return Vertex(0, 0, nullptr);
}

bool RRTPath::moveTowardsPoint(Vertex closestVertex,
                               std::pair<int, int> randomPoint) {
  /**
   * TODO
   *    1. move epsilon distance from vertex towards random point
   *    2. check if path between vertex and the new point is safe
   *    3. if safe, create new vertex with previous vertex as prevVertex
   *       and add to vertexList
   *    4. check if new vertex is within goalRadius of goal
   *       4a. if so, call calculatePath to rebuild the path back to the root
   *           and then draw the map
   *       4b. if not, generate a new random point and begin again
   */
  return false;
}

bool RRTPath::reachedGoal(Vertex newVertex) {
  /**
   * TODO
   *    Check if newVertex is within goalRadius of goal
   */
  return false;
}

std::list<std::pair<int, int> > RRTPath::calculatePath(Vertex goal) {
  /**
   * TODO
   *    1. add prevVertex to front of list
   *    2. repeat until we reach the root vertex, designated by having a
   *       nullptr instead of a prevVertex
   */
  std::list<std::pair<int, int>> path;
  path.push_back(goal.getLocation());
  return path;
}

void RRTPath::drawMap() {
  /**
   * TODO
   *    use matplotlib to draw a 2D graph of the map and obstacles, the RRT,
   *    and the path taken from start to goal
   */

}
