/**
 * @file mainwindow.cpp
 * @author codezijie (skd1102@outlook.com)
 * @brief
 * @version 0.0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "mainwindow.h"

#include <QtGui/QWindow>
#include <QtGui/QScreen>

namespace gui {

MainWindow::MainWindow() { Init(); }

void MainWindow::Init() { 
  setWindowTitle("App"); 
  auto size = windowHandle()->screen()->size();
  resize(size * 0.5);
}

}  // namespace gui