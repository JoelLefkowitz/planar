#include "transformation.hpp"

planar::Transformation::Transformation(bool flip, double rotation) : flip(flip), rotation(rotation) {
}

bool planar::Transformation::empty() const {
    return !flip && rotation == 0;
}
