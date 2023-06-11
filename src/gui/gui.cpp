/**
 * @file gui.cpp
 * @author codezijie (skd1102@outlook.com)
 * @brief
 * @version 0.0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "gui.h"

#include "mainwindow.h"
#include "utility.h"

namespace gui {

void InitGui(int argc, char** argv) {
  new Gui(argc, argv);
  Gui::GetGui()->Show();
  Gui::GetGui()->GetGuiApp()->exec();
}

void DeleteGui() { delete Gui::GetGui(); }

Gui* Gui::m_gui = nullptr;

Gui::Gui(int argc, char** argv) : m_gui_app(new QApplication(argc, argv)) {
  m_gui = this;
  Init();
}

Gui::~Gui() {
  util::DeletePointer(m_gui_app);
  util::DeletePointer(m_mainwindow);
}

void Gui::Init() { m_mainwindow = new MainWindow(); }

void Gui::Show() { m_mainwindow->show(); }

}  // namespace gui