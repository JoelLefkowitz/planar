#ifndef PLANAR_LINEAR_MATRIX_HPP
#define PLANAR_LINEAR_MATRIX_HPP

#include <cstddef>
#include <vector>

namespace linear {
    class Dimensions;
    class Slice;

    template <typename T>
    class Point;

    template <typename T>
    class Matrix {
      private:
        std::vector<std::vector<T>> content;

      public:
        explicit Matrix(const std::vector<std::vector<T>> &content = {});

        Matrix(const std::vector<T> &flat, size_t size);

        bool operator==(const Matrix<T> &rhs) const;
        bool operator!=(const Matrix<T> &rhs) const;

        Dimensions size() const;

        bool empty() const;

        void clear();

        T get(const Point<size_t> &point) const;

        Matrix<T> slice(const linear::Slice &rows, const linear::Slice &cols) const;

        T sum() const;
    };
}

#endif
