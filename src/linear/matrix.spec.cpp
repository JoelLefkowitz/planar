#include "matrix.tpp"
#include "point.tpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

using namespace linear;

// clang-format off
TEST(Matrix, Chunk) {
    EXPECT_EQ(
        Matrix<int>(functional::range(0, 6), 2),
        Matrix<int>({{0, 1}, {2, 3}, {4, 5}})
    );

    EXPECT_EQ(
        Matrix<int>(functional::range(0, 6), 3),
        Matrix<int>({{0, 1, 2}, {3, 4, 5}})
    );
}

TEST(Matrix, Size) {
    EXPECT_EQ(Matrix<int>().size(), Dimensions(0, 0));
    EXPECT_EQ(Matrix<int>({{0, 0}}).size(), Dimensions(1, 2));

    EXPECT_EQ(
        Matrix<int>({{0, 0}, {0, 0}}).size(), 
        Dimensions(2, 2)
    );
}


TEST(Matrix, Get) {
    Matrix<int> grid({{0, 1}, {2, 3}});
    EXPECT_EQ(grid.get({0, 0}), 0);
    EXPECT_EQ(grid.get({1, 0}), 1);
    EXPECT_EQ(grid.get({0, 1}), 2);
    EXPECT_EQ(grid.get({1, 1}), 3);
}

TEST(Matrix, Slice) {
    Matrix<int> grid({
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
    });

    EXPECT_EQ(
        grid.slice({0, 2}, {0, 2}), 
        Matrix<int>({
            {0, 0},
            {0, 1}
        })
    );
    
    EXPECT_EQ(
        grid.slice({0, 3}, {0, 2}), 
        Matrix<int>({
            {0, 0},
            {0, 1},
            {0, 1}
        })
    );

    EXPECT_EQ(
        grid.slice({0, 2}, {0, 3}),
        Matrix<int>({
            {0, 0, 0},
            {0, 1, 1}
        })
    );

    EXPECT_EQ(
        grid.slice({1, 3}, {1, 4}),
        Matrix<int>({
            {1, 1, 1},
            {1, 1, 1}
        })
    );
}

TEST(Matrix, Sum) {
    Matrix<int> grid({
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    });

    EXPECT_EQ(grid.sum(), 24);
}
