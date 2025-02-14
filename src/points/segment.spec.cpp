#include "segment.tpp"
#include "point.hpp"
#include <gtest/gtest.h>

using namespace linear;

TEST(Segment, Midpoint) {
    EXPECT_EQ(Segment<double>({0.0, 0.0}, {2.0, 2.0}).midpoint(), Point(1.0, 1.0));
}

TEST(Segment, Repr) {
    EXPECT_EQ(Segment<double>({0.0, 0.0}, {1.0, 1.0}).repr(), "{start: {x: 0, y: 0}, end: {x: 1, y: 1}}");
}
