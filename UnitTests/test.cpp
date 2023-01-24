#include "../main.h"
#include "gtest/gtest.h"

TEST(TestCase, SimpleTest)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);

  const char* test1 = "X X X X X X X X X X X X";
  EXPECT_EQ(ComputeScore(test1), 300);
  
  const char* test2 = "9- 9- 9- 9- 9- 9- 9- 9- 9- 9-";
  EXPECT_EQ(ComputeScore(test2), 90);
}
