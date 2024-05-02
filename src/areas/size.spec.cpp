#include "size.tpp"
#include "vector.tpp"
#include <gtest/gtest.h>

using namespace linear;

TEST(Size, Operators) {
    EXPECT_EQ(Size(1, 1) + Size(1, 1), Size(2, 2));

    EXPECT_EQ(Size(2, 2) - Size(1, 1), Size(1, 1));

    EXPECT_EQ(Size(1, 1) * 2, Size(2, 2));

    EXPECT_EQ(Size(1.0, 1.0) / 2, Size(0.5, 0.5));

    EXPECT_EQ(Size(2, 2) / 2, Size(1, 1));
    EXPECT_EQ(Size(1, 1) / 2, Size(0, 0));
}

TEST(Size, NonNegative) {
    EXPECT_EQ(Size(2, 2) - Size(10, 1), Size(0, 1));
    EXPECT_EQ(Size(1, 1) * -2, Size(0, 0));
}

TEST(Size, Repr) { EXPECT_EQ(Size(1, 1).repr(), "{width: 1, height: 1}"); }

TEST(Size, Empty) {
    EXPECT_TRUE(Size(0, 0).empty());

    EXPECT_FALSE(Size(0, 1).empty());
    EXPECT_FALSE(Size(1, 0).empty());
    EXPECT_FALSE(Size(1, 1).empty());
}

TEST(Size, Transpose) {
    EXPECT_EQ(Size(1, 1).transpose(), Size(1, 1));
    EXPECT_EQ(Size(1, 2).transpose(), Size(2, 1));
}

TEST(Size, Scale) {
    EXPECT_EQ(Size(1, 1).scale(1), Size(1, 1));
    EXPECT_EQ(Size(1, 1).scale(2), Size(2, 2));
    EXPECT_EQ(Size(1, 1).scale({2, 3}), Size(2, 3));
}
