#include "dimensions.hpp"
#include <gtest/gtest.h>

using namespace linear;

TEST(Dimensions, Operators) {
    EXPECT_FALSE(Dimensions(0, 0) == Dimensions(1, 1));
    EXPECT_TRUE(Dimensions(1, 1) == Dimensions(1, 1));
}

TEST(Dimensions, Repr) {
    EXPECT_EQ(Dimensions(1, 1).repr(), "{rows: 1, cols: 1}");
}
