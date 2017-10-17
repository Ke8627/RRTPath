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
#include <math.h>
#include <vertex.h>

Vertex::Vertex(int x_start, int y_start, Vertex* parent_vertex) {
  Vertex::x_ = x_start;
  Vertex::y_ = y_start;
  Vertex::parent_ = parent_vertex;
}

std::pair<int, int> Vertex::get_location() {
  std::pair<int, int> location(Vertex::x_, Vertex::y_);
  return location;
}

Vertex* Vertex::get_parent() {
  return parent_;
}
