#ifndef PLANAR_AREAS_SIZE_TPP
#define PLANAR_AREAS_SIZE_TPP

#include "../linear/vector.hpp"
#include "size.hpp"
#include <algorithm>
#include <fmt/core.h>

template <typename T>
planar::Size<T>::Size() : size({0, 0}) {
}

template <typename T>
planar::Size<T>::Size(T w, T h) : size({w, h}) {
}

template <typename T>
planar::Size<T>::Size(const Vector<T> &size) : size(size) {
}

template <typename T>
bool planar::Size<T>::operator==(const Size<T> &rhs) const {
    return size == rhs.size;
}

template <typename T>
bool planar::Size<T>::operator!=(const Size<T> &rhs) const {
    return size != rhs.size;
}

template <typename T>
bool planar::Size<T>::operator<(const Size<T> &rhs) const {
    return size < rhs.size;
}

template <typename T>
bool planar::Size<T>::operator>(const Size<T> &rhs) const {
    return size > rhs.size;
}

template <typename T>
bool planar::Size<T>::operator<=(const Size<T> &rhs) const {
    return size <= rhs.size;
}

template <typename T>
bool planar::Size<T>::operator>=(const Size<T> &rhs) const {
    return size >= rhs.size;
}

template <typename T>
planar::Size<T> planar::Size<T>::operator+(const Size<T> &rhs) const {
    return Size<T>(size + rhs.size);
}

template <typename T>
planar::Size<T> planar::Size<T>::operator-(const Size<T> &rhs) const {
    auto difference = size - rhs.size;
    return {std::max(difference.x, T()), std::max(difference.y, T())};
}

template <typename T>
planar::Size<T> planar::Size<T>::operator*(const T &rhs) const {
    auto scaled = size * rhs;
    return {std::max(scaled.x, T()), std::max(scaled.y, T())};
}

template <typename T>
planar::Size<T> planar::Size<T>::operator/(const T &rhs) const {
    auto scaled = size / rhs;
    return {std::max(scaled.x, T()), std::max(scaled.y, T())};
}

template <typename T>
std::string planar::Size<T>::repr() const {
    return fmt::format("{{width: {}, height: {}}}", size.x, size.y);
}

template <typename T>
T planar::Size<T>::width() const {
    return size.x;
}

template <typename T>
T planar::Size<T>::height() const {
    return size.y;
}

template <typename T>
bool planar::Size<T>::empty() const {
    return size.x == 0 && size.y == 0;
}

template <typename T>
planar::Size<T> planar::Size<T>::transpose() const {
    return {size.y, size.x};
}

template <typename T>
planar::Size<T> planar::Size<T>::scale(T factor) const {
    return scale({factor, factor});
}

template <typename T>
planar::Size<T> planar::Size<T>::scale(const Size<T> &factor) const {
    return {size.x * factor.size.x, size.y * factor.size.y};
}

#endif
