#include "bezier.hpp"
#include "point.hpp"
#include <functional/generics/functor/map.tpp>
#include <gtest/gtest.h>

using namespace linear;

TEST(Bezier, FromPoints) {
    Bezier reference({0, 0}, {0, 1}, {1, 1}, {1, 0});
    auto   points = reference.sample(100);

    Bezier bezier(points);

    EXPECT_EQ(bezier.p1, points.front());
    EXPECT_EQ(bezier.p4, points.back());

    EXPECT_NEAR(bezier.p2.x(), 0, 0.2);
    EXPECT_NEAR(bezier.p2.y(), 1, 0.2);

    EXPECT_NEAR(bezier.p3.x(), 1, 0.2);
    EXPECT_NEAR(bezier.p3.y(), 1, 0.2);
}

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
    EXPECT_NEAR(bezier.square_error(bezier.sample(10)), 0, 0.01);

    std::vector<Point<double>> points({
        {0, 1}
    });

    EXPECT_NEAR(bezier.square_error(points), 1, 0.01);

    points.emplace_back(1, 0);
    EXPECT_NEAR(bezier.square_error(points), 2, 0.01);
}
