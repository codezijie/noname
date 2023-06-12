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

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <iostream>
#include <thread>

#include "mainwindow.h"
#include "utility.h"
namespace gui {

void InitGui(int argc, char** argv) { new Gui(argc, argv); }

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

void Gui::exec() { m_gui_app->exec(); }

void Gui::run() {
  auto app = GetGuiApp();
  Show();
  app->exec();
}
#if 0
void GuiCallBack() {
  auto app = Gui::GetGui();
  app->Show();
  app->exec();
}
// can't run app->exec in other thread except main thread
void Gui::run() {
  std::thread t(GuiCallBack);
  if (!t.joinable()) {
    std::cout << "error: run gui failed. " << std::endl;
    return;
  }
  t.join();
}
#endif
}  // namespace gui