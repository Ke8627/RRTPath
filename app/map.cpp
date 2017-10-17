/**
 * @file Map.cpp
 * @author Jessica Howard
 * @copyright GNU public license
 *
 * @brief Class implementation of a simple grid map with obstacles
 *
 * @section DESCRIPTION
 * This is the implementation of a simple grid map with obstacles. It is
 * always rectangular in size, specified either at creation or later using the
 * setSize method.
 *
 * It has a dependent class, Obstacle.
 */

#include "map.h"

Map::Map() {
  Map::size_.first = 10;
  Map::size_.second = 10;
}

Map::Map(int height, int width, std::list<Obstacle> obstacle_list) {
  Map::size_.first = height;
  Map::size_.second = width;
  Map::obstacle_list_ = obstacle_list;
}

void Map::AddObstacle(Obstacle obs) {
  obstacle_list_.push_back(obs);
  obstacle_list_.sort();
  obstacle_list_.unique();
}

void Map::RemoveObstacle(Obstacle obs) {
  obstacle_list_.remove(obs);
}

std::pair<int, int> Map::GetSize() {
  return size_;
}

std::list<Obstacle> Map::GetObstacleList() {
  return obstacle_list_;
}
