#ifndef PLANAR_LINEAR_MATRIX_TPP
#define PLANAR_LINEAR_MATRIX_TPP

#include "../areas/size.tpp"
#include "../points/point.tpp"
#include "../scalar/dimensions.hpp"
#include "../scalar/slice.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <functional/generics/foldable/fold.tpp>
#include <functional/generics/functor/map.tpp>
#include <functional/implementations/vectors/elements.tpp>
#include <functional/implementations/vectors/immutable.tpp>
#include <functional/implementations/vectors/mutable.tpp>
#include <functional/implementations/vectors/ranges.tpp>
#include <vector>

template <typename T>
linear::Matrix<T>::Matrix(const std::vector<std::vector<T>> &content) : content(content) {
}

template <typename T>
linear::Matrix<T>::Matrix(const std::vector<T> &flat, size_t size) {
    size_t rows = flat.size() / size;

    std::function<std::vector<T>(size_t)> chunk = [&flat, size](auto x) {
        return functional::slice(flat, x * size, (x + 1) * size);
    };

    content = functional::map(chunk, functional::range(rows));
}

template <typename T>
bool linear::Matrix<T>::operator==(const Matrix<T> &rhs) const {
    return content == rhs.content;
}

template <typename T>
bool linear::Matrix<T>::operator!=(const Matrix<T> &rhs) const {
    return content != rhs.content;
}

template <typename T>
linear::Dimensions linear::Matrix<T>::size() const {
    return {content.size(), content.empty() ? 0 : content[0].size()};
}

template <typename T>
bool linear::Matrix<T>::empty() const {
    return content.empty();
}

template <typename T>
void linear::Matrix<T>::clear() {
    content.clear();
}

template <typename T>
T linear::Matrix<T>::get(const Point<size_t> &point) const {
    return content.at(point.y()).at(point.x());
}

template <typename T>
linear::Matrix<T> linear::Matrix<T>::slice(const linear::Slice &rows, const linear::Slice &cols) const {
    std::function<std::vector<T>(const std::vector<T> &)> fixed_slice = [&cols](const auto &inner) {
        return functional::slice(inner, cols.start, cols.end);
    };

    return linear::Matrix<T>(functional::map(fixed_slice, functional::slice(content, rows.start, rows.end)));
}

template <typename T>
T linear::Matrix<T>::sum() const {
    std::function<T(T, T)> add = [](auto acc, auto x) {
        return acc + x;
    };

    std::function<T(T, std::vector<T>)> sum = [&add](auto acc, auto x) {
        return acc + functional::fold(add, T(), x);
    };

    return functional::fold(sum, T(), content);
}

#endif
