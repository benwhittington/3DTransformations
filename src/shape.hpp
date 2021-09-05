#pragma once

#include <stddef.h>

template<size_t dims>
class Point {
private:
    double m_pts[dims];
public:
    Point() {};

    Point(double* pts[dims]) {
        for (size_t i = 0; i < dims; ++i) {
            m_pts[i];
        }
    }

    Point(double x, double y, double z) {
        m_pts[0] = x; 
        m_pts[1] = y; 
        m_pts[2] = z; 
    }

    Point(double x, double y) {
        m_pts[0] = x; 
        m_pts[1] = y; 
    }

    double operator[](size_t i) const {
        return m_pts[i];
    }

    double& operator[](size_t i) {
        return m_pts[i];
    }

    Point<dims> operator*(double val) const {
        auto res = *this;
        for (size_t i = 0; i < dims; ++i) {
            res[i] *= val;
        }
        return res;
    }

    Point<dims> operator-(const double val) const {
        auto res = Point<dims>();
        for (size_t i = 0; i < dims; ++i) {
            res[i] = m_pts[i] - val;
        }
        return res;
    }

    Point<dims> operator-(const Point<dims> p) const {
        auto res = p;
        for (size_t i = 0; i < dims; ++i) {
            res[i] = m_pts[i] - p[i];
        }
        return res;
    }

    Point<dims> operator/(double val) const {
        auto res = *this;
        for (size_t i = 0; i < dims; ++i) {
            res[i] /= val;
        }
        return res;
    }

    Point<dims> operator/=(double val) const {
        auto res = *this;
        for (size_t i = 0; i < dims; ++i) {
            res[i] /= val;
        }
        return res;
    }

    double Norm() const {
        auto total = 0;
        for (size_t i = 0; i < dims; ++i) {
            total += m_pts[i] * m_pts[i];
        }
        return std::sqrt(total);
    }

    double& x() {
        return m_pts[0];
    }
    
    double& y() {
        return m_pts[1];
    }
    
    double& z() {
        return m_pts[2];
    }

    double x() const {
        return m_pts[0];
    }
    
    double y() const {
        return m_pts[1];
    }
    
    double z() const {
        return m_pts[2];
    }
};

template<size_t dims>
class Shape {
private:
    std::vector<Point<dims>> m_points;
    size_t m_size;
    size_t idx;

public:
    Shape() {}

    Shape(size_t size) : m_size(size) {
        m_points = std::vector<Point<dims>>(m_size);
        idx = 0;
    }

    ~Shape() {}

    size_t NumPoints() const {
        return m_size;
    }

    Shape<dims>& operator<<(Point<dims>&& p) {
        m_points[idx++] = p;
        return *this;
    }

    Point<dims>& operator[](size_t i) {
        return m_points[i];
    }

    Point<dims> operator[](size_t i) const {
        return m_points[i];
    }

};

template<size_t dims>
double Dot(const Point<dims>& p1, const Point<dims>& p2) {
    auto res = 0.;
    for (size_t i = 0; i < dims; ++i) {
        res += p1[i] * p2[i];
    }
    return res;
}