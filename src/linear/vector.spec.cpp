#include "vector.tpp"
#include <gtest/gtest.h>

using namespace linear;

TEST(Vector, Operators) {
    EXPECT_TRUE(Vector(1, 1) == Vector(1, 1));
    EXPECT_FALSE(Vector(1, 1) == Vector(2, 2));

    EXPECT_TRUE(Vector(1, 1) < Vector(2, 2));
    EXPECT_TRUE(Vector(1, 3) < Vector(2, 2));
    EXPECT_TRUE(Vector(2, 1) < Vector(2, 2));
    EXPECT_FALSE(Vector(2, 2) < Vector(2, 2));

    EXPECT_EQ(Vector(1, 1) + Vector(1, 1), Vector(2, 2));
    EXPECT_EQ(Vector(1, 1) - Vector(1, 1), Vector(0, 0));

    EXPECT_EQ(Vector(1, 1) * 2, Vector(2, 2));
    EXPECT_EQ(Vector(2, 2) / 2, Vector(1, 1));
}

TEST(Vector, Repr) { EXPECT_EQ(Vector(1, 1).repr(), "{x: 1, y: 1}"); }

TEST(Vector, Magnitude) { EXPECT_EQ(Vector(3, 4).magnitude(), 5.0); }
