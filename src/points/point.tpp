#ifndef PLANAR_POINTS_POINT_TPP
#define PLANAR_POINTS_POINT_TPP

#include "../areas/size.tpp"
#include "../linear/vector.tpp"
#include "point.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <functional>
#include <funky/generics/iterables.tpp>
#include <funky/generics/mutable.tpp>
#include <funky/generics/pairs.tpp>

template <typename T>
planar::Point<T>::Point() : point({0, 0}) {
}

template <typename T>
planar::Point<T>::Point(T x, T y) : point({x, y}) {
}

template <typename T>
planar::Point<T>::Point(const Vector<T> &point) : point(point) {
}

template <typename T>
bool planar::Point<T>::operator==(const Point<T> &rhs) const {
    return point == rhs.point;
}

template <typename T>
bool planar::Point<T>::operator!=(const Point<T> &rhs) const {
    return point != rhs.point;
}

template <typename T>
bool planar::Point<T>::operator<(const Point<T> &rhs) const {
    return point < rhs.point;
}

template <typename T>
bool planar::Point<T>::operator>(const Point<T> &rhs) const {
    return point > rhs.point;
}

template <typename T>
bool planar::Point<T>::operator<=(const Point<T> &rhs) const {
    return point <= rhs.point;
}

template <typename T>
bool planar::Point<T>::operator>=(const Point<T> &rhs) const {
    return point >= rhs.point;
}

template <typename T>
planar::Point<T> planar::Point<T>::operator+(const Vector<T> &rhs) const {
    return Point(point + rhs);
}

template <typename T>
planar::Point<T> planar::Point<T>::operator-(const Vector<T> &rhs) const {
    return Point(point - rhs);
}

template <typename T>
planar::Point<T> planar::Point<T>::operator+(const Size<T> &rhs) const {
    return Point(point + rhs.size);
}

template <typename T>
planar::Point<T> planar::Point<T>::operator-(const Size<T> &rhs) const {
    return Point(point - rhs.size);
}

template <typename T>
std::string planar::Point<T>::repr() const {
    return fmt::format("{{x: {}, y: {}}}", point.x, point.y);
}

template <typename T>
T planar::Point<T>::x() const {
    return point.x;
}

template <typename T>
T planar::Point<T>::y() const {
    return point.y;
}

template <typename T>
bool planar::Point<T>::zero() const {
    return point.x == 0 && point.y == 0;
}

template <typename T>
planar::Point<T> planar::Point<T>::scale(T factor) const {
    return scale({factor, factor});
}

template <typename T>
planar::Point<T> planar::Point<T>::scale(const Size<T> &factor) const {
    return {point.x * factor.width(), point.y * factor.height()};
}

template <typename T>
planar::Point<T> planar::Point<T>::flip(const Point<T> &origin) const {
    return {2 * origin.x() - point.x, 2 * origin.y() - point.y};
}

template <typename T>
planar::Point<T> planar::Point<T>::flip_x(T origin) const {
    return {2 * origin - point.x, point.y};
}

template <typename T>
planar::Point<T> planar::Point<T>::flip_y(T origin) const {
    return {point.x, 2 * origin - point.y};
}

template <typename T>
planar::Point<T> planar::Point<T>::shift(const Size<T> &size) const {
    return {point.x + size.width(), point.y + size.height()};
}

template <typename T>
planar::Point<T> planar::Point<T>::center(const Size<T> &size) const {
    auto width  = static_cast<T>(size.width());
    auto height = static_cast<T>(size.height());
    return shift({-width / 2, -height / 2});
}

template <typename T>
planar::Point<T> planar::Point<T>::center_horizontal(const Size<T> &size) const {
    return center({size.width(), 0});
}

template <typename T>
planar::Point<T> planar::Point<T>::center_vertical(const Size<T> &size) const {
    return center({0, size.height()});
}

template <typename T>
planar::Size<T> planar::Point<T>::projection() const {
    return Size<T>(point);
}

template <typename T>
std::vector<planar::Point<T>> planar::Point<T>::linspace(const std::vector<T> &heights, T start, T end) {
    if (heights.empty()) {
        return {};
    }

    if (heights.size() == 1) {
        return {Point<T>((end - start) / 2, heights[0])};
    }

    auto spaces = static_cast<double>((heights.size() - 1));
    auto spread = (end - start) / spaces;

    return funky::map<std::vector<Point<T>>>(
        [start, spread](auto pair) {
            auto size = static_cast<double>(pair.first);
            return Point<T>(start + spread * size, pair.second);
        },
        funky::zip(funky::range(heights.size()), heights)
    );
}

#endif
