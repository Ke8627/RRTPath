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
  Map::size.first = 10;
  Map::size.second = 10;
}

Map::Map(int height, int width, std::list<Obstacle> obstacleList) {
  Map::size.first = height;
  Map::size.second = width;
  Map::obstacleList = obstacleList;
}

void Map::addObstacle(Obstacle obs) {
  obstacleList.push_back(obs);
  obstacleList.sort();
  obstacleList.unique();
}

void Map::removeObstacle(Obstacle obs) {
  obstacleList.remove(obs);
}

std::pair<int, int> Map::getSize() {
  return size;
}

std::list<Obstacle> Map::getObstacleList() {
  return obstacleList;
}
