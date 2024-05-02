#ifndef PLANAR_AREAS_SIZE_HPP
#define PLANAR_AREAS_SIZE_HPP

#include "vector.hpp"

namespace linear {
    template <typename T>
    class Size {
      public:
        Vector<T> size;

        Size();
        Size(T w, T h);

        explicit Size(const Vector<T> &size);

        bool operator==(const Size<T> &rhs) const;
        bool operator!=(const Size<T> &rhs) const;
        bool operator<(const Size<T> &rhs) const;
        bool operator>(const Size<T> &rhs) const;
        bool operator<=(const Size<T> &rhs) const;
        bool operator>=(const Size<T> &rhs) const;

        Size<T> operator+(const Size<T> &rhs) const;
        Size<T> operator-(const Size<T> &rhs) const;
        Size<T> operator*(const T &rhs) const;
        Size<T> operator/(const T &rhs) const;

        std::string repr() const;

        T width() const;
        T height() const;

        bool empty() const;

        Size<T> transpose() const;

        Size<T> scale(T factor) const;
        Size<T> scale(const Size<T> &factor) const;
    };
}

#endif
