#include "unicode/unicodetile.hpp"
#include <gtest/gtest.h>
#include <memory>

class UnicodeTileTest : public ::testing::Test {
protected:
  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(UnicodeTileTest, Check_constraints) {
  UnicodeTile tile1(0, 1, 2, 0, "TEST");
  UnicodeTile tile2(2, 1, 1, 1, "TEST");
  std::shared_ptr<ITile<std::string>> tile2_ptr = std::make_shared<UnicodeTile>(tile2);

  const int left = 0;
  const int right = 1;
  const int up = 2;
  const int down = 3;

  EXPECT_TRUE(tile1.Check_constraints(tile2_ptr, right));
  EXPECT_FALSE(tile1.Check_constraints(tile2_ptr, left));
  EXPECT_FALSE(tile1.Check_constraints(tile2_ptr, up));
  EXPECT_TRUE(tile1.Check_constraints(tile2_ptr, down));
}
