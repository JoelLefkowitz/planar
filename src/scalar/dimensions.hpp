#ifndef PLANAR_SCALAR_DIMENSIONS_HPP
#define PLANAR_SCALAR_DIMENSIONS_HPP

#include <cstddef>
#include <string>

namespace planar {
    class Dimensions {
      public:
        size_t rows;
        size_t cols;

        Dimensions(size_t rows, size_t cols);

        bool operator==(const Dimensions &rhs) const;

        std::string repr() const;
    };
}

#endif
