#include <cmath>

#include "point.hpp"

template class Point<2>;
template class Point<3>;

template<size_t dims>
Point<dims>::Point() {
}

template<size_t dims>
Point<dims>::Point(double x, double y, double z) {
    m_pts[0] = x; 
    m_pts[1] = y; 
    m_pts[2] = z; 
}

template<size_t dims>
Point<dims>::Point(double x, double y) {
    m_pts[0] = x; 
    m_pts[1] = y; 
}

template<size_t dims>
double Point<dims>::operator[](size_t i) const {
    return m_pts[i];
}

template<size_t dims>
double& Point<dims>::operator[](size_t i) {
    return m_pts[i];
}

template<size_t dims>
Point<dims>& Point<dims>::operator*=(double val) {
    return this->operator*(val);
}

template<size_t dims>
Point<dims>& Point<dims>::operator*(double val) {
    for (size_t i = 0; i < dims; ++i) {
        m_pts[i] *= val;
    }
    return *this;
}

template<size_t dims>
Point<dims> Point<dims>::operator*(double val) const {
    auto res = *this;
    for (size_t i = 0; i < dims; ++i) {
        res[i] *= val;
    }
    return res;
}

template<size_t dims>
Point<dims> Point<dims>::operator-(const double val) const {
    auto res = Point<dims>();
    for (size_t i = 0; i < dims; ++i) {
        res[i] = m_pts[i] - val;
    }
    return res;
}

template<size_t dims>
Point<dims> Point<dims>::operator-(const Point<dims> p) const {
    auto res = p;
    for (size_t i = 0; i < dims; ++i) {
        res[i] = m_pts[i] - p[i];
    }
    return res;
}

template<size_t dims>
Point<dims> Point<dims>::operator/(double val) const {
    auto res = *this;
    for (size_t i = 0; i < dims; ++i) {
        res[i] /= val;
    }
    return res;
}

template<size_t dims>
Point<dims>& Point<dims>::operator+=(const Point<dims>& p) {
    for (size_t i = 0; i < dims; ++i) {
        m_pts[i] += p[i];
    }
    return *this;
}

template<size_t dims>
Point<dims>& Point<dims>::operator-=(const Point<dims>& p) {
    for (size_t i = 0; i < dims; ++i) {
        m_pts[i] -= p[i];
    }
    return *this;
}

template<size_t dims>
Point<dims>& Point<dims>::operator/=(double val) {
    for (size_t i = 0; i < dims; ++i) {
        m_pts[i] /= val;
    }
    return *this;
}

template<size_t dims>
double Point<dims>::Norm() const {
    auto total = 0;
    for (size_t i = 0; i < dims; ++i) {
        total += m_pts[i] * m_pts[i];
    }
    return std::sqrt(total);
}

template<size_t dims>
double& Point<dims>::x() {
    return m_pts[0];
}

template<size_t dims>
double& Point<dims>::y() {
    return m_pts[1];
}

template<size_t dims>
double& Point<dims>::z() {
    return m_pts[2];
}

template<size_t dims>
double Point<dims>::x() const {
    return m_pts[0];
}

template<size_t dims>
double Point<dims>::y() const {
    return m_pts[1];
}

template<size_t dims>
double Point<dims>::z() const {
    return m_pts[2];
}
