/**
 * @file testCmd.cpp
 * @author yanqing (yanqing.cao@huaxinjushu.com)
 * @brief
 * @version 0.1
 * @date 2023-03-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "testCmd.h"
#include "gui_ternimal.h"
#include <algorithm>
#include <iostream>

namespace App {

// start TestCmdMgr
TestCmdMgr::TestCmdMgr() { Initalize(); }

void TestCmdMgr::Initalize() {
  RegisterCmd("demo", std::make_unique<DemoTestCmd>());
  RegisterCmd("tgui", std::make_unique<TerminalGuiTestCmd>());
}

bool TestCmdMgr::RegisterCmd(const std::string &cmdName,
                             std::unique_ptr<BaseTestCmd> &&cmdInterface) {
  if (cmdMap_.find(cmdName) != cmdMap_.end()) {
    std::cout << "command " << cmdName << " have been register\n";
    return false;
  }
  auto res = cmdMap_.emplace(cmdName, std::move(cmdInterface));
  return res.second;
}

void TestCmdMgr::RemoveCmd(const std::string &cmdName) {
  auto iter = cmdMap_.find(cmdName);
  if (iter == cmdMap_.end()) {
    std::cout << "command " << cmdName << " does not exist\n";
    return;
  }
  cmdMap_.erase(iter);
}

BaseTestCmd *TestCmdMgr::GetTestCmdByName(const std::string cmdName) {
  auto iter = cmdMap_.find(cmdName);
  if (iter == cmdMap_.end()) {
    std::cout << "error: commmand doesn't find\n";
    return nullptr;
  }
  return iter->second.get();
}

// end TestCmdMgr

// start DemoTestCmd

void DemoTestCmd::GenFakeData() {
  // TODO
  //  generate data for command
}

bool DemoTestCmd::Run() {
  std::cout << "test Demo command running...\n";
  std::cout << "test Demo command finish\n";
  return true;
}

// end DemoTestCmd

// start TerniamlGuiTestCmd
void TerminalGuiTestCmd::GenFakeData() {
  // TODO: add some char to draw
}

bool TerminalGuiTestCmd::Run() {
  auto tGui = gui::Terniaml::Instance();
  tGui->SetBoundaryColor(gui::Terniaml::Color::Cyan);
  tGui->AddBoundary2Frame();
  tGui->Draw();
  // tGui->Dump();
  gui::Terniaml::DeleteInstance();
  return true;
}

// end TerniamlGuiTestCmd

} // namespace App
