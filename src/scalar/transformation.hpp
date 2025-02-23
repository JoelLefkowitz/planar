#ifndef PLANAR_SCALAR_TRANSFORMATION_HPP
#define PLANAR_SCALAR_TRANSFORMATION_HPP

namespace planar {
    class Transformation {
      public:
        bool flip = false;

        double rotation = 0;

        explicit Transformation(bool flip = false, double rotation = 0);

        bool empty() const;
    };
}

#endif
