#include "bounds.hpp"
#include "../areas/size.tpp"
#include "../linear/matrix.tpp"
#include "../points/point.tpp"
#include "../points/segment.tpp"
#include "../scalar/dimensions.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <functional>
#include <funky/concrete/booleans.tpp>
#include <funky/generics/iterables.tpp>
#include <funky/generics/pairs.tpp>
#include <funky/generics/sets.tpp>
#include <string>
#include <vector>

planar::Bounds::Bounds() : point(0, 0), size(0, 0) {
}

planar::Bounds::Bounds(double x, double y, double w, double h) : point(Point(x, y)), size(Size(w, h)) {
}

planar::Bounds::Bounds(const Point<int> &point, const Size<int> &size)
    : point(Point<double>(point.x(), point.y()))
    , size(Size<double>(size.width(), size.height())) {
}

planar::Bounds::Bounds(const Point<double> &point, const Size<double> &size) : point(point), size(size) {
}

planar::Bounds::Bounds(const std::vector<Bounds> &bounds) {
    using F = std::function<Point<double>(const Bounds &)>;

    F left = [](const auto &x) {
        return x.point;
    };
    F right = [](const auto &x) {
        return x.point + x.size;
    };

    auto interval = enclose(funky::concat(
        funky::map<std::vector<Point<double>>>(left, bounds),
        funky::map<std::vector<Point<double>>>(right, bounds)
    ));

    point = interval.point;
    size  = interval.size;
}

planar::Bounds::Bounds(const Matrix<Bounds> &bounds) {
    auto limits = bounds.size();

    auto first = bounds.get({0, 0});
    auto last  = bounds.get({limits.cols - 1, limits.rows - 1});

    point = first.point;
    size  = last.point.projection() - first.point.projection() + last.size;
}

planar::Bounds planar::Bounds::enclose(const std::vector<Point<double>> &points) {
    auto x = funky::map<std::vector<double>>(
        [](const auto &p) {
            return p.x();
        },
        points
    );

    auto y = funky::map<std::vector<double>>(
        [](const auto &p) {
            return p.y();
        },
        points
    );

    Point<double> point(funky::min(x, 0), funky::min(y, 0));
    Size<double> size(funky::max(x, 0) - point.x(), funky::max(y, 0) - point.y());

    return {point, size};
}

bool planar::Bounds::operator==(const Bounds &rhs) const {
    return point == rhs.point && size == rhs.size;
}

bool planar::Bounds::operator!=(const Bounds &rhs) const {
    return !(*this == rhs);
}

bool planar::Bounds::operator<(const Bounds &rhs) const {
    return point < rhs.point || (point == rhs.point && size < rhs.size);
}

bool planar::Bounds::operator>(const Bounds &rhs) const {
    return rhs < *this;
}

bool planar::Bounds::operator<=(const Bounds &rhs) const {
    return !(rhs < *this);
}

bool planar::Bounds::operator>=(const Bounds &rhs) const {
    return !(*this < rhs);
}

planar::Bounds planar::Bounds::operator+(const planar::Size<double> &rhs) const {
    return {point, size + rhs};
}

planar::Bounds planar::Bounds::operator-(const planar::Size<double> &rhs) const {
    return {point, size - rhs};
}

planar::Bounds planar::Bounds::operator*(const double &rhs) const {
    return {point, size * rhs};
}

planar::Bounds planar::Bounds::operator/(const double &rhs) const {
    return {point, size / rhs};
}

std::string planar::Bounds::repr() const {
    return fmt::format("{{{}, {}}}", point.repr(), size.repr());
}

bool planar::Bounds::empty() const {
    return size.empty();
}

std::vector<planar::Point<double>> planar::Bounds::corners() const {
    return {
        point,
        point + Size<double>(size.width(), 0),
        point + Size<double>(0, size.height()),
        point + size,
    };
}

std::vector<planar::Point<double>> planar::Bounds::midpoints() const {
    return {
        point + Size<double>(size.width() / 2, 0),
        point + Size<double>(0, size.height() / 2),
        point + Size(size.width(), size.height() / 2),
        point + Size(size.width() / 2, size.height()),
    };
}

std::vector<planar::Segment<double>> planar::Bounds::segments() const {
    auto points = corners();
    return {
        {points[0], points[1]},
        {points[0], points[2]},
        {points[1], points[3]},
        {points[2], points[3]},
    };
}

bool planar::Bounds::contains(const Point<double> &rhs) const {
    auto upper = point + size;
    return funky::all(std::vector<bool>({
        point.x() <= rhs.x(),
        point.y() <= rhs.y(),
        rhs.x() <= upper.x(),
        rhs.y() <= upper.y(),
    }));
}

bool planar::Bounds::overlaps(const Bounds &bounds) const {
    std::function<bool(const Point<double> &x)> contains_corner = [&bounds](const auto &x) {
        return bounds.contains(x);
    };

    return funky::any(contains_corner, corners());
}

planar::Point<double> planar::Bounds::center() const {
    return point + size / 2;
}

planar::Bounds planar::Bounds::center(const Size<double> &region) const {
    return align(region, Alignment::Center);
}

planar::Bounds planar::Bounds::rebase() const {
    return {0, 0, size.width(), size.height()};
}

planar::Bounds planar::Bounds::shift(const Size<double> &move) const {
    return {point + move, size};
}

planar::Bounds planar::Bounds::pad(const Size<double> &border) const {
    return {point + border / 2, size - border};
}

planar::Bounds planar::Bounds::constrain(const Size<double> &limits) const {
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

planar::Bounds planar::Bounds::align(const Size<double> &region, Alignment alignment) const {
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

planar::Bounds planar::Bounds::scale(const double &factor) const {
    return scale({factor, factor});
}

planar::Bounds planar::Bounds::scale(const Size<double> &factor) const {
    return scale_about(factor, center());
}

planar::Bounds planar::Bounds::scale_about(const double &factor, const Point<double> &origin) const {
    return scale_about({factor, factor}, origin);
}

planar::Bounds planar::Bounds::scale_about(const Size<double> &factor, const Point<double> &origin) const {
    auto x = factor.width() * point.x() + (1 - factor.width()) * origin.x();
    auto y = factor.height() * point.y() + (1 - factor.height()) * origin.y();
    return {
        {x, y},
        size.scale(factor)
    };
}

planar::Bounds planar::Bounds::slice(const Dimensions &dimensions, const planar::Slice &rows, const planar::Slice &cols)
    const {
    return Bounds(grid(dimensions).slice(rows, cols));
}

std::pair<planar::Bounds, planar::Bounds> planar::Bounds::split_width(double x) const {
    return {
        Bounds(point, Size<double>(x, size.height())),
        Bounds(point + Size<double>(x, 0), size - Size<double>(x, 0)),
    };
}

std::pair<planar::Bounds, planar::Bounds> planar::Bounds::split_height(double y) const {
    return {
        Bounds(point, Size<double>(size.width(), y)),
        Bounds(point + Size<double>(0, y), size - Size<double>(0, y)),
    };
}

std::vector<planar::Point<double>> planar::Bounds::sample(size_t side) const {
    if (side == 1) {
        return {center()};
    }

    auto pairs = funky::product(
        funky::linspace(point.x(), point.x() + size.width(), side),
        funky::linspace(point.y(), point.y() + size.height(), side)
    );

    return funky::map<std::vector<Point<double>>>(
        [](auto pair) {
            return Point<double>(pair.first, pair.second);
        },
        pairs
    );
}

std::vector<planar::Bounds> planar::Bounds::rows(size_t n) const {
    planar::Size<double> segment(size.width(), size.height() / static_cast<double>(n));

    std::function<planar::Bounds(size_t)> split = [&segment, &point = point](auto i) {
        planar::Point<double> row(point.x(), point.y() + segment.height() * static_cast<double>(i));
        return planar::Bounds(row, segment);
    };

    return funky::map<std::vector<Bounds>>(split, funky::range(n));
}

std::vector<planar::Bounds> planar::Bounds::cols(size_t n) const {
    planar::Size<double> segment(size.width() / static_cast<double>(n), size.height());

    std::function<planar::Bounds(size_t)> split = [&segment, &point = point](auto i) {
        planar::Point<double> row(point.x() + segment.width() * i, point.y());
        return planar::Bounds(row, segment);
    };

    return funky::map<std::vector<Bounds>>(split, funky::range(n));
}

planar::Matrix<planar::Bounds> planar::Bounds::tile(const Dimensions &dimensions, const Size<double> &padding) const {
    auto pairs = funky::product(funky::range(dimensions.rows), funky::range(dimensions.cols));

    return {
        funky::map<std::vector<Bounds>>(
            [&point = point, &size = size, &padding](auto pair) {
                auto x = static_cast<double>(pair.first);
                auto y = static_cast<double>(pair.second);

                Point<double> offset(
                    point.x() + (size + padding).width() * y,
                    point.y() + (size + padding).height() * x
                );
                Bounds bounds(offset, size);
                return bounds;
            },
            pairs
        ),
        dimensions.cols
    };
}

planar::Matrix<planar::Bounds> planar::Bounds::grid(
    const Dimensions &dimensions,
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
