#pragma once

#include "geometry.h"
#include "singleton.h"
#include "utility.h"

#include <map>

namespace gui {

using geometry::Point;

class Terniaml {
  DECLARE_SINGLETON(Terniaml);

public:
  enum class Color {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
  };

private:
  std::map<Point, std::pair<Color, char>> m_frame;

  // first -> row -> y
  // second -> col -> x
  util::IntPair m_size;  // Terniaml window size
  util::IntPair m_fsize; // draw window size
  char m_boundary = '#';
  Color m_bColor = Color::Default; // boundary color

public:
  void Draw();
  void Clear();
  void Dump() const;

  void SetBoundaryColor(Color c);
  void AddBoundary2Frame();

private:
  Terniaml();
};

} // namespace gui
