#pragma once

#include "shape.hpp"
#include "domain.hpp"

template <typename A, typename B, typename C>
C MapRange(A x, B x1, B x2, C y1, C y2) {
    return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}

// template<typename A>
// C MapRange(A x, B x1, B x2, C y1, C y2) {
//     return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
// }

// Point MapPointToScreen() {
//     auto x = MapRange(Point.x(), )
// }

