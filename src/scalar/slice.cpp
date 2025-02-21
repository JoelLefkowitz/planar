#include "slice.hpp"
#include <cstddef>

planar::Slice::Slice(size_t start, size_t end) : start(start), end(end) {
}

bool planar::Slice::operator==(const Slice &rhs) const {
    return start == rhs.start && end == rhs.end;
}
