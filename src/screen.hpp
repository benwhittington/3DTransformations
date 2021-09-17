#pragma once

#include <stddef.h>

struct Screen {
    Screen() {}
    
    Screen(size_t pixelsX, size_t pixelsY) : m_pixelsX(pixelsX), 
                                             m_pixelsY(pixelsY),
                                             m_NumPixels(m_pixelsX * m_pixelsY) 
    {}

    size_t PixelsX() const {
        return m_pixelsX;
    }

    size_t PixelsY() const {
        return m_pixelsY;
    }

    size_t NumPixels() const {
        return m_NumPixels;
    }

private:
    size_t m_pixelsX;
    size_t m_pixelsY;
    size_t m_NumPixels;
};