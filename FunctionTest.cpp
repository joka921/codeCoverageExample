#include <gtest/gtest.h>

#include "./Function.h"

TEST(Function, SimpleTest) {
  ASSERT_EQ(24, twice(12));
}
