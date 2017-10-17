/**
 * @file Obstacle.h
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

#ifndef APP_OBSTACLE_H_
#define APP_OBSTACLE_H_

#include <utility>

class Obstacle {
 private:
  /**
   * @brief the location of the obstacle
   * @details a std::pair<int,int> designating the location of the obstacle.
   * The first of the pair is the x location, the second is the y location
   */
  std::pair<int,int> location;

  /**
   * @brief the size of the obstacle
   * @details the radius of the square obstacle
   */
  int size;


 public:
  /**
   * @brief constructor for the Obstacle class
   * @details Creates an Obstacle object to be used with the Map class. An
   * Obstacle consists of a location on the Map and the size of the obstacle.
   * The first argument is the x location of the center of the obstacle. The
   * second argument is the y location of the center of the obstacle. The size
   * is the radius of the obstacle. Obstacles are square.
   * @param xLocation int value of the x location of the center of the obstacle
   * @param yLocation int value of the y location of the center of the obstacle
   * @param size the radius of the obstacle
   */
  Obstacle(int, int, int);

  /**
   * @brief gets the location of an Obstacle
   * @return a std::pair<xLocation:int, yLocation:int>
   */
  std::pair<int,int> get_location();

  /**
   * @brief gets the size of an Obstacle
   * @return returns the radius of the obstacle
   */
  int get_size();

  /**
   * @brief overload of < operator
   */
  inline bool operator < (const Obstacle& o) const {
    return size < o.size;
  }

  /**
   * @brief overload of > operator
   */
  inline bool operator > (const Obstacle& o) const {
    return o.size < size;
  }

  /**
   * @brief overload of == operator
   */
  inline bool operator == (const Obstacle& o) const {
    return (location.first == o.location.first &&
        location.second == o.location.second &&
        size == o.size);
  }

  /**
   * @brief overload of != operator
   */
  inline bool operator != (const Obstacle& o) const {
    return (location.first != o.location.first ||
        location.second != o.location.second ||
        size != o.size);
  }
};

#endif /* APP_OBSTACLE_H_ */
