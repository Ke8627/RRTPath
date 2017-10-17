/**
 * @file Obstacle.cpp
 * @author Jessica Howard
 * @copyright GNU public license
 *
 * @brief Simple obstacle class for use with Map
 *
 * @section DESCRIPTION
 * The Obstacle class is intended for use with the Map class. An Obstacle
 * is defined by it's location in x,y coordinates and the size of the obstacle.
 * Obstacles are square since the map is laid out on a simple integer grid. The
 * "size" of the obstacle is the radius, the distance from the x,y location to
 * the nearest edge of the obstacle.
 */

#include "obstacle.h"

Obstacle::Obstacle(int x_location, int y_location, int size) {
  Obstacle::location_.first = x_location;
  Obstacle::location_.second = y_location;
  Obstacle::obstacle_radius_ = size;
}

std::pair<int, int> Obstacle::get_location() {
  return Obstacle::location_;
}

int Obstacle::get_size() {
  return Obstacle::obstacle_radius_;
}
