#include "gtest/gtest.h"

#include "dummy/dummy.hpp"

TEST(dummy_test, test_sum)
{
  my::Dummy dummy(1, 2);
  EXPECT_EQ(dummy.Sum(), 3);
}
