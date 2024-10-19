#pragma once

#include <vector>

#include "Point.h"

namespace geometry {
/**
 *  @brief A Polygon consists of an outer hull and optional several holes.
 *
 *  @note The orientation of hull is clockwise, while the orientation of hole is
 * counterclockwise.
 */
class Polygon {
private:
  // TODO: implementation of Point class
  std::vector<Point> m_hull;
  // TODO: how to store holes in Polygon? Wrap a new structure like "Contour"?

public:
  Polygon(/* args */);
  ~Polygon();
};

} // namespace geometry
