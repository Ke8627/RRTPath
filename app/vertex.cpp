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

Vertex::Vertex(int xStart, int yStart, Vertex* prevVertex) {
  Vertex::x = xStart;
  Vertex::y = yStart;
  Vertex::parent = prevVertex;
}

std::pair<int, int> Vertex::getLocation() {
  std::pair<int, int> location(Vertex::x, Vertex::y);
  return location;
}

Vertex* Vertex::getParent() {
  return parent;
}
