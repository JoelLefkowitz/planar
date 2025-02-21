#include "dimensions.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <string>

planar::Dimensions::Dimensions(size_t rows, size_t cols) : rows(rows), cols(cols) {
}

bool planar::Dimensions::operator==(const Dimensions &rhs) const {
    return rows == rhs.rows && cols == rhs.cols;
}

std::string planar::Dimensions::repr() const {
    return fmt::format("{{rows: {}, cols: {}}}", rows, cols);
}
