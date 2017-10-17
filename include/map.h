/**
 * @file Map.h
 * @author Jessica Howard
 * @copyright GNU public license
 *
 * @brief Header file for Map.cpp, an implementation of a simple grid map with
 * obstacles
 *
 * @section DESCRIPTION
 * This is the header file for an implementation of a simple grid map with
 * obstacles. It is always rectangular in size, specified either at creation or
 * later using the setSize method.
 *
 * It has a dependent class, Obstacle.
 */

#ifndef APP_MAP_H_
#define APP_MAP_H_

#include "obstacle.h"
#include "vertex.h"
#include <list>

class Map {
 private:
  /**
   * @brief size of the grid
   * @param height height of grid
   * @param width width of grid
   */
  std::pair<int,int> size_;

  /**
   * @brief the list of obstacles within the map. Obstacles can overlap
   */
  std::list<Obstacle> obstacle_list_;


 public:
  /**
   * @brief generic constructor for a map object
   * @detail creates a 10x10 map with no obstacles
   */
  Map();

  /**
   * @brief constructor for a map object
   * @param height height of the map
   * @param width width of the map
   * @param obstacleList list of Obstacle objects within the map
   */
  Map(int, int, std::list<Obstacle>);


  /**
   * @brief Add a new obstacle to the map
   * @details Adds a new obstacle to the map by adding it to the back of the
   * obstacleList. The list is then sorted and any duplicate obstacles are
   * removed.
   * @param obs the Obstacle to be added
   */
  void add_obstacle(Obstacle);

  /**
   * @brief Removes an obstacle from the map
   * @details Removes an obstacle from the obstacleList of the map. If the
   * obstacle does not exist nothing happens.
   * @param obs the obstacle to be removed
   */
  void remove_obstacle(Obstacle);

  /**
   * @brief Gets the size of the map
   * @details Returns the size of the map as a std::pair<int,int>. The first
   * of the pair is the height, the second is the width
   * @return size of the map
   */
  std::pair<int,int> get_size();

  /**
   * @brief returns the list of obstacles in the map
   * @return list of obstacles
   */
  std::list<Obstacle> get_obstacle_list();
};

#endif /* APP_MAP_H_ */
