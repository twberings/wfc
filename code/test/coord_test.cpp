#include "wfc/coord.hpp"
#include <gtest/gtest.h>

class CoordTest : public ::testing::Test {
protected:
  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(CoordTest, To_string) {
  int coords[] = {1, 2, 3};
  Coord coord(3, coords);
  EXPECT_EQ(coord.To_string(), "(1, 2, 3)");
}

TEST_F(CoordTest, Get_neighbors) {
  int coords[] = {1, 2};
  Coord coord(2, coords);
  std::vector<Coord> neighbors = coord.Get_neighbors();
  EXPECT_EQ(neighbors.size(), 4);
  EXPECT_EQ(neighbors[0].To_string(), "(2, 2)");
  EXPECT_EQ(neighbors[1].To_string(), "(0, 2)");
  EXPECT_EQ(neighbors[2].To_string(), "(1, 3)");
  EXPECT_EQ(neighbors[3].To_string(), "(1, 1)");
}

TEST_F(CoordTest, Get_direction) {
  int origin_coords[] = {1, 2};
  Coord origin(2, origin_coords);
  int up_coords[] = {1, 1};
  Coord up(2, up_coords);
  int right_coords[] = {2, 2};
  Coord right(2, right_coords);
  int down_coords[] = {1, 3};
  Coord down(2, down_coords);
  int left_coords[] = {0, 2};
  Coord left(2, left_coords);

  EXPECT_EQ(origin.Get_direction(left), 0);
  EXPECT_EQ(origin.Get_direction(right), 1);
  EXPECT_EQ(origin.Get_direction(up), 2);
  EXPECT_EQ(origin.Get_direction(down), 3);
}

TEST_F(CoordTest, Equals) {
  int coords1[] = {1, 2};
  Coord coord1(2, coords1);
  int coords2[] = {1, 2};
  Coord coord2(2, coords2);
  int coords3[] = {1, 3};
  Coord coord3(2, coords3);

  EXPECT_TRUE(coord1 == coord2);
  EXPECT_FALSE(coord1 == coord3);
  EXPECT_TRUE(coord1 == coord1);
}
