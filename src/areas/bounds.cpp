#include "bounds.hpp"
#include "../areas/size.tpp"
#include "../linear/matrix.tpp"
#include "../points/point.tpp"
#include "../points/segment.tpp"
#include "../scalar/dimensions.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <functional/generics/functor/map.tpp>
#include <functional/generics/functor/product.tpp>
#include <functional/implementations/booleans/booleans.tpp>
#include <functional/implementations/vectors/elements.tpp>
#include <functional/implementations/vectors/immutable.tpp>
#include <functional/implementations/vectors/ranges.tpp>
#include <functional>
#include <string>
#include <vector>

linear::Bounds::Bounds() : point(0, 0), size(0, 0) {}

linear::Bounds::Bounds(double x, double y, double w, double h) : point(Point(x, y)), size(Size(w, h)) {}

linear::Bounds::Bounds(const Point<int> &point, const Size<int> &size)
    : point(Point<double>(point.x(), point.y()))
    , size(Size<double>(size.width(), size.height())) {}

linear::Bounds::Bounds(const Point<double> &point, const Size<double> &size) : point(point), size(size) {}

linear::Bounds::Bounds(const std::vector<Bounds> &bounds) {
    using F = std::function<Point<double>(const Bounds &)>;

    F left  = [](const auto &x) { return x.point; };
    F right = [](const auto &x) { return x.point + x.size; };

    auto interval = enclose(functional::concat(functional::map(left, bounds), functional::map(right, bounds)));

    point = interval.point;
    size  = interval.size;
}

linear::Bounds::Bounds(const Matrix<Bounds> &bounds) {
    auto limits = bounds.size();

    auto first = bounds.get({0, 0});
    auto last  = bounds.get({limits.cols - 1, limits.rows - 1});

    point = first.point;
    size  = last.point.projection() - first.point.projection() + last.size;
}

linear::Bounds linear::Bounds::enclose(const std::vector<Point<double>> &points) {
    std::function<double(Point<double>)> x = [](const auto &p) { return p.x(); };
    std::function<double(Point<double>)> y = [](const auto &p) { return p.y(); };

    Point<double> point(functional::min(functional::map(x, points)), functional::min(functional::map(y, points)));

    Size<double> size(
        functional::max(functional::map(x, points)) - point.x(),
        functional::max(functional::map(y, points)) - point.y()
    );

    return {point, size};
}

bool linear::Bounds::operator==(const Bounds &rhs) const { return point == rhs.point && size == rhs.size; }

bool linear::Bounds::operator!=(const Bounds &rhs) const { return !(*this == rhs); }

bool linear::Bounds::operator<(const Bounds &rhs) const {
    return point < rhs.point || (point == rhs.point && size < rhs.size);
}

bool linear::Bounds::operator>(const Bounds &rhs) const { return rhs < *this; }

bool linear::Bounds::operator<=(const Bounds &rhs) const { return !(rhs < *this); }

bool linear::Bounds::operator>=(const Bounds &rhs) const { return !(*this < rhs); }

linear::Bounds linear::Bounds::operator+(const linear::Size<double> &rhs) const { return {point, size + rhs}; }

linear::Bounds linear::Bounds::operator-(const linear::Size<double> &rhs) const { return {point, size - rhs}; }

linear::Bounds linear::Bounds::operator*(const double &rhs) const { return {point, size * rhs}; }

linear::Bounds linear::Bounds::operator/(const double &rhs) const { return {point, size / rhs}; }

std::string linear::Bounds::repr() const { return fmt::format("{{{}, {}}}", point.repr(), size.repr()); }

bool linear::Bounds::empty() const { return size.empty(); }

std::vector<linear::Point<double>> linear::Bounds::corners() const {
    return {
        point,
        point + Size<double>(size.width(), 0),
        point + Size<double>(0, size.height()),
        point + size,
    };
}

std::vector<linear::Point<double>> linear::Bounds::midpoints() const {
    return {
        point + Size<double>(size.width() / 2, 0),
        point + Size<double>(0, size.height() / 2),
        point + Size(size.width(), size.height() / 2),
        point + Size(size.width() / 2, size.height()),
    };
}

std::vector<linear::Segment<double>> linear::Bounds::segments() const {
    auto points = corners();
    return {
        {points[0], points[1]},
        {points[0], points[2]},
        {points[1], points[3]},
        {points[2], points[3]},
    };
}

bool linear::Bounds::contains(const Point<double> &rhs) const {
    auto upper = point + size;
    return functional::all(std::vector<bool>({
        point.x() <= rhs.x(),
        point.y() <= rhs.y(),
        rhs.x() <= upper.x(),
        rhs.y() <= upper.y(),
    }));
}

bool linear::Bounds::overlaps(const Bounds &bounds) const {
    std::function<bool(const Point<double> &x)> contains_corner = [&bounds](const auto &x) {
        return bounds.contains(x);
    };

    return functional::any(contains_corner, corners());
}

linear::Point<double> linear::Bounds::center() const { return point + size / 2; }

linear::Bounds linear::Bounds::center(const Size<double> &region) const { return align(region, Alignment::Center); }

linear::Bounds linear::Bounds::rebase() const { return {0, 0, size.width(), size.height()}; }

linear::Bounds linear::Bounds::shift(const Size<double> &move) const { return {point + move, size}; }

linear::Bounds linear::Bounds::pad(const Size<double> &border) const { return {point + border / 2, size - border}; }

linear::Bounds linear::Bounds::constrain(const Size<double> &limits) const {
    auto w = limits.width();
    auto h = limits.height();

    auto W = size.width();
    auto H = size.height();

    if (w <= W && h <= H) {
        return center(limits);
    }

    Size<double> narrow(H * w / h, H);
    Size<double> wide(W, W * h / w);

    return center((H * w / h) < w && H < h ? narrow : wide);
}

linear::Bounds linear::Bounds::align(const Size<double> &region, Alignment alignment) const {
    auto steps = 0;

    auto w = region.width();
    auto h = region.height();

    if (alignment == Alignment::Center) {
        steps = 1;
    }

    if (alignment == Alignment::Right) {
        steps = 2;
    }

    return {point.x() + steps * (size.width() - w) / 2, point.y() + (size.height() - h) / 2, w, h};
}

linear::Bounds linear::Bounds::scale(const double &factor) const { return scale({factor, factor}); }

linear::Bounds linear::Bounds::scale(const Size<double> &factor) const { return scale_about(factor, center()); }

linear::Bounds linear::Bounds::scale_about(const double &factor, const Point<double> &origin) const {
    return scale_about({factor, factor}, origin);
}

linear::Bounds linear::Bounds::scale_about(const Size<double> &factor, const Point<double> &origin) const {
    auto x = factor.width() * point.x() + (1 - factor.width()) * origin.x();
    auto y = factor.height() * point.y() + (1 - factor.height()) * origin.y();
    return {
        {x, y},
        size.scale(factor)
    };
}

linear::Bounds linear::Bounds::slice(const Dimensions &dimensions, const linear::Slice &rows, const linear::Slice &cols)
    const {
    return Bounds(grid(dimensions).slice(rows, cols));
}

std::pair<linear::Bounds, linear::Bounds> linear::Bounds::split_width(double x) const {
    return {
        Bounds(point, Size<double>(x, size.height())),
        Bounds(point + Size<double>(x, 0), size - Size<double>(x, 0)),
    };
}

std::pair<linear::Bounds, linear::Bounds> linear::Bounds::split_height(double y) const {
    return {
        Bounds(point, Size<double>(size.width(), y)),
        Bounds(point + Size<double>(0, y), size - Size<double>(0, y)),
    };
}

std::vector<linear::Point<double>> linear::Bounds::sample(size_t side) const {
    if (side == 1) {
        return {center()};
    }

    std::function<Point<double>(double, double)> pair = [](auto x, auto y) { return Point<double>(x, y); };

    return functional::product(
        pair,
        functional::linspace(point.x(), point.x() + size.width(), side),
        functional::linspace(point.y(), point.y() + size.height(), side)
    );
}

std::vector<linear::Bounds> linear::Bounds::rows(size_t n) const {
    linear::Size<double> segment(size.width(), size.height() / static_cast<double>(n));

    std::function<linear::Bounds(size_t)> split = [&segment, &point = point](auto i) {
        linear::Point<double> row(point.x(), point.y() + segment.height() * static_cast<double>(i));
        return linear::Bounds(row, segment);
    };

    return functional::map(split, functional::range(n));
}

std::vector<linear::Bounds> linear::Bounds::cols(size_t n) const {
    linear::Size<double> segment(size.width() / static_cast<double>(n), size.height());

    std::function<linear::Bounds(size_t)> split = [&segment, &point = point](auto i) {
        linear::Point<double> row(point.x() + segment.width() * i, point.y());
        return linear::Bounds(row, segment);
    };

    return functional::map(split, functional::range(n));
}

linear::Matrix<linear::Bounds> linear::Bounds::tile(const Dimensions &dimensions, const Size<double> &padding) const {
    std::function<Bounds(size_t, size_t)> shift = [&point = point, &size = size, &padding](auto col, auto row) {
        auto x = static_cast<double>(col);
        auto y = static_cast<double>(row);

        Point<double> offset(point.x() + (size + padding).width() * y, point.y() + (size + padding).height() * x);
        Bounds        bounds(offset, size);
        return bounds;
    };

    return {
        functional::product(shift, functional::range(dimensions.rows), functional::range(dimensions.cols)),
        dimensions.cols
    };
}

linear::Matrix<linear::Bounds> linear::Bounds::grid(
    const Dimensions   &dimensions,
    const Size<double> &padding,
    const Size<double> &margin
) const {
    auto rows = static_cast<double>(dimensions.rows);
    auto cols = static_cast<double>(dimensions.cols);

    Size<double> section(
        (size.width() - 2 * margin.width()) / cols - 2 * padding.width(),
        (size.height() - 2 * margin.height()) / rows - 2 * padding.height()
    );

    return Bounds(point + padding + margin, section).tile(dimensions, padding * 2);
}
