#ifndef PLANAR_AREAS_BOUNDS_HPP
#define PLANAR_AREAS_BOUNDS_HPP

#include "point.hpp"
#include "size.tpp"
#include "vector.tpp"
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace linear {
    enum class Alignment {
        Left,
        Center,
        Right,
    };

    class Dimensions;
    class Slice;

    template <typename T>
    class Matrix;

    template <typename T>
    class Segment;

    class Bounds {
      public:
        Point<double> point;
        Size<double>  size;

        static Bounds enclose(const std::vector<Point<double>> &points);

        Bounds();
        Bounds(double x, double y, double w, double h);

        Bounds(const Point<int> &point, const Size<int> &size);
        Bounds(const Point<double> &point, const Size<double> &size);

        explicit Bounds(const std::vector<Bounds> &bounds);
        explicit Bounds(const Matrix<Bounds> &bounds);

        bool operator==(const Bounds &rhs) const;
        bool operator!=(const Bounds &rhs) const;
        bool operator<(const Bounds &rhs) const;
        bool operator>(const Bounds &rhs) const;
        bool operator<=(const Bounds &rhs) const;
        bool operator>=(const Bounds &rhs) const;

        Bounds operator*(const double &rhs) const;
        Bounds operator/(const double &rhs) const;

        Bounds operator+(const Size<double> &rhs) const;
        Bounds operator-(const Size<double> &rhs) const;

        std::string repr() const;

        bool empty() const;

        std::vector<Point<double>> corners() const;
        std::vector<Point<double>> midpoints() const;

        std::vector<Segment<double>> segments() const;

        bool contains(const Point<double> &rhs) const;
        bool overlaps(const Bounds &bounds) const;

        Point<double> center() const;
        Bounds        center(const Size<double> &region) const;

        Bounds rebase() const;

        Bounds shift(const Size<double> &move) const;

        Bounds pad(const Size<double> &border) const;

        Bounds constrain(const Size<double> &limits) const;
        Bounds align(const Size<double> &region, Alignment alignment) const;

        Bounds scale(const double &factor) const;
        Bounds scale(const Size<double> &factor) const;

        Bounds scale_about(const double &factor, const Point<double> &origin) const;
        Bounds scale_about(const Size<double> &factor, const Point<double> &origin) const;

        Bounds slice(const Dimensions &dimensions, const linear::Slice &rows, const linear::Slice &cols) const;

        std::pair<Bounds, Bounds> split_width(double x) const;
        std::pair<Bounds, Bounds> split_height(double y) const;

        std::vector<Point<double>> sample(size_t side) const;

        std::vector<Bounds> rows(size_t n) const;
        std::vector<Bounds> cols(size_t n) const;

        Matrix<Bounds> tile(const Dimensions &dimensions, const Size<double> &padding = {0.0, 0.0}) const;

        Matrix<Bounds> grid(
            const Dimensions   &dimensions,
            const Size<double> &padding = {0.0, 0.0},
            const Size<double> &margin  = {0.0, 0.0}
        ) const;
    };
}

#endif
