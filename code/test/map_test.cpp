#include "mtile.hpp"
#include "wfc/map2d.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

class MapTest : public ::testing::Test {
protected:
  MapTest()
      : tile1(std::make_shared<MTile>()), tile2(std::make_shared<MTile>()),
        tileSet({tile1, tile2}), map(width, height, tileSet) {}
  virtual ~MapTest() {}

  int width = 3;
  int height = 3;
  std::shared_ptr<MTile> tile1;
  std::shared_ptr<MTile> tile2;
  std::vector<std::shared_ptr<ITile<int>>> tileSet;

  Map2D<int> map;
};

TEST_F(MapTest, Output) {
  EXPECT_CALL(*tile1, Output()).Times(9).WillRepeatedly(testing::Return(1));
  EXPECT_CALL(*tile2, Output()).Times(9).WillRepeatedly(testing::Return(2));
  std::vector<std::vector<int>> output = map.Output();
  EXPECT_EQ(output.size(), 9);
  EXPECT_EQ(output[0].size(), 2);
}

TEST_F(MapTest, Get_position) {
  int coords[] = {1, 1};
  std::optional<std::reference_wrapper<Position<int>>> result =
      map.Get_position(Coord(2, coords));
  EXPECT_TRUE(result.has_value());
  Position<int> &position = result.value().get();
  EXPECT_EQ(position.Get_coord(), Coord(2, coords));
}

TEST_F(MapTest, Collapse_at) {
  EXPECT_CALL(*tile1, Check_constraints(testing::_, testing::_))
      .Times(testing::AtLeast(1))
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(*tile2, Check_constraints(testing::_, testing::_))
      .Times(testing::AtLeast(1))
      .WillRepeatedly(testing::Return(true));

  int coords[] = {1, 1};
  map.Collapse_at(Coord(2, coords));
  std::optional<std::reference_wrapper<Position<int>>> result =
      map.Get_position(Coord(2, coords));
  EXPECT_TRUE(result.has_value());
  Position<int> &position = result.value().get();
  EXPECT_EQ(position.Get_entropy(), 1);
}

TEST_F(MapTest, Is_solved) {
  EXPECT_CALL(*tile1, Check_constraints(testing::_, testing::_))
      .Times(testing::AtLeast(1))
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(*tile2, Check_constraints(testing::_, testing::_))
      .Times(testing::AtLeast(1))
      .WillRepeatedly(testing::Return(true));

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int coords[] = {x, y};
      EXPECT_FALSE(map.Is_solved());
      map.Collapse_at(Coord(2, coords));
    }
  }
  EXPECT_TRUE(map.Is_solved());
}
