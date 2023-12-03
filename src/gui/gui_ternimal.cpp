#include "gui_ternimal.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

namespace gui {
IMPLEMENT_SINGLETON(Terniaml);

// start Terniaml

Terniaml::Terniaml() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  m_size.first = size.ws_row;
  m_size.second = size.ws_col;

  m_fsize.first = size.ws_row / 2;
  m_fsize.second = size.ws_col / 2;

  // addBoundary2Frame();
}

// Terniaml public

void Terniaml::Clear() { system("clear"); }

void Terniaml::Draw() {

  Clear();

  Color old = Color::Default;
  int xShift = (m_size.second - m_fsize.second) / 2;
  int yShift = (m_size.first - m_fsize.first) / 2;

  for (int row = 0; row < yShift; row++) {
    std::cout << std::endl;
  }

  std::string xShiftStr(xShift, ' ');

  for (int y = 0; y < m_fsize.first; y++) { // y
    std::cout << xShiftStr;
    for (int x = 0; x < m_fsize.second; x++) { // x
      if (m_frame.find({x, y}) == m_frame.end()) {
        std::cout << ' ';
      } else {
        auto &[color, c] = m_frame.at({x, y});
        if (color == old) {
          std::cout << c;
        } else {
          old = color;
          std::cout << "\033[" << static_cast<int>(color) << "m" << c;
        }
      }
    }
    std::cout << std::endl;
  }

  std::cout << "\033[" << static_cast<int>(Color::Default) << "m";
}

void Terniaml::Dump() const {

  std::cout << "[debug] Terniaml window size: " << m_size.first << ", "
            << m_size.second << std::endl;

  std::cout << "[debug] draw window size: " << m_fsize.first << ", "
            << m_fsize.second << std::endl;

  for (auto &item : m_frame) {

    std::cout << "[debug]: point(" << item.first.x() << ", " << item.first.y()
              << ")"
              << ": " << item.second.second << std::endl;
  }
}

void Terniaml::SetBoundaryColor(Color c) { m_bColor = c; }

void Terniaml::AddBoundary2Frame() {
  // first row and last row
  for (int i = 0; i < m_fsize.first; i++) {
    m_frame[Point(0, i)] = std::pair(m_bColor, m_boundary);
    m_frame[Point(m_fsize.second - 1, i)] = std::pair(m_bColor, m_boundary);
  }
  for (int i = 0; i < m_fsize.second; i++) {
    m_frame[Point(i, 0)] = std::pair(m_bColor, m_boundary);
    m_frame[Point(i, m_fsize.first - 1)] = std::pair(m_bColor, m_boundary);
  }
}

// Terniaml private
// end Terniaml

} // namespace gui
