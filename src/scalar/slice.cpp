#include "slice.hpp"
#include <cstddef>

linear::Slice::Slice(size_t start, size_t end) : start(start), end(end) {}

bool linear::Slice::operator==(const Slice &rhs) const { return start == rhs.start && end == rhs.end; }
