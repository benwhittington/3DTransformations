#include "point.hpp"
#include "shape.hpp"

template class Shape<2>;
template class Shape<3>;

template<size_t dims>
Shape<dims>::Shape() {}

template<size_t dims>
Shape<dims>::Shape(size_t size) : m_size(size) {
    m_points = std::vector<Point<dims>>(m_size);
    idx = 0;
}

template<size_t dims>
void Shape<dims>::operator+=(Point<dims>&& p) {
    for (auto& val : m_points) {
        val += p;
    }
}

template<size_t dims>
size_t Shape<dims>::NumPoints() const {
    return m_size;
}

template<size_t dims>
Shape<dims>& Shape<dims>::operator<<(Point<dims>&& p) {
    m_points[idx++] = p;
    return *this;
}

template<size_t dims>
Shape<dims> Shape<dims>::operator-(const Point<dims>& p) const {
    auto res = *this;
    for (size_t i = 0; i < dims; ++i) {
        res[i] -= p;
    }
    return res;
}

template<size_t dims>
Point<dims>& Shape<dims>::operator[](size_t i) {
    return m_points[i];
}

template<size_t dims>
Point<dims> Shape<dims>::operator[](size_t i) const {
    return m_points[i];
}
