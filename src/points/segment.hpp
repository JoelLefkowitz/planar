#ifndef PLANAR_POINTS_SEGMENT_HPP
#define PLANAR_POINTS_SEGMENT_HPP

#include "point.hpp"

namespace planar {
    template <typename T>
    class Segment {
      public:
        Point<T> start;
        Point<T> end;

        Segment(const Point<T> &start, const Point<T> &end);

        bool operator==(const Segment<T> &rhs) const;
        bool operator!=(const Segment<T> &rhs) const;

        std::string repr() const;

        Point<T> midpoint() const;
    };
}

#endif
