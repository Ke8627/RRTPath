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

RRTPath::RRTPath(Map map, int start_x, int start_y,
                 int goal_x, int goal_y, int epsilon,
                 int radius) {
  RRTPath::map_ = map;
  RRTPath::start_location_.first = start_x;
  RRTPath::start_location_.second = start_y;
  RRTPath::goal_location_.first = goal_x;
  RRTPath::goal_location_.second = goal_y;
  RRTPath::epsilon_ = epsilon;
  RRTPath::goal_radius_ = radius;

  Vertex *root_node = new Vertex(start_x, start_y, nullptr);

  RRTPath::root_node_ = root_node;

  RRTPath::vertex_list_.push_back(RRTPath::root_node_);

}

std::list<std::pair<int,int>> RRTPath::FindPath() {
  bool goal_reached = false;
  while (!goal_reached) {
    //First we get a random point within the map
    std::pair<int, int> random_point = RRTPath::GetRandomPoint();

    //Next we find the closest vertex to that random point
    Vertex *closest_vertex = RRTPath::GetClosestPoint(random_point);

    //Then we try to make a move towards that point
    if (RRTPath::MoveTowardsPoint(closest_vertex, random_point)) {
      //Check if we've reached our goal
      Vertex *new_vertex = RRTPath::vertex_list_.front();
      goal_reached = RRTPath::ReachedGoal(new_vertex->get_location());
    }
  } //end while loop

  //Rebuild our path and return
  RRTPath::overall_path_ = CalculatePath(RRTPath::vertex_list_.front());
  return RRTPath::overall_path_;
}

std::pair<int, int> RRTPath::GetRandomPoint() {
  std::pair<int, int> random_point;

  //Get the size of the map so we know our bounds
  std::pair<int, int> map_size = RRTPath::map_.GetSize();

  //Get a random point within the bounds of our map
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> x_random(0,map_size.first);
  std::uniform_int_distribution<> y_random(0,map_size.second);

  //Generate the random point
  random_point.first = x_random(gen);
  random_point.second = y_random(gen);

  //Return the random point
  return random_point;
}

Vertex* RRTPath::GetClosestPoint(std::pair<int, int> random_point) {
  //Set our closest vertex to our root, since we know it exists
  Vertex* closest = RRTPath::root_node_;

  //closest distance will keep track of the closest distance we find
  float closest_distance = INFINITY;
  //current distance will keep track of the distance of our current vertex
  float current_distance = INFINITY;

  //iterate through our vertex list to find the closest
  std::list<Vertex*>::iterator it;
  for (it = RRTPath::vertex_list_.begin(); it != RRTPath::vertex_list_.end();
      ++it) {
    //get the distance between our current vertex (it) and the random point
    current_distance = RRTPath::GetDistance((*it)->get_location(),
                                             random_point);
    //if the current distance is closer than what we have saved as closest
    //save the current node and update the closest distance
    if (current_distance < closest_distance) {
      closest = *it;
      closest_distance = current_distance;
    }
  }

  return closest;
}

float RRTPath::GetDistance(std::pair<int, int> start_point,
                            std::pair<int, int> end_point) {
  //x,y coords for our starting point
  int x1 = start_point.first;
  int y1 = start_point.second;

  //x,y coords for our ending point
  int x2 = end_point.first;
  int y2 = end_point.second;

  //euclidean distance formula
  float distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  return distance;
}

bool RRTPath::MoveTowardsPoint(Vertex* closest_vertex,
                                 std::pair<int, int> random_point) {
  //Move epsilon distance from our closest point towards our random point
  std::pair<int, int> closest_point = closest_vertex->get_location();
  float theta = atan2(random_point.second-closest_point.second,
                      random_point.first-closest_point.first);
  float newX = closest_point.first + RRTPath::epsilon_ * cos(theta);
  float newY = closest_point.second + RRTPath::epsilon_ * sin(theta);
  //Cast from float to int, should automatically round down which is what we
  //want
  std::pair<int, int> new_point(static_cast<int>(newX), static_cast<int>(newY));

  //Check if the new path is safe
  if (RRTPath::IsSafe(closest_point, new_point)) {
    Vertex *new_vertex = new Vertex(new_point.first, new_point.second,
                                   closest_vertex);
    RRTPath::vertex_list_.push_front(new_vertex);
    return true;
  }
  return false;
}

bool RRTPath::ReachedGoal(std::pair<int, int> new_vertex) {
  //Check to see if our new vertex is within the designated radius of the goal
  float distance = RRTPath::GetDistance(new_vertex, RRTPath::goal_location_);
  if (distance <= RRTPath::goal_radius_)
    return true;
  return false;
}

std::list<std::pair<int, int> > RRTPath::CalculatePath(Vertex* goal) {
  //Create an empty list for the path
  std::list<std::pair<int, int>> path;

  //Set our current vertex to our end point vertex (goal)
  Vertex *current = goal;

  //So long as our current vertex's parent isn't the nullptr (indicating the
  //root node) add the location to the beginning of the list, then set the
  //current vertex to be the parent
  while (current->get_parent() != nullptr) {
    path.push_front(current->get_location());
    current = current->get_parent();
  }

  //Add the root node's location to the front of the list
  path.push_front(root_node_->get_location());
  return path;
}

bool RRTPath::IsSafe(std::pair<int, int> start_point,
                      std::pair<int, int> end_point) {
  //Check to make sure our endpoint is within bounds of the map
  if (end_point.first < 0 || end_point.first > RRTPath::map_.GetSize().first ||
      end_point.second < 0 || end_point.second > RRTPath::map_.GetSize().second)
    return false;

  //Check to make sure endpoint isn't inside of an obstacle
  std::list<Obstacle> obstacles = RRTPath::map_.GetObstacleList();
  for (Obstacle o : obstacles) {
    if (RRTPath::GetDistance(end_point, o.GetLocation()) < o.GetSize())
      return false;
  }

  //Check the path at intervals for a total distance of epsilon for collisions
  float theta = atan2(end_point.second - start_point.second,
                      end_point.first - start_point.first);
  float current_x = start_point.first;
  float current_y = start_point.second;
  float step = static_cast<float>(epsilon_)/10;
  //Move towards our next increment
  for (int i = 0; i < 10; i++) {
    current_x += step*cos(theta);
    current_y += step*sin(theta);
    //Check the next step for obstacles

    for (Obstacle o : obstacles) {
      if (RRTPath::GetDistance(std::pair<int, int>(static_cast<int>(current_x),
                                                    static_cast<int>(current_y)),
                                o.GetLocation()) < o.GetSize())
        return false;
    }
  }

  return true;
}
