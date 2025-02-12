#include "bezier.hpp"
#include "../areas/bounds.hpp"
#include "../areas/size.tpp"
#include "../linear/vector.tpp"
#include "point.tpp"
#include <algorithm>
#include <cmath>
#include <fmt/core.h>
#include <functional/generics/functor/map.tpp>
#include <functional/implementations/vectors/ranges.tpp>

linear::Bezier::Bezier(
    const linear::Point<double> &p1,
    const linear::Point<double> &p2,
    const linear::Point<double> &p3,
    const linear::Point<double> &p4
)
    : p1(p1)
    , p2(p2)
    , p3(p3)
    , p4(p4) {}

linear::Bezier::Bezier(const std::vector<Point<double>> &points) {
    if (points.size() < 2) {
        return;
    }

    p1 = points.front();
    p4 = points.back();

    p2 = p1;
    p3 = p4;

    auto grid  = Bounds::enclose(points).scale({1, 1.5}).sample(5);
    auto error = square_error(points);

    auto best_p2    = p1;
    auto best_p3    = p4;
    auto best_error = error;

    for (const auto &i : grid) {
        for (const auto &j : grid) {
            p2 = i;
            p3 = j;

            auto current_error = square_error(points);

            if (current_error < best_error) {
                best_p2    = p2;
                best_p3    = p3;
                best_error = current_error;
            };
        }
    }

    p2 = best_p2;
    p3 = best_p3;
}

bool linear::Bezier::operator==(const Bezier &rhs) const {
    return p1 == rhs.p1 && p2 == rhs.p2 && p3 == rhs.p3 && p4 == rhs.p4;
}

bool linear::Bezier::operator!=(const Bezier &rhs) const { return !(*this == rhs); }

std::string linear::Bezier::repr() const {
    return fmt::format("[{}, {}, {}, {}]", p1.repr(), p2.repr(), p3.repr(), p4.repr());
}

linear::Point<double> linear::Bezier::point(double t) const {
    auto term = [t](auto i, auto j) { return std::pow((1 - t), i) * std::pow(t, j); };

    auto cube = [&term](auto q1, auto q2, auto q3, auto q4) {
        return q1 * term(3, 0) + q2 * 3 * term(2, 1) + q3 * 3 * term(1, 2) + q4 * term(0, 3);
    };

    return {
        cube(p1.x(), p2.x(), p3.x(), p4.x()),
        cube(p1.y(), p2.y(), p3.y(), p4.y()),
    };
}

std::vector<linear::Point<double>> linear::Bezier::sample(size_t n) const {
    std::function<Point<double>(double)> point = [this](auto t) { return this->point(t); };
    return functional::map(point, functional::linspace(0.0, 1.0, n));
}

linear::Bezier linear::Bezier::shift(const linear::Size<double> &offset) const {
    return {
        p1 + offset,
        p2 + offset,
        p3 + offset,
        p4 + offset,
    };
}

linear::Bezier linear::Bezier::transform(const std::function<linear::Point<double>(const linear::Point<double> &)> &map
) const {
    return {
        map(p1),
        map(p2),
        map(p3),
        map(p4),
    };
}

double linear::Bezier::square_error(const std::vector<Point<double>> &points) const {
    auto copy = points;
    std::sort(copy.begin(), copy.end());

    double error = 0;

    for (const auto t : functional::linspace(0.0, 1.0, 100)) {
        auto projection = point(1 - t);

        while (!copy.empty() && projection.x() <= copy.back().x()) {
            error += std::pow(projection.y() - copy.back().y(), 2);
            copy.pop_back();
        }
    }

    return error;
}
