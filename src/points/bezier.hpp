#ifndef PLANAR_POINTS_BEZIER_HPP
#define PLANAR_POINTS_BEZIER_HPP

#include "point.hpp"
#include <cstddef>
#include <functional>
#include <string>
#include <vector>

namespace linear {
    template <typename T>
    class Size;

    class Bezier {
      public:
        Point<double> p1;
        Point<double> p2;
        Point<double> p3;
        Point<double> p4;

        Bezier(const Point<double> &p1, const Point<double> &p2, const Point<double> &p3, const Point<double> &p4);

        explicit Bezier(const std::vector<Point<double>> &points);

        bool operator==(const Bezier &rhs) const;
        bool operator!=(const Bezier &rhs) const;

        std::string repr() const;

        Point<double> point(double t) const;

        std::vector<Point<double>> sample(size_t n) const;

        Bezier shift(const Size<double> &offset) const;

        Bezier transform(const std::function<Point<double>(const Point<double> &)> &map) const;

        double square_error(const std::vector<Point<double>> &points) const;
    };
}

#endif
