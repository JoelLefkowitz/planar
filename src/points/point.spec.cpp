#include "point.tpp"
#include "../linear/vector.tpp"
#include <gtest/gtest.h>

using namespace linear;

TEST(Point, Operators) {
    EXPECT_EQ(Point(1, 1) + Vector(1, 1), Point(2, 2));
    EXPECT_EQ(Point(1, 1) - Vector(1, 1), Point(0, 0));

    EXPECT_EQ(Point(1, 1) + Size(1, 1), Point(2, 2));
    EXPECT_EQ(Point(1, 1) - Size(1, 1), Point(0, 0));
}

TEST(Point, Repr) { EXPECT_EQ(Point(1, 1).repr(), "{x: 1, y: 1}"); }

TEST(Point, Zero) {
    EXPECT_TRUE(Point(0, 0).zero());

    EXPECT_FALSE(Point(0, 1).zero());
    EXPECT_FALSE(Point(1, 0).zero());
    EXPECT_FALSE(Point(1, 1).zero());
}

TEST(Point, Scale) {
    EXPECT_EQ(Point(1, 1).scale(1), Point(1, 1));
    EXPECT_EQ(Point(1, 1).scale(2), Point(2, 2));
    EXPECT_EQ(Point(1, 1).scale({2, 3}), Point(2, 3));
}

TEST(Point, Flip) {
    EXPECT_EQ(Point(1, 1).flip({0, 0}), Point(-1, -1));
    EXPECT_EQ(Point(1, 1).flip({1, 1}), Point(1, 1));
    EXPECT_EQ(Point(1, 1).flip({2, 2}), Point(3, 3));
}

TEST(Point, FlipX) {
    EXPECT_EQ(Point(1, 1).flip_x(0), Point(-1, 1));
    EXPECT_EQ(Point(1, 1).flip_x(1), Point(1, 1));
    EXPECT_EQ(Point(1, 1).flip_x(2), Point(3, 1));
}

TEST(Point, FlipY) {
    EXPECT_EQ(Point(1, 1).flip_y(0), Point(1, -1));
    EXPECT_EQ(Point(1, 1).flip_y(1), Point(1, 1));
    EXPECT_EQ(Point(1, 1).flip_y(2), Point(1, 3));
}

TEST(Point, Shift) { EXPECT_EQ(Point(1, 1).shift({1, 2}), Point(2, 3)); }

TEST(Point, Center) {
    EXPECT_EQ(Point(1, 1).center({10, 10}), Point(-4, -4));
    EXPECT_EQ(Point(1, 1).center_horizontal({10, 10}), Point(-4, 1));
    EXPECT_EQ(Point(1, 1).center_vertical({10, 10}), Point(1, -4));
}

TEST(Point, Linspace) {
    auto points = Point<double>::linspace({}, 0.0, 1.0);
    EXPECT_TRUE(points.empty());

    points = Point<double>::linspace({0.0}, 0.0, 1.0);
    EXPECT_EQ(points[0], Point(0.5, 0.0));

    points = Point<double>::linspace({0.0, 1.0}, 0.0, 1.0);
    EXPECT_EQ(points[0], Point(0.0, 0.0));
    EXPECT_EQ(points[1], Point(1.0, 1.0));

    points = Point<double>::linspace({0.0, 1.0, 2.0}, 0.0, 2.0);
    EXPECT_EQ(points[0], Point(0.0, 0.0));
    EXPECT_EQ(points[1], Point(1.0, 1.0));
    EXPECT_EQ(points[2], Point(2.0, 2.0));
}
