#pragma once

#include "stddef.h"

template<size_t dims>
class Point {
private:
    double m_pts[dims];
public:
    Point();
    Point(double x, double y, double z);
    Point(double x, double y);
    double operator[](size_t i) const;
    double& operator[](size_t i);
    Point<dims>& operator*=(double val);
    Point<dims>& operator*(double val);
    Point<dims> operator*(double val) const;
    Point<dims> operator-(const double val) const;
    Point<dims> operator-(const Point<dims> p) const;
    Point<dims> operator/(double val) const;
    Point<dims>& operator+=(const Point<dims>& p);
    Point<dims>& operator-=(const Point<dims>& p);
    Point<dims>& operator/=(double val);
    double Norm() const;
    double& x();
    double& y();
    double& z();
    double x() const;
    double y() const;
    double z() const;
};