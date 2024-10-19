/**
 * @file gui.h
 * @author codezijie (skd1102@outlook.com)
 * @brief
 * @version 0.0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

class QApplication;
namespace gui {

class MainWindow;

/**
 * @brief init gui interface
 *
 * @param argc
 * @param argv
 */
void InitGui(int argc, char** argv);
/**
 * @brief delete gui pointer
 *
 */
void DeleteGui();

class Gui {
 public:
  Gui(int argc, char** argv);
  /**
   * @brief Get QApplication object
   *
   * @return QApplication*
   */
  QApplication* GetGuiApp() const { return m_gui_app; }
  ~Gui();

  static Gui* GetGui() { return m_gui; }
  /**
   * @brief start a thread to run gui
   * 
   */
  void run();

 private:
  /**
   * @brief init all paramters in gui
   * 
   */
  void Init();
  void Show();
  void exec();

  QApplication* m_gui_app = nullptr;
  MainWindow* m_mainwindow = nullptr;
  static Gui* m_gui;
};

}  // namespace gui