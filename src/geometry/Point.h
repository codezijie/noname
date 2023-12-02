#ifndef HDR_POINT
#define HDR_POINT

namespace geometry {
/**
 *  @brief A Point represents a coordinate in 2D space.
 *
 *  @note The coordinate should be integer, which means all the points should be
 * snapped at input.
 */
class Point {
private:
  int m_x, m_y;

public:
  Point();
  Point(int x, int y);
  Point(const Point &p);
  ~Point();

  int x() { return m_x; }
  int y() { return m_y; }

  void swap(Point &p);

  Point &operator+=(const Point &p);
  Point &operator-=(const Point &p);
  Point &operator*=(double scale);
  Point &operator/=(double scale);

  bool operator<(const Point &p) const;
  bool operator==(const Point &p) const;
  bool operator!=(const Point &p) const;
};

Point operator+(const Point &p1, const Point &p2);
Point operator-(const Point &p1, const Point &p2);
} // namespace geometry

#endif
