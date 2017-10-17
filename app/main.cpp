#include <iostream>
#include "rrt_path.h"

int main()
{
  int startX = 0;
  int startY = 0;
  int goalX = 12;
  int goalY = 12;
  int step = 5;
  int radius = 5;
  Obstacle obs(15, 15, 3);
  std::list<Obstacle> obsList;

  Map specificMap(15, 15, obsList);
  specificMap.addObstacle(obs);
  RRTPath rrt(specificMap, startX, startY, goalX, goalY, step, radius);
  std::list<std::pair<int, int>> path = rrt.findPath();
    return 0;
}
