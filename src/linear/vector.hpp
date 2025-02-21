#ifndef PLANAR_LINEAR_VECTOR_HPP
#define PLANAR_LINEAR_VECTOR_HPP

#include <string>

namespace planar {
    template <typename T>
    class Vector {
      public:
        T x;
        T y;

        Vector(T x, T y);

        bool operator==(const Vector<T> &rhs) const;
        bool operator!=(const Vector<T> &rhs) const;
        bool operator<(const Vector<T> &rhs) const;
        bool operator>(const Vector<T> &rhs) const;
        bool operator<=(const Vector<T> &rhs) const;
        bool operator>=(const Vector<T> &rhs) const;

        Vector<T> operator+(const Vector<T> &rhs) const;
        Vector<T> operator-(const Vector<T> &rhs) const;
        Vector<T> operator*(const T &rhs) const;
        Vector<T> operator/(const T &rhs) const;

        std::string repr() const;

        double magnitude() const;
    };
}

#endif
