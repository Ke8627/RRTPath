/**
 * @file RRTPath.h
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

#ifndef APP_RRTPATH_H_
#define APP_RRTPATH_H_

#include <map.h>
#include <vertex.h>

class RRTPath {
 private:
  /**
   * @brief the starting location of the path from start to goal
   * @return a pair indicating the starting location of the path as
   * std::pair<startXLocation:int, startYLocation:int>
   */
  std::pair<int,int> startLocation;

  /**
   * @brief the location of the goal
   * @return a pair indicating the goal location of the path as
   * std::pair<goalXLocation:int, goalYLocation:int>
   */
  std::pair<int,int> goalLocation;

  /**
   * @brief The radius of the goal
   * @details How close to the goal is close enough to count
   */
  int goalRadius;

  /**
   * @brief the distance moved each step during mapping
   */
  int epsilon;

  /**
   * @brief a subsampling distance to be used to determine path safety
   * @detail A distance less than epsilon that will be used to sample the
   * proposed path between a vertex and a new point to be sure that no
   * collisions occur.
   */
  int delta;

  /**
   * @brief the Map object we are navigating
   */
  Map map;

  /**
   * @brief The root vertex of our tree
   * @detail This vertex holds the starting location of our path. The previous
   * vertex has a value of zero, to let us know we've reached the beginning
   * when we are reconstructing the path
   */
  Vertex *root;

  /**
   * @brief a list of x,y coordinates indicating the path from start to goal
   */
  std::list<std::pair<int,int>> overallPath;

  /**
   * @brief a list of all the vertices in the map
   */
  std::list<Vertex*> vertexList;

  /**
   * @brief returns a random location on the map
   * @return a random location as a std::pair<xCoord:int, yCoord:int>
   */
  std::pair<int,int> getRandomPoint();

  /**
   * @brief returns the closest Vertex to the given point
   * @detail Calculates the Euclidean distance between the given point and
   * all Vertices to determine which Vertex is the closest.
   * @param randomPoint the point you want to find the nearest vertex to
   * @return the nearest Vertex to the given point
   */
  Vertex getClosestPoint(std::pair<int,int>);

  /**
   * @brief Expands the RRT between the Vertex and the given point
   * @detail Move epsilon distance from closestVertex towards the given point.
   * Make a call to Map::isSafe to make sure that the path between the vertex
   * and the point does not cause any collisions with obstacles. If the path
   * is safe create a new vertex with the point that is epsilon distance away
   * from the previous vertex, list the previous vertex as the new vertex's
   * parent, and push the new vertex to the vertexList. Check to see if the
   * new vertex has reached the goal. If so, calculate the path. If not,
   * generate a new random location and repeat.
   * @param closestVertex The starting point of our expansion
   * @param randomPoint The point we are moving towards
   * @return true if the expansion was made, false if a collision would have
   * occurred
   */
  bool moveTowardsPoint(Vertex, std::pair<int,int>);

  /**
   * @brief determines if we have reached the goal
   * @detail Determines if a newly discovered Vertex is within
   * RRTPath::goalRadius of the goal.
   * @return true if within goalRadius of goal, false otherwise
   */
  bool reachedGoal(Vertex);

  /**
   * @brief the path between the start and goal
   * @detail a std::list of std::pairs of the x,y coordinates of the vertices
   * traveled to get between the starting point and the ending point. This
   * function is called once the reachedGoal call returns true. The parameter
   * vertex, goal, added to the list. Goals' prevVertex location is then
   * pushed to the front of the list, continued on until we reach the root
   * vertex, which will be designated by having a 0 instead of a Vertex in
   * the prevVertex.
   */
  std::list<std::pair<int,int>> calculatePath(Vertex);



 public:
  /**
   * @brief Constructor for RRTPath
   * @param map the Map object that we will be traversing
   * @param startXLocation the beginning x coordinate of the map
   * @param startYLocation the beginning y coordinate of the map
   * @param goalXLocation the x coordinate of the goal
   * @param goalYLocation the y coordinate of the goal
   * @param epsilon the distance the RRT expands when discovering a new point
   * @param delta a subsampling distance to determine if a collision occurs
   * @param goalRadius how close to the goal is close enough
   */
  RRTPath(Map, int, int, int, int, int, int, int);

  /**
   * @brief runs the rrt algorithm and finds the path
   * @detail The behavior is as described in the included activity diagram.
   * Until we reach our goal we continue to generate random points, locate
   * their closest vertex and draw new, safe paths.
   * @return returns the path as a std::list<std::pair<x, y>>
   */
  std::list<std::pair<int,int>> run();


  /**
   * @brief Draws a visual diagram of the RRT
   * @detail a 2D drawing of the map and obstacles, the RRT, and the path
   * taken from the start to the goal using matplotlibcpp.
   */
  void drawMap();
};

#endif /* APP_RRTPATH_H_ */
