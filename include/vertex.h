/**
 * @file Vertex.cpp
 * @author Jessica Howard
 * @copyright GNU public license
 *
 * @brief A Vertex class
 *
 * @section DESCRIPTION
 * The Vertex class is a dependency for RRTPath. It specifies a location
 * on the RRTPath's map and the vertex that came before it.
 */

#ifndef APP_VERTEX_H_
#define APP_VERTEX_H_

#include <utility>
#include <list>

class Vertex {
 private:
  /**
   * @brief the x coordinate of the vertex
   */
  int x_;

  /**
   * @brief the y coordinate of the vertex
   */
  int y_;

  /**
   * @brief the vertex that came before this one
   */
  Vertex* parent_;



 public:
  /**
   * @brief constructor for a Vertex
   * @param x x coordinate of vertex
   * @param y y coordinate of vertex
   * @param prevVertex location of the vertex that led to this one, nullptr
   * if root
   */
  Vertex(int, int, Vertex*);

  /**
   * @brief gets location of vertex
   * @return returns std::pair<x,y>
   */
  std::pair<int,int> get_location();

  /**
   * @brief gets the previous vertex
   * @return the parent vertex
   */
  Vertex* get_parent();

  /**
   * @brief overload of == operator
   */
  bool operator==(const Vertex& v) {
    return (x_ == v.x_ &&
        y_ == v.y_ &&
        parent_ == v.parent_);
  }

  /**
   * @brief overload of != operator
   */
  bool operator!=(const Vertex&v) {
    return (x_ != v.x_ ||
        y_ != v.y_ ||
        parent_ != v.parent_);
  }
};

#endif /* APP_VERTEX_H_ */
