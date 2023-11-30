/**
 * @file database.h
 * @author codezijie (skd1102@outlook.com)
 * @brief
 * @version 0.0.1
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <vector>

#include "geometry.h"
#include "singleton.h"

namespace db {

using geometry::Point;
using geometry::Polygon;

enum FLAG { DRAW = 0x1 };
enum TYPE { POINT, POLYGON };

/**
 * @brief add property to shapes
 *
 */
template <typename T>
class DShape : public std::enable_if_t<
                   std::is_same_v<T, Polygon> || std::is_same_v<T, Point>, T> {
public:
  using T::T;
  bool IsDraw() const { return m_flag & DRAW; }
  inline int GetGroupNum() const { return m_group; }

private:
  unsigned int m_flag = 0;
  int m_group = 0;
};

/**
 * @brief interface class of db, you could get all shapes.
 *
 */

using PolygonList = std::vector<DShape<Polygon> *>;
using PointList = std::vector<DShape<Point> *>;
using PolygonListIter = std::vector<DShape<Polygon> *>::iterator;

class TopModule {
  DECLARE_SINGLETON(TopModule)

public:
  /**
   * @brief Get the Polygon List that need paint
   *
   * @return PolygenList
   */
  PolygonList GetDrawPolygenList();
  /**
   * @brief print all info of Polygon. such as groups, need draw , etc...
   *
   */
  void GetAllPolygonInfo() const;

private:
  PolygonList m_polygen_list;
};

} // namespace db
