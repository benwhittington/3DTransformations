#pragma once

struct Domain {
    Domain() {};

    Domain(double minX, double maxX, double minY, double maxY) : m_minX(minX),
                                             m_maxX(maxX),
                                             m_minY(minY),
                                             m_maxY(maxY),
                                             m_initMinX(minX),
                                             m_initMaxX(maxX),
                                             m_initMinY(minY),
                                             m_initMaxY(maxY)
    {}

    double MinX() const {
        return m_minX;
    }

    double MaxX() const {
        return m_maxX;
    }

    double MinY() const {
        return m_minY;
    }

    double MaxY() const {
        return m_maxY;
    }


    void ZoomIn() {
        zoomIn(m_minX, m_maxX);
        zoomIn(m_minY, m_maxY);
    }

    void ZoomOut() {
        zoomOut(m_minX, m_maxX);
        zoomOut(m_minY, m_maxY);
    }

    void Up() { // shift the content not the view
        neg(m_minY, m_maxY);
    }

    void Down() { // shift the content not the view
        pos(m_minY, m_maxY);
    }

    void Left() {
        neg(m_minX, m_maxX);
    }

    void Right() {
        pos(m_minX, m_maxX);
    }

    void Reset() {
        m_minX = m_initMinX;
        m_maxX = m_initMaxX;
        m_minY = m_initMinY;
        m_maxY = m_initMaxY;  
    }

private:
    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;

    double m_initMinX;
    double m_initMaxX;
    double m_initMinY;
    double m_initMaxY;

    static constexpr double m_sFactor = 1.01;
    static constexpr double m_sShift = 0.01;

    static void pos(double& x0, double& x1){
        const auto absShift = m_sShift * (x1 - x0);
        x0 += absShift;
        x1 += absShift;
    }

    static void neg(double& x0, double& x1){
        const auto absShift = m_sShift * (x1 - x0);
        x0 -= absShift;
        x1 -= absShift;
    }

    static void zoomOut(double& x0, double& x1) {
        const auto middle = x0 + (x1 - x0) / 2;
        const auto halfWidth = m_sFactor * (x1 - x0) / 2;
        
        x0 = middle - halfWidth; 
        x1 = middle + halfWidth;
    }

    static void zoomIn(double& x0, double& x1) {
        const auto middle = x0 + (x1 - x0) / 2;
        const auto halfWidth = (x1 - x0) / (m_sFactor * 2);
        
        x0 = middle - halfWidth; 
        x1 = middle + halfWidth;
    }
};
