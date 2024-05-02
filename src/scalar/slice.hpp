#ifndef PLANAR_SCALAR_SLICE_HPP
#define PLANAR_SCALAR_SLICE_HPP

#include <cstddef>

namespace linear {
    class Slice {
      public:
        size_t start;
        size_t end;

        Slice(size_t start, size_t end);

        bool operator==(const Slice &rhs) const;
    };
}

#endif
