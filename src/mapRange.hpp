#pragma once

#include "domain.hpp"
#include "screen.hpp"
#include "shape.hpp"
#include "point.hpp"

namespace map {
    template <typename A, typename B, typename C>
    C MapRange(A x, B x1, B x2, C y1, C y2) {
        return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
    }

    Shape<2> MapFromDomainToScreen(const Shape<2>& shape, Domain domain, Screen screen) {
        auto outShape = Shape<2>(shape.NumPoints());
        for (size_t i = 0; i < shape.NumPoints(); ++i) {
            auto x = MapRange(shape[i].x(), domain.MinX(), domain.MaxX(), static_cast<double>(screen.PixelsX()), static_cast<double>(0));
            auto y = MapRange(shape[i].y(), domain.MinY(), domain.MaxY(), static_cast<double>(screen.PixelsY()), static_cast<double>(0));
            outShape << Point<2>(x, y);
        }
        return outShape;
    }
}