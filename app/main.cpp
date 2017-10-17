#include <iostream>
#include "rrt_path.h"

int main()
{
  //Set our starting variables
  int start_x = 0;          //Path beginning x location
  int start_y = 0;          //Path beginning y location
  int goal_x = 12;           //Goal x location
  int goal_y = 12;           //Goal y location
  int step = 5;             //Size of step
  int radius = 5;           //How close do we need to be to the goal?
  int map_width = 15;       //Width of map
  int map_height = 15;      //Height of map

  //Create an empty list for our obstacles
  std::list<Obstacle> obstacle_list;

  //Create a map of size map_height, map_width
  Map specificMap(map_height, map_width, obstacle_list);

  //Create an obstacle (you can create more)
  Obstacle obs(15, 15, 3);
  //Add our obstacle to our map
  specificMap.add_obstacle(obs);

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
