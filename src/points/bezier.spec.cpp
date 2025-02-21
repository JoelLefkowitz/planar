#include "bezier.hpp"
#include "point.hpp"
#include <funky/generics/iterables.tpp>
#include <gtest/gtest.h>

using namespace planar;

TEST(Bezier, Repr) {
    EXPECT_EQ(
        Bezier({0, 0}, {0, 1}, {1, 1}, {1, 0}).repr(),
        "[{x: 0, y: 0}, {x: 0, y: 1}, {x: 1, y: 1}, {x: 1, y: 0}]"
    );
}

TEST(Bezier, Point) {
    Bezier bezier({0, 0}, {0, 1}, {1, 1}, {1, 0});

    EXPECT_NEAR(bezier.point(0).x(), 0, 0.01);
    EXPECT_NEAR(bezier.point(0).y(), 0, 0.01);

    EXPECT_NEAR(bezier.point(0.5).x(), 0.5, 0.01);
    EXPECT_NEAR(bezier.point(0.5).y(), 0.75, 0.01);

    EXPECT_NEAR(bezier.point(1).x(), 1, 0.01);
    EXPECT_NEAR(bezier.point(1).y(), 0, 0.01);
}

TEST(Bezier, SquareError) {
    Bezier bezier({0, 0}, {0, 0}, {1, 1}, {1, 1});
    std::vector<Point<double>> points({
        {0, 1}
    });

    EXPECT_NEAR(bezier.square_error(points), 1, 0.01);

    points.emplace_back(1, 0);
    EXPECT_NEAR(bezier.square_error(points), 2, 0.01);
}
