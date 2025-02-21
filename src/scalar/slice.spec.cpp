#include "slice.hpp"
#include <gtest/gtest.h>

using namespace planar;

TEST(Slice, Operators) {
    EXPECT_FALSE(Slice(0, 0) == Slice(1, 1));
    EXPECT_TRUE(Slice(1, 1) == Slice(1, 1));
}
