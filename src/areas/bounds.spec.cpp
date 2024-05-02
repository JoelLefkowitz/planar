#include "bounds.hpp"
#include "matrix.tpp"
#include "point.tpp"
#include "segment.tpp"
#include "vector.tpp"
#include <gtest/gtest.h>

using namespace linear;

// clang-format off
TEST(Bounds, FromVector) {
    EXPECT_EQ(
        Bounds(
            std::vector<Bounds>({
                {0, 0, 1, 1},
                {1, 0, 1, 1},
                {0, 1, 2, 2}
            })
        ),
        Bounds(0, 0, 2, 3)
    );
}

TEST(Bounds, FromMatrix) {
    EXPECT_EQ(
        Bounds(
            Matrix<Bounds>({
                {{0, 0, 1, 1}, {1, 0, 1, 1}},
                {{0, 1, 1, 1}, {1, 1, 1, 1}},
                {{0, 2, 1, 1}, {1, 2, 1, 1}},
            })
        ),
        Bounds(0, 0, 2, 3)
    );

    EXPECT_EQ(
        Bounds(
            Matrix<Bounds>({
                {{0, 0, 1, 1}, {1, 0, 1, 1}, {2, 0, 1, 1}},
                {{0, 1, 1, 1}, {1, 1, 1, 1}, {2, 1, 1, 1}},
            })
        ),
        Bounds(0, 0, 3, 2)
    );
}

TEST(Bounds, Enclose) {
    EXPECT_EQ(
        Bounds::enclose(
            std::vector<Point<double>>({
                {0, 1},
                {1, 0}
            })
        ),
        Bounds(0, 0, 1, 1)
    );

    EXPECT_EQ(
        Bounds::enclose(
            std::vector<Point<double>>({
                {1, 1},
                {2, 5},
                {5, 2}
            })
        ),
        Bounds(1, 1, 4, 4)
    );
}

TEST(Bounds, Operators) {
    EXPECT_TRUE(Bounds(1, 1, 1, 1) == Bounds(1, 1, 1, 1));
    EXPECT_FALSE(Bounds(1, 1, 1, 1) == Bounds(2, 2, 2, 2));

    EXPECT_TRUE(Bounds(1, 3, 3, 3) < Bounds(2, 2, 2, 2));
    EXPECT_TRUE(Bounds(2, 1, 3, 3) < Bounds(2, 2, 2, 2));
    EXPECT_TRUE(Bounds(2, 2, 1, 3) < Bounds(2, 2, 2, 2));
    EXPECT_TRUE(Bounds(2, 2, 2, 1) < Bounds(2, 2, 2, 2));

    EXPECT_EQ(Bounds(1, 1, 2, 2) + Size<double>(1, 1), Bounds(1, 1, 3, 3));
    EXPECT_EQ(Bounds(1, 1, 2, 2) - Size<double>(1, 1), Bounds(1, 1, 1, 1));

    EXPECT_EQ(Bounds(1, 1, 1, 1) * 2, Bounds(1, 1, 2, 2));
    EXPECT_EQ(Bounds(1, 1, 2, 2) / 2, Bounds(1, 1, 1, 1));
}

TEST(Bounds, Repr) {
    EXPECT_EQ(Bounds(1, 1, 1, 1).repr(), "{{x: 1, y: 1}, {width: 1, height: 1}}");
}

TEST(Bounds, Empty) {
    EXPECT_TRUE(Bounds(0, 0, 0, 0).empty());
    EXPECT_TRUE(Bounds(1, 1, 0, 0).empty());

    EXPECT_FALSE(Bounds(0, 0, 0, 1).empty());
    EXPECT_FALSE(Bounds(0, 0, 1, 0).empty());
    EXPECT_FALSE(Bounds(0, 0, 1, 1).empty());
}

TEST(Bounds, Corners) {
    EXPECT_EQ(
        Bounds(1.0, 1.0, 1.0, 1.0).corners(), 
        std::vector<Point<double>>({
            {1.0, 1.0},
            {2.0, 1.0},
            {1.0, 2.0},
            {2.0, 2.0},
        })
    );

    EXPECT_EQ(
        Bounds(1.0, 1.0, 2.0, 3.0).corners(), 
        std::vector<Point<double>>({
            {1.0, 1.0},
            {3.0, 1.0},
            {1.0, 4.0},
            {3.0, 4.0},
        })
    );
}

TEST(Bounds, Midpoints) {
    EXPECT_EQ(Bounds(1.0, 1.0, 1.0, 1.0).midpoints(),
        std::vector<Point<double>>({
            {1.5, 1.0},
            {1.0, 1.5},
            {2.0, 1.5},
            {1.5, 2.0},
        })
    );


    EXPECT_EQ(Bounds(1.0, 1.0, 2.0, 3.0).midpoints(),
        std::vector<Point<double>>({
            {2.0, 1.0},
            {1.0, 2.5},
            {3.0, 2.5},
            {2.0, 4.0},
        })
    );
}

TEST(Bounds, Segments) {
    EXPECT_EQ(
        Bounds(1.0, 1.0, 1.0, 1.0).segments(), 
        std::vector<Segment<double>>({
            {{1.0, 1.0}, {2.0, 1.0}},
            {{1.0, 1.0}, {1.0, 2.0}},
            {{2.0, 1.0}, {2.0, 2.0}},
            {{1.0, 2.0}, {2.0, 2.0}},
        })
     );
}

TEST(Bounds, Contains) {
    EXPECT_TRUE(Bounds(0.0, 0.0, 1.0, 1.0).contains({0.0, 0.0}));
    EXPECT_TRUE(Bounds(0.0, 0.0, 1.0, 1.0).contains({0.5, 0.5}));
    EXPECT_TRUE(Bounds(0.0, 0.0, 1.0, 1.0).contains({1.0, 1.0}));
    EXPECT_FALSE(Bounds(0.0, 0.0, 1.0, 1.0).contains({2.0, 2.0}));
}

TEST(Bounds, Overlaps) {
    EXPECT_TRUE(Bounds(0.0, 0.0, 1.0, 1.0).overlaps({0.0, 0.0, 1.0, 1.0}));
    EXPECT_TRUE(Bounds(0.0, 0.0, 1.0, 1.0).overlaps({0.5, 0.5, 1.0, 1.0}));
    EXPECT_TRUE(Bounds(0.0, 0.0, 1.0, 1.0).overlaps({1.0, 1.0, 1.0, 1.0}));
    EXPECT_FALSE(Bounds(0.0, 0.0, 1.0, 1.0).overlaps({2.0, 2.0, 1.0, 1.0}));
}

TEST(Bounds, Center) {
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).center(), Point<double>(0.5, 0.5));
    EXPECT_EQ(Bounds(1.0, 1.0, 1.0, 1.0).center(), Point<double>(1.5, 1.5));
    EXPECT_EQ(Bounds(1.0, 1.0, 2.0, 2.0).center(), Point<double>(2.0, 2.0));

    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).center({1.0, 1.0}), Bounds(0.0, 0.0,  1.0, 1.0));
    EXPECT_EQ(Bounds(1.0, 1.0, 1.0, 1.0).center({1.0, 1.0}), Bounds(1.0, 1.0,  1.0, 1.0));
    EXPECT_EQ(Bounds(1.0, 1.0, 2.0, 2.0).center({1.0, 1.0}), Bounds(1.5, 1.5,  1.0, 1.0));
}

TEST(Bounds, Rebase) {
    EXPECT_EQ(Bounds(1.0, 1.0, 10.0, 10.0).rebase(), Bounds(0.0, 0.0, 10.0, 10.0));
}

TEST(Bounds, Shift) {
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).shift({0.0, 0.0}), Bounds(0.0, 0.0, 1.0, 1.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).shift({1.0, 1.0}), Bounds(1.0, 1.0, 1.0, 1.0));
}

TEST(Bounds, Pad) {
    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).pad({2.0, 2.0}), Bounds(1.0, 1.0, 8.0, 8.0));
}

TEST(Bounds, Constrain) {
    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).constrain({5.0, 5.0}), Bounds(2.5, 2.5, 5.0, 5.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).constrain({2.0, 5.0}), Bounds(4.0, 2.5, 2.0, 5.0));

    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).constrain({20.0, 4.0}), Bounds(0.0, 4.0, 10.0, 2.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).constrain({4.0, 20.0}), Bounds(4.0, 0.0, 2.0, 10.0));

    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).constrain({20.0, 50.0}), Bounds( 3.0, 0.0, 4.0, 10.0));
}

TEST(Bounds, Align) {
    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).align({2.0, 2.0}, Alignment::Left), Bounds(0.0, 4.0, 2.0, 2.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).align({2.0, 2.0}, Alignment::Center), Bounds(4.0, 4.0, 2.0, 2.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 10.0, 10.0).align({2.0, 2.0}, Alignment::Right), Bounds(8.0, 4.0, 2.0, 2.0));

    EXPECT_EQ(Bounds(1.0, 1.0, 10.0, 10.0).align({4.0, 2.0}, Alignment::Left), Bounds(1.0, 5.0, 4.0, 2.0));
    EXPECT_EQ(Bounds(1.0, 1.0, 10.0, 10.0).align({4.0, 2.0}, Alignment::Center), Bounds(4.0, 5.0, 4.0, 2.0));
    EXPECT_EQ(Bounds(1.0, 1.0, 10.0, 10.0).align({4.0, 2.0}, Alignment::Right), Bounds(7.0, 5.0, 4.0, 2.0));
}

TEST(Bounds, Scale) {
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).scale(2.0), Bounds(-0.5, -0.5, 2.0, 2.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).scale({2.0, 4.0}), Bounds(-0.5, -1.5, 2.0, 4.0));
}

TEST(Bounds, ScaleAbout) {    
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).scale_about(1.0, {0.0, 0.0}), Bounds(0.0, 0.0, 1.0, 1.0));
    EXPECT_EQ(Bounds(1.0, 1.0, 1.0, 1.0).scale_about(2.0, {0.0, 0.0}), Bounds(2.0, 2.0, 2.0, 2.0));
    EXPECT_EQ(Bounds(1.0, 1.0, 1.0, 1.0).scale_about(2.0, {1.0, 1.0}), Bounds(1.0, 1.0, 2.0, 2.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).scale_about(2.0, {0.5, 0.5}), Bounds(-0.5, -0.5, 2.0, 2.0));

    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).scale_about({1.0, 2.0}, {0.0, 0.0}), Bounds(0.0, 0.0, 1.0, 2.0));
    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).scale_about({2.0, 4.0}, {0.5, 0.5}), Bounds(-0.5, -1.5, 2.0, 4.0));
}

TEST(Bounds, Slice) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 10.0, 10.0).slice({2, 4}, {0, 1}, {2, 4}),
        Bounds(5.0, 0.0, 5.0, 5.0)
    );
}

TEST(Bounds, SplitWidth) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 5.0, 5.0).split_width(2.0),
        std::pair(Bounds(0.0, 0.0, 2.0, 5.0), Bounds(2.0, 0.0, 3.0, 5.0))
    );
}

TEST(Bounds, SplitHeight) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 5.0, 5.0).split_height(2.0),
        std::pair(Bounds(0.0, 0.0, 5.0, 2.0), Bounds(0.0, 2.0, 5.0, 3.0))
    );
}

TEST(Bounds, Sample) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 10.0, 10.0).sample(1),
        std::vector({Point(5.0, 5.0)})
    );

    EXPECT_EQ(
        Bounds(0.0, 0.0, 10.0, 10.0).sample(2),
        std::vector({
            Point(0.0, 0.0),
            Point(0.0, 10.0),
            Point(10.0, 0.0),
            Point(10.0, 10.0),
        })
    );

    EXPECT_EQ(
        Bounds(1.0, 0.0, 10.0, 10.0).sample(3),
        std::vector({
            Point(1.0, 0.0),
            Point(1.0, 5.0),
            Point(1.0, 10.0),
            Point(6.0, 0.0),
            Point(6.0, 5.0),
            Point(6.0, 10.0),
            Point(11.0, 0.0),
            Point(11.0, 5.0),
            Point(11.0, 10.0),
        })
    );
}

TEST(Bounds, Rows) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 1.0, 3.0).rows(3),
        std::vector({
            Bounds(0.0, 0.0, 1.0, 1.0),
            Bounds(0.0, 1.0, 1.0, 1.0),
            Bounds(0.0, 2.0, 1.0, 1.0),
        })
    );
}

TEST(Bounds, Cols) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 3.0, 1.0).cols(3),
        std::vector({
            Bounds(0.0, 0.0, 1.0, 1.0),
            Bounds(1.0, 0.0, 1.0, 1.0),
            Bounds(2.0, 0.0, 1.0, 1.0),
        })
    );
}

TEST(Bounds, Tile) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 1.0, 1.0).tile({2, 2}),
        linear::Matrix<Bounds>({
            {{0.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 1.0}},
            {{0.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}},
        })
    );

    EXPECT_EQ(
        Bounds(0.0, 0.0, 1.0, 1.0).tile({2, 3}),
        linear::Matrix<Bounds>({
            {{0.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 1.0}, {2.0, 0.0, 1.0, 1.0}},
            {{0.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {2.0, 1.0, 1.0, 1.0}},
        })
    );

    EXPECT_EQ(Bounds(0.0, 0.0, 1.0, 1.0).tile({2, 2}, {1.0, 1.0}),
        linear::Matrix<Bounds>({
            {{0.0, 0.0, 1.0, 1.0}, {2.0, 0.0, 1.0, 1.0}},
            {{0.0, 2.0, 1.0, 1.0}, {2.0, 2.0, 1.0, 1.0}}
        })
    );
}

TEST(Bounds, Grid) {
    EXPECT_EQ(
        Bounds(0.0, 0.0, 10.0, 10.0).grid({4, 2}),
        linear::Matrix<Bounds>({
            {{0.0, 0.0, 5.0, 2.5}, {5.0, 0.0, 5.0, 2.5}},
            {{0.0, 2.5, 5.0, 2.5}, {5.0, 2.5, 5.0, 2.5}},
            {{0.0, 5.0, 5.0, 2.5}, {5.0, 5.0, 5.0, 2.5}},
            {{0.0, 7.5, 5.0, 2.5}, {5.0, 7.5, 5.0, 2.5}},
        })
    );

    EXPECT_EQ(
        Bounds(0.0, 0.0, 10.0, 10.0).grid({2, 4}),
        linear::Matrix<Bounds>({
            {{0.0, 0.0, 2.5, 5.0}, {2.5, 0.0, 2.5, 5.0}, {5.0, 0.0, 2.5, 5.0}, {7.5, 0.0, 2.5, 5.0}},
            {{0.0, 5.0, 2.5, 5.0}, {2.5, 5.0, 2.5, 5.0}, {5.0, 5.0, 2.5, 5.0}, {7.5, 5.0, 2.5, 5.0}},
        })
    );

    EXPECT_EQ(
        Bounds(0.0, 0.0, 10.0, 10.0).grid({2, 2}, {1.0, 1.0}, {1.0, 1.0}),
        linear::Matrix<Bounds>({
            {{2.0, 2.0, 2.0, 2.0}, {6.0, 2.0, 2.0, 2.0}},
            {{2.0, 6.0, 2.0, 2.0}, {6.0, 6.0, 2.0, 2.0}},
        })
    );
}
