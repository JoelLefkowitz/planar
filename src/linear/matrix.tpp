#ifndef PLANAR_LINEAR_MATRIX_TPP
#define PLANAR_LINEAR_MATRIX_TPP

#include "../areas/size.tpp"
#include "../points/point.tpp"
#include "../scalar/dimensions.hpp"
#include "../scalar/slice.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <funky/generics/iterables.tpp>
#include <vector>

template <typename T>
planar::Matrix<T>::Matrix(const std::vector<std::vector<T>> &content) : content(content) {
}

template <typename T>
planar::Matrix<T>::Matrix(const std::vector<T> &flat, size_t size) {
    size_t rows = flat.size() / size;

    std::function<std::vector<T>(size_t)> chunk = [&flat, size](auto x) {
        return funky::slice(flat, x * size, (x + 1) * size);
    };

    content = funky::map<std::vector<std::vector<T>>>(chunk, funky::range(rows));
}

template <typename T>
bool planar::Matrix<T>::operator==(const Matrix<T> &rhs) const {
    return content == rhs.content;
}

template <typename T>
bool planar::Matrix<T>::operator!=(const Matrix<T> &rhs) const {
    return content != rhs.content;
}

template <typename T>
planar::Dimensions planar::Matrix<T>::size() const {
    return {content.size(), content.empty() ? 0 : content[0].size()};
}

template <typename T>
bool planar::Matrix<T>::empty() const {
    return content.empty();
}

template <typename T>
void planar::Matrix<T>::clear() {
    content.clear();
}

template <typename T>
T planar::Matrix<T>::get(const Point<size_t> &point) const {
    return content.at(point.y()).at(point.x());
}

template <typename T>
planar::Matrix<T> planar::Matrix<T>::slice(const planar::Slice &rows, const planar::Slice &cols) const {
    std::function<std::vector<T>(const std::vector<T> &)> fixed_slice = [&cols](const auto &inner) {
        return funky::slice(inner, cols.start, cols.end);
    };

    return planar::Matrix<T>(
        funky::map<std::vector<std::vector<T>>>(fixed_slice, funky::slice(content, rows.start, rows.end))
    );
}

template <typename T>
T planar::Matrix<T>::sum() const {
    std::function<T(T, T)> add = [](auto acc, auto x) {
        return acc + x;
    };

    std::function<T(T, std::vector<T>)> sum = [&add](auto acc, auto x) {
        return acc + funky::fold(add, T(), x);
    };

    return funky::fold(sum, T(), content);
}

#endif
