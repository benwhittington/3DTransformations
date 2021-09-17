#pragma once

#include <iostream>
#include <stddef.h>
#include <vector>

#include "point.hpp"

template<size_t dims>
class Shape {
private:
    std::vector<Point<dims>> m_Points;
    size_t m_Size;
    size_t m_Idx;
public:
    Shape();
    Shape(size_t size);
    void operator+=(Point<dims>&& p);
    size_t NumPoints() const;
    Shape<dims> operator-(const Point<dims>& p) const;
    Point<dims> operator[](size_t i) const;
    Point<dims>& operator[](size_t i);
    Shape<dims>& operator<<(Point<dims>&& p);
};

template<size_t dims>
double Dot(const Point<dims>& p1, const Point<dims>& p2) {
    auto res = 0.;
    for (size_t i = 0; i < dims; ++i) {
        res += p1[i] * p2[i];
    }
    return res;
}