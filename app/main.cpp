/**
 * @file main.cpp
 * @author Jessica Howard
 * @copyright GNU public license
 *
 * @brief Demo of RRT path planning algorithm
 *
 * @section DESCRIPTION
 * This is a demo of the RRT path planning algorithm. To customize it you may
 * set any of the variables in the customizable variables section at the top.
 * map_height: The height of your rectangular map
 * map_width: The width of your rectangular map
 * start_x: the x coordinate of where you want your path to begin
 * start_y: the y coordinate of where you want your path to begin
 * goal_x: the x coordinate of your goal location
 * goal_y: the y coordinate of your goal location
 * step: how far you travel at each algorithm iteration. Smaller steps
 *      have more detail and may create a more efficient path, but take longer
 *      to run.
 * radius: how near you need to be to the goal to "reach" it
 *
 * Obstacles may be added to the map in the create obstacles here section.
 * Simply create your obstacle(s) and then add them to the map as shown.
 *
 * Your path is printed to the console at the conclusion of the demo.
 */

#include <iostream>
#include "rrt_path.h"

int main()
{
  /*********************** Customizable variables here ***********************/
  int map_width = 15;       //Width of map
  int map_height = 15;      //Height of map
  int start_x = 0;          //Path beginning x location
  int start_y = 0;          //Path beginning y location
  int goal_x = 12;          //Goal x location
  int goal_y = 12;          //Goal y location
  int step = 5;             //Size of step
  int radius = 5;           //How close do we need to be to the goal?

  /***************************************************************************/

  //Create an empty list for our obstacles
  std::list<Obstacle> obstacle_list;

  //Create a map of size map_height, map_width
  Map specificMap(map_height, map_width, obstacle_list);

  /************************** Create obstacles here **************************/
  //Create obstacles (make as many as you like!)
  Obstacle obs(15, 15, 3);
  //Add our obstacle(s) to our map
  specificMap.add_obstacle(obs);
  /***************************************************************************/

  //Create our path object
  RRTPath rrt(specificMap, start_x, start_y, goal_x, goal_y, step, radius);

  //Start it running and save the path
  std::list<std::pair<int, int>> path = rrt.find_path();

  //Print the path for funsies so we can see where we went
  std::list<std::pair<int, int>>::iterator it;
  std::cout << "Path from start to goal" << std::endl;
  for (it = path.begin(); it != path.end(); ++it) {
    std::cout << it->first << ", " << it->second << std::endl;
  }
  return 0;
}
