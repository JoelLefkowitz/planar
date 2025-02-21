#ifndef PLANAR_POINTS_POINT_HPP
#define PLANAR_POINTS_POINT_HPP

#include "../linear/vector.hpp"
#include <string>
#include <vector>

namespace planar {
    template <typename T>
    class Size;

    template <typename T>
    class Point {
      public:
        Vector<T> point;

        Point();
        Point(T x, T y);

        explicit Point(const Vector<T> &point);

        bool operator==(const Point<T> &rhs) const;
        bool operator!=(const Point<T> &rhs) const;
        bool operator<(const Point<T> &rhs) const;
        bool operator>(const Point<T> &rhs) const;
        bool operator<=(const Point<T> &rhs) const;
        bool operator>=(const Point<T> &rhs) const;

        Point<T> operator+(const Vector<T> &rhs) const;
        Point<T> operator-(const Vector<T> &rhs) const;

        Point<T> operator+(const Size<T> &rhs) const;
        Point<T> operator-(const Size<T> &rhs) const;

        std::string repr() const;

        T x() const;
        T y() const;

        bool zero() const;

        Point<T> scale(T factor) const;
        Point<T> scale(const Size<T> &factor) const;

        Point<T> flip(const Point<T> &origin) const;
        Point<T> flip_x(T origin) const;
        Point<T> flip_y(T origin) const;

        Point<T> shift(const Size<T> &size) const;

        Point<T> center(const Size<T> &size) const;

        Point<T> center_horizontal(const Size<T> &size) const;
        Point<T> center_vertical(const Size<T> &size) const;

        Size<T> projection() const;

        static std::vector<Point<T>> linspace(const std::vector<T> &heights, T start, T end);
    };
}

#endif
