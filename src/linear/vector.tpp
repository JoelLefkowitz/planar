#ifndef PLANAR_LINEAR_VECTOR_TPP
#define PLANAR_LINEAR_VECTOR_TPP

#include "vector.hpp"
#include <cmath>
#include <fmt/core.h>
#include <string>

template <typename T>
planar::Vector<T>::Vector(T x, T y) : x(x)
                                    , y(y) {
}

template <typename T>
bool planar::Vector<T>::operator==(const Vector<T> &rhs) const {
    return x == rhs.x && y == rhs.y;
}

template <typename T>
bool planar::Vector<T>::operator!=(const Vector<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T>
bool planar::Vector<T>::operator<(const Vector<T> &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
}

template <typename T>
bool planar::Vector<T>::operator>(const Vector<T> &rhs) const {
    return rhs < *this;
}

template <typename T>
bool planar::Vector<T>::operator<=(const Vector<T> &rhs) const {
    return !(rhs < *this);
}

template <typename T>
bool planar::Vector<T>::operator>=(const Vector<T> &rhs) const {
    return !(*this < rhs);
}

template <typename T>
planar::Vector<T> planar::Vector<T>::operator+(const Vector<T> &rhs) const {
    return {x + rhs.x, y + rhs.y};
}

template <typename T>
planar::Vector<T> planar::Vector<T>::operator-(const Vector<T> &rhs) const {
    return {x - rhs.x, y - rhs.y};
}

template <typename T>
planar::Vector<T> planar::Vector<T>::operator*(const T &rhs) const {
    return {x * rhs, y * rhs};
}

template <typename T>
planar::Vector<T> planar::Vector<T>::operator/(const T &rhs) const {
    return {x / rhs, y / rhs};
}

template <typename T>
std::string planar::Vector<T>::repr() const {
    return fmt::format("{{x: {}, y: {}}}", x, y);
}

template <typename T>
double planar::Vector<T>::magnitude() const {
    return std::pow(std::pow(x, 2) + std::pow(y, 2), 0.5);
}

#endif
