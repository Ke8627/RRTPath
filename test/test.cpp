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
  std::pair<int, int> location = obs.GetLocation();
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
  EXPECT_EQ(obs.GetSize(), 5);
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
  EXPECT_EQ(vertex.get_location().first, 5);
  EXPECT_EQ(vertex.get_location().second, 7);
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
  EXPECT_EQ(root, nextVertex.get_parent());
  EXPECT_EQ(root->get_location().first, 5);
  EXPECT_EQ(root->get_location().second, 7);
}

/**
 * @brief tests the Map constructor
 */
TEST(map, constructor) {
  //Check generic map constructor
  //Size should be 10x10 with no obstacles
  Map genericMap;
  EXPECT_EQ(genericMap.GetSize().first, 10);
  EXPECT_EQ(genericMap.GetSize().second, 10);
  EXPECT_TRUE(genericMap.GetObstacleList().size()==0);

  //Create an obstacle and add it to a list
  Obstacle obs(5, 10, 3);
  std::list<Obstacle> obsList;
  obsList.push_back(obs);

  //Create a non-generic map with that obstacle list
  //Check size 15x20
  //Check that it has an obstacle
  Map specificMap(15, 20, obsList);
  EXPECT_EQ(specificMap.GetSize().first, 15);
  EXPECT_EQ(specificMap.GetSize().second, 20);
  EXPECT_TRUE(specificMap.GetObstacleList().size()==1);
}

TEST(map, obstacle_tests) {
  Obstacle obs(1, 1, 3);
  std::list<Obstacle> obsList;

  //constructor
  Map specificMap(15, 20, obsList);
  EXPECT_TRUE(specificMap.GetObstacleList().size()==0);

  //add obstacle
  specificMap.AddObstacle(obs);
  EXPECT_TRUE(specificMap.GetObstacleList().size()==1);

  //get obstacle list
  std::list<Obstacle> obsList2 = specificMap.GetObstacleList();
  EXPECT_TRUE(obsList2.size()==1);

  //remove obstacle
  specificMap.RemoveObstacle(obs);
  EXPECT_TRUE(specificMap.GetObstacleList().size()==0);
}



/**
 * @brief tests RRTPath
 */
TEST(path, constructor) {
  //Create an RRTPath with a single obstacle
  Obstacle obs(1, 1, 3);
  std::list<Obstacle> obsList;
  Map specificMap(15, 20, obsList);
  specificMap.AddObstacle(obs);
  RRTPath rrt(specificMap, 0, 0, 15, 15, 5, 5);

  //Check the getters and setters
  EXPECT_EQ(rrt.map_.GetSize().first, 15);
  EXPECT_EQ(rrt.map_.GetSize().second, 20);
  EXPECT_EQ(rrt.root_node_->get_location().first, 0);
  EXPECT_EQ(rrt.root_node_->get_location().second, 0);
  EXPECT_EQ(rrt.goal_location_.first, 15);
  EXPECT_EQ(rrt.goal_location_.second, 15);
  EXPECT_EQ(rrt.epsilon_, 5);
  EXPECT_EQ(rrt.goal_radius_, 5);
}

TEST(path, random_points) {
  //Create an RRTPath
  std::list<Obstacle> obsList;
  Map specificMap(15, 20, obsList);
  RRTPath rrt(specificMap, 0, 0, 15, 15, 5, 5);

  //Check that point is within map bounds
  std::pair<int, int> randomPoint = rrt.GetRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.GetSize().first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.GetSize().second);
  EXPECT_GE(randomPoint.second, 0);

  //Check several times
  randomPoint = rrt.GetRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.GetSize().first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.GetSize().second);
  EXPECT_GE(randomPoint.second, 0);

  randomPoint = rrt.GetRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.GetSize().first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.GetSize().second);
  EXPECT_GE(randomPoint.second, 0);

  randomPoint = rrt.GetRandomPoint();
  EXPECT_LE(randomPoint.first, specificMap.GetSize().first);
  EXPECT_GE(randomPoint.first, 0);
  EXPECT_LE(randomPoint.second, specificMap.GetSize().second);
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
  EXPECT_NEAR(rrt.GetDistance(pointA, pointB), 1.41421, 0.0001);
  EXPECT_NEAR(rrt.GetDistance(pointA, pointC), 7.07106, 0.0001);
  EXPECT_NEAR(rrt.GetDistance(pointA, pointD), 15.620499, 0.0001);
}

/**
 * @brief tests path safety
 */
TEST(path, safety_test) {
  //Create an obstacle and insert it into a map
  Obstacle obs(1, 1, 1);
  std::list<Obstacle> obsList;
  Map specificMap(15, 20, obsList);
  specificMap.AddObstacle(obs);
  RRTPath rrt(specificMap, 0, 0, 15, 15, 5, 5);

  //Create a vertex and a point
  //Path should go through the obstacle, so not safe
  std::pair<int, int> v(0, 0);
  std::pair<int, int> p(5, 5);
  EXPECT_FALSE(rrt.IsSafe(v, p));

  //Change the location of the point
  //Path should not go through obstacle, so safe
  p.first = 0;
  p.second = 1;
  EXPECT_TRUE(rrt.IsSafe(v, p));

  p.first = 100;
  p.second = 100;
  EXPECT_FALSE(rrt.IsSafe(v,p));
}

TEST(path, algorithm_test) {
  //Create an RRTPath
  Obstacle obs(15, 15, 3);
  std::list<Obstacle> obsList;
  std::list<std::pair<int, int>> path;
  Map specificMap(15, 15, obsList);
  specificMap.AddObstacle(obs);
  RRTPath rrt(specificMap, 0, 0, 12, 12, 5, 5);

  //testing moving towards the point, closest vertex should be the root
  //shouldn't be any obstacles in the way of moving from 0,0 to 3,3
  Vertex* closest = rrt.GetClosestPoint(std::pair<int, int>(10, 10));
  EXPECT_EQ(closest->x_, rrt.root_node_->x_);
  EXPECT_EQ(closest->y_, rrt.root_node_->y_);
  EXPECT_TRUE(rrt.vertex_list_.size()==1);
  EXPECT_TRUE(rrt.MoveTowardsPoint(closest, std::pair<int, int>(10, 10)));
  EXPECT_TRUE(rrt.vertex_list_.size()==2);

  //Check to make sure that the closest node is now at 3,3 rather than root
  //should be able to move from 3,3 to 6,6
  closest = rrt.GetClosestPoint(std::pair<int, int>(10, 10));
  EXPECT_EQ(closest->x_, 3);
  EXPECT_EQ(closest->y_, 3);
  EXPECT_TRUE(rrt.MoveTowardsPoint(closest, std::pair<int, int>(10, 10)));
  EXPECT_TRUE(rrt.vertex_list_.size()==3);

  //Check to make sure closest node is now at 6,6
  //should be able to get from 6,6 to 9,9
  closest = rrt.GetClosestPoint(std::pair<int, int>(15, 15));
  EXPECT_EQ(closest->x_, 6);
  EXPECT_EQ(closest->y_, 6);
  EXPECT_TRUE(rrt.MoveTowardsPoint(closest, std::pair<int,int>(15, 15)));
  EXPECT_TRUE(rrt.vertex_list_.size()==4);

  //Check to make sure closest node is now at 9,9
  //should be able to get from 9,9 to 12,12
  closest = rrt.GetClosestPoint(std::pair<int, int>(15, 15));
  EXPECT_EQ(closest->x_, 9);
  EXPECT_EQ(closest->y_, 9);
  EXPECT_TRUE(rrt.MoveTowardsPoint(closest, std::pair<int,int>(15, 15)));
  EXPECT_TRUE(rrt.vertex_list_.size()==5);

  //should not be able to move to 15,15 because of an obstacle
  //but should be within range of the goal
  closest = rrt.GetClosestPoint(std::pair<int, int>(15, 15));
  EXPECT_FALSE(rrt.MoveTowardsPoint(closest, std::pair<int, int>(15, 15)));
  EXPECT_TRUE(rrt.vertex_list_.size()==5);
  EXPECT_TRUE(rrt.ReachedGoal(closest->get_location()));

  //rebuild the path
  path = rrt.CalculatePath(rrt.vertex_list_.front());
  //path should be of size 5: 0,0; 3,3; 6,6; 9,9; 12,12
  EXPECT_TRUE(path.size()==5);
  std::list<std::pair<int, int>>::iterator it;
  int loc = 0;
  for (it=path.begin(); it != path.end(); ++it) {
    EXPECT_EQ(it->first, loc);
    EXPECT_EQ(it->second,loc);
    loc += 3;
  }
}

TEST(path, find_path) {
  //Create an RRTPath
  Obstacle obs(15, 15, 3);
  std::list<Obstacle> obsList;
  std::list<std::pair<int, int>> path;
  Map specificMap(15, 15, obsList);
  specificMap.AddObstacle(obs);
  RRTPath rrt(specificMap, 0, 0, 12, 12, 5, 5);

  path = rrt.FindPath();
  //Can't test exact path coords because of the randomness
  //We do know that the most direct path takes at least 4 moves
  //therefore the size of our rebuilt list should be greater than 3
  EXPECT_TRUE(path.size() > 3);
}
