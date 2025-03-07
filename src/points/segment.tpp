#ifndef PLANAR_POINTS_SEGMENT_TPP
#define PLANAR_POINTS_SEGMENT_TPP

#include "point.hpp"
#include "segment.hpp"
#include <fmt/core.h>

template <typename T>
planar::Segment<T>::Segment(const Point<T> &start, const Point<T> &end) : start(start)
                                                                        , end(end) {
}

template <typename T>
bool planar::Segment<T>::operator==(const Segment<T> &rhs) const {
    return start == rhs.start && end == rhs.end;
}

template <typename T>
bool planar::Segment<T>::operator!=(const Segment<T> &rhs) const {
    return start != rhs.start || end != rhs.end;
}

template <typename T>
std::string planar::Segment<T>::repr() const {
    return fmt::format("{{start: {}, end: {}}}", start.repr(), end.repr());
}

template <typename T>
planar::Point<T> planar::Segment<T>::midpoint() const {
    return {(start.x() + end.x()) / 2, (start.y() + end.y()) / 2};
}

#endif
