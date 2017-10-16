#include <gtest/gtest.h>

#define private public
#include <rrt_path.h>
#undef private

/**
 * @brief tests the location part of the Obstacle class
 */
TEST(obstacle, location) {
  //Create an obstacle and check the location
  Obstacle obs(0, 0, 5);
  std::pair<int, int> location = obs.getLocation();
  /**
   * Tests location setting and getting of obstacle
   */
  EXPECT_EQ(location.first, 0);
  EXPECT_EQ(location.second, 0);
}

/**
 * @brief tests the size part of the Obstacle class
 */
TEST(obstacle, size) {
  //Create an obstacle and check the size
  Obstacle obs(0, 0, 5);
  EXPECT_EQ(obs.getSize(), 5);
}

/**
 * @brief tests operator overloads
 */
TEST(obstacle, overloads) {
  //Create 3 obstacles and check their comparators
  //d should is bigger than a, so should be GT
  //a should be smaller than d, so should be LT
  //a and b are the same size in same location so should be equal
  //a and c are the same size, but different location so should be not equal

  Obstacle a(0, 0, 5);
  Obstacle b(0, 0, 5);
  Obstacle c(1, 1, 5);
  Obstacle d(0, 0, 10);
  EXPECT_GT(d, a);
  EXPECT_LT(a, d);
  EXPECT_EQ(a, b);
  EXPECT_NE(a, c);
}

/**
 * @brief tests the location of the Vertex class
 */
TEST(vertex, location) {
  //Create vertex, check location
  Vertex vertex(5, 7, nullptr);
  EXPECT_EQ(vertex.getLocation().first, 5);
  EXPECT_EQ(vertex.getLocation().second, 7);
}

/**
 * @brief tests the prevVertex of the Vertex class
 */
TEST(vertex, previous_vertex) {
  //Create a root vertex and a child
  //Check that the root is the child's parent
  //Check that the location of the root is correct
  Vertex *root = new Vertex(5, 7, nullptr);
  Vertex nextVertex(10, 12, root);
  EXPECT_EQ(root, nextVertex.getParent());
  EXPECT_EQ(root->getLocation().first, 5);
  EXPECT_EQ(root->getLocation().second, 7);
}

/**
 * @brief tests the Map constructor
 */
TEST(map, constructor) {
  //Check generic map constructor
  //Size should be 10x10 with no obstacles
  Map genericMap;
  EXPECT_EQ(genericMap.getSize().first, 10);
  EXPECT_EQ(genericMap.getSize().second, 10);
  EXPECT_EQ(genericMap.getObstacleList().size(), 0);

  //Create an obstacle and add it to a list
  Obstacle obs(5, 10, 3);
  std::list<Obstacle> obsList;
  obsList.push_back(obs);

  //Create a non-generic map with that obstacle list
  //Check size 15x20
  //Check that it has an obstacle
  Map specificMap(15, 20, obsList);
  EXPECT_EQ(specificMap.getSize().first, 15);
  EXPECT_EQ(specificMap.getSize().second, 20);
  EXPECT_EQ(specificMap.getObstacleList().size(), 1);
}

TEST(map, obstacle_tests) {
  Obstacle obs(1, 1, 3);
  std::list<Obstacle> obsList;

  //constructor
  Map specificMap(15, 20, obsList);
  EXPECT_EQ(specificMap.getObstacleList().size(), 0);

  //add obstacle
  specificMap.addObstacle(obs);
  EXPECT_EQ(specificMap.getObstacleList().size(), 1);

  //get obstacle list
  std::list<Obstacle> obsList2 = specificMap.getObstacleList();
  EXPECT_EQ(obsList2.size(), 1);

  //remove obstacle
  specificMap.removeObstacle(obs);
  EXPECT_EQ(specificMap.getObstacleList().size(), 0);
}



/**
 * @brief tests RRTPath
 */
TEST(path, constructor) {
  //Create an RRTPath with a single obstacle
  Obstacle obs(1, 1, 3);
  std::list<Obstacle> obsList;
  Map specificMap(15, 20, obsList);
  specificMap.addObstacle(obs);
  RRTPath rrt(specificMap, 0, 0, 15, 15, 5, 5);

  //Check the getters and setters
  EXPECT_EQ(rrt.map.getSize().first, 15);
  EXPECT_EQ(rrt.map.getSize().second, 20);
  EXPECT_EQ(rrt.root->getLocation().first, 0);
  EXPECT_EQ(rrt.root->getLocation().second, 0);
  EXPECT_EQ(rrt.goalLocation.first, 15);
  EXPECT_EQ(rrt.goalLocation.second, 15);
  EXPECT_EQ(rrt.epsilon, 5);
  EXPECT_EQ(rrt.goalRadius, 5);
}

TEST(path, random_points) {
  //Create an RRTPath
  std::list<Obstacle> obsList;
  Map specificMap(15, 20, obsList);
  RRTPath rrt(specificMap, 0, 0, 15, 15, 5, 5);

  //Check that point is within map bounds
  std::pair<int, int> randomPoint = rrt.getRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.size.first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.size.second);
  EXPECT_GE(randomPoint.second, 0);

  //Check several times
  randomPoint = rrt.getRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.size.first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.size.second);
  EXPECT_GE(randomPoint.second, 0);

  randomPoint = rrt.getRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.size.first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.size.second);
  EXPECT_GE(randomPoint.second, 0);

  randomPoint = rrt.getRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.size.first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.size.second);
  EXPECT_GE(randomPoint.second, 0);
}

TEST(path, get_distance) {
  //Create an RRTPath
  std::list<Obstacle> obsList;
  Map specificMap(15, 20, obsList);
  RRTPath rrt(specificMap, 0, 0, 15, 15, 5, 5);

  //create points
  std::pair<int, int> pointA(0,0);
  std::pair<int, int> pointB(1,1);
  std::pair<int, int> pointC(5,5);
  std::pair<int, int> pointD(10,12);
  EXPECT_NEAR(rrt.getDistance(pointA, pointB), 1.41421, 0.0001);
  EXPECT_NEAR(rrt.getDistance(pointA, pointC), 7.07106, 0.0001);
  EXPECT_NEAR(rrt.getDistance(pointA, pointD), 15.620499, 0.0001);
}

/**
 * @brief tests path safety
 */
TEST(path, safety_test) {
  //Create an obstacle and insert it into a map
  Obstacle obs(1, 1, 3);
  std::list<Obstacle> obsList;
  Map specificMap(15, 20, obsList);
  specificMap.addObstacle(obs);
  RRTPath rrt(specificMap, 0, 0, 15, 15, 5, 5);

  //Create a vertex and a point
  //Path should go through the obstacle, so not safe
  std::pair<int, int> v(0, 0);
  std::pair<int, int> p(5, 5);
  EXPECT_FALSE(rrt.isSafe(v, p));

  //Change the location of the point
  //Path should not go through obstacle, so safe
  p.first = 0;
  p.second = 1;
  EXPECT_TRUE(rrt.isSafe(v, p));
}

TEST(path, algorithm_test) {
  //Create an RRTPath
  Obstacle obs(15, 15, 3);
  std::list<Obstacle> obsList;
  Map specificMap(15, 15, obsList);
  specificMap.addObstacle(obs);
  RRTPath rrt(specificMap, 0, 0, 12, 12, 5, 5);

  //testing moving towards the point, closest vertex should be the root
  //shouldn't be any obstacles in the way of moving from 0,0 to 3,3
  Vertex* closest = rrt.getClosestPoint(std::pair<int, int>(10, 10));
  EXPECT_EQ(closest->x, rrt.root->x);
  EXPECT_EQ(closest->y, rrt.root->y);
  EXPECT_EQ(rrt.vertexList.size(), 1);
  EXPECT_TRUE(rrt.moveTowardsPoint(closest, std::pair<int, int>(10, 10)));
  EXPECT_EQ(rrt.vertexList.size(), 2);

  //Check to make sure that the closest node is now at 3,3 rather than root
  //should be able to move from 3,3 to 6,6
  closest = rrt.getClosestPoint(std::pair<int, int>(10, 10));
  EXPECT_EQ(closest->x, 3);
  EXPECT_EQ(closest->y, 3);
  EXPECT_TRUE(rrt.moveTowardsPoint(closest, std::pair<int, int>(10, 10)));
  EXPECT_EQ(rrt.vertexList.size(), 3);

  //Check to make sure closest node is now at 6,6
  //should be able to get from 6,6 to 9,9
  closest = rrt.getClosestPoint(std::pair<int, int>(15, 15));
  EXPECT_EQ(closest->x, 6);
  EXPECT_EQ(closest->y, 6);
  EXPECT_TRUE(rrt.moveTowardsPoint(closest, std::pair<int,int>(15, 15)));
  EXPECT_EQ(rrt.vertexList.size(), 4);

  //Check to make sure closest node is now at 9,9
  //should be able to get from 9,9 to 12,12
  closest = rrt.getClosestPoint(std::pair<int, int>(15, 15));
  EXPECT_EQ(closest->x, 9);
  EXPECT_EQ(closest->y, 9);
  EXPECT_TRUE(rrt.moveTowardsPoint(closest, std::pair<int,int>(15, 15)));
  EXPECT_EQ(rrt.vertexList.size(), 5);

  //should not be able to move to 15,15 because of an obstacle
  //but should be within range of the goal
  EXPECT_FALSE(rrt.moveTowardsPoint(closest, std::pair<int, int>(15, 15)));
  EXPECT_EQ(rrt.vertexList.size(), 5);
  EXPECT_TRUE(rrt.reachedGoal(closest->getLocation()));
}

