#include "dimensions.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <string>

linear::Dimensions::Dimensions(size_t rows, size_t cols) : rows(rows), cols(cols) {}

bool linear::Dimensions::operator==(const Dimensions &rhs) const { return rows == rhs.rows && cols == rhs.cols; }

std::string linear::Dimensions::repr() const { return fmt::format("{{rows: {}, cols: {}}}", rows, cols); }
