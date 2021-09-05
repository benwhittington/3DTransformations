#pragma once

#include <cmath>
#include <stddef.h>

#include "mapRange.hpp"
#include "shape.hpp"
#include "screen.hpp"

struct X {};
struct Y {};
struct Z {};

// free functions for performing transformations
namespace trans {
    // ------------- rotation -------------
    template<typename axis>
    void Rotate(Point<3>& p, double a);

    template<typename axis>
    void Rotate(Shape<3>& shape, double a) {
        for (size_t i = 0; i < shape.NumPoints(); ++i) {
            Rotate<axis>(shape[i], a);
        }
    }

    template<>
    void Rotate<X>(Point<3>& p, double a) {
        const auto sinTheta = std::sin(a);
        const auto cosTheta = std::cos(a);
        const auto y = p.y();
        const auto z = p.z();
        // x = x
        p.y() = cosTheta * y - sinTheta * z;
        p.z() = sinTheta * y + cosTheta * z;
    }

    template<>
    void Rotate<Y>(Point<3>& p, double a) {
        const auto sinTheta = std::sin(a);
        const auto cosTheta = std::cos(a);
        const auto x = p.x();
        const auto z = p.z();
        p.x() = + cosTheta * x + sinTheta * z;
        // y = y
        p.z() = - sinTheta * x + cosTheta * z;
    }

    template<>
    void Rotate<Z>(Point<3>& p, double a) {
        const auto sinTheta = std::sin(a);
        const auto cosTheta = std::cos(a);
        const auto x = p.x();
        const auto y = p.y();
        p.x() = cosTheta * x - sinTheta * y;
        p.y() = sinTheta * x + cosTheta * y;
        // z = z
    }

    // ------------- projection -------------
    // simple project onto basis
    Point<2> Project(const Point<3>& p) {
        return Point<2>(p.x(), p.y());
    }

    Shape<2> Project(const Shape<3>& shape) {
        auto outShape = Shape<2>(shape.NumPoints());
        for (size_t i = 0; i < shape.NumPoints(); ++i) {
            outShape << Project(shape[i]);
        }
        return outShape;
    }

    template<typename axis0, typename axis1>
    Point<2> Project(const Point<3>& p);

    template<>
    Point<2> Project<X, Y>(const Point<3>& p) {
        return Point<2>(p.x(), p.y());
    }

    template<>
    Point<2> Project<X, Z>(const Point<3>& p) {
        return Point<2>(p.x(), p.z());
    }

    template<>
    Point<2> Project<Y, Z>(const Point<3>& p) {
        return Point<2>(p.y(), p.z());
    }

    template<typename axis0, typename axis1>
    Shape<2> Project(const Shape<3>& shape) {
        auto outShape = Shape<2>(shape.NumPoints());
        for (size_t i = 0; i < shape.NumPoints(); ++i) {
            outShape << Project<axis0, axis1>(shape[i]);
        }
        return outShape;
    }

    // project onto plane
    template<typename axis0, typename axis1>
    Point<2> Project(const Point<3>& p, const Point<3>& n) {
        auto projectedPoint = p - n * Dot<3>(p, n / n.Norm());
        return Project<axis0, axis1>(projectedPoint);
    }    

    template<typename axis0, typename axis1>
    Shape<2> Project(const Shape<3>& shape, const Point<3>& n) {
        auto outShape = Shape<2>(shape.NumPoints());
        for (size_t i = 0; i < shape.NumPoints(); ++i) {
            outShape << Project<axis0, axis1>(shape[i], n);
        }
        return outShape;
    }
}
