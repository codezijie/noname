#include "Point.h"
#include "utility"

namespace geometry
{
    // ----------------------------------------------------------------
    //  Implementation of class Point

    Point::Point() : m_x(0), m_y(0)
    {
    }
    Point::Point(int x, int y) : m_x(x), m_y(y)
    {
    }
    Point::Point(const Point &p) : m_x(p.m_x), m_y(p.m_y)
    {
    }

    void Point::swap(Point &p)
    {
        std::swap(m_x, p.m_x);
        std::swap(m_y, p.m_y);
    }

    inline Point &Point::operator+=(const Point &p)
    {
        m_x += p.m_x;
        m_y += p.m_y;
        return *this;
    }
    inline Point &Point::operator-=(const Point &p)
    {
        m_x -= p.m_x;
        m_y -= p.m_y;
        return *this;
    }

    inline bool Point::operator<(const Point &p) const
    {
        return m_x < p.m_x || (m_x == p.m_x && m_y < p.m_y);
    }
    inline bool Point::operator==(const Point &p) const
    {
        return m_x == p.m_x && m_y == p.m_y;
    }
    inline bool Point::operator!=(const Point &p) const
    {
        return m_x != p.m_x || m_y != p.m_y;
    }

    inline Point &operator+(const Point &p1, const Point &p2)
    {
        Point p(p1);
        p += p2;
        return p;
    }
    inline Point &operator-(const Point &p1, const Point &p2)
    {
        Point p(p1);
        p -= p2;
        return p;
    }

} // namespace geometry
