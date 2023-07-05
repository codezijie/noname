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
#include "utility.h"
#include <tcl.h>
#include <thread>
#include <algorithm>
#include <iostream>

namespace App {

// start TestCmdMgr
TestCmdMgr::TestCmdMgr() {
	Initalize();
}

void TestCmdMgr::Initalize() { 
	RegisterCmd("demo", std::make_unique<DemoTestCmd>()); 
	RegisterCmd("interp", std::make_unique<InterpTestCmd>()); 
}

bool TestCmdMgr::RegisterCmd(const std::string &cmdName, std::unique_ptr<BaseTestCmd> &&cmdInterface) {
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

BaseTestCmd* TestCmdMgr::GetTestCmdByName(const std::string cmdName) {
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


// start InterpTestCmd
void InterpTestCmd::GenFakeData() {
  // do nothing
}

bool InterpTestCmd::Run() {
  auto interp = util::GlobalObject::Instance()->GetInterp();
  std::string cmd = "puts \"run cmd in main-thread\"";
  if (TCL_ERROR == Tcl_Eval(interp, cmd.c_str())) {
    std::cout << "eval: " << cmd << " error\n";
  }
  std::thread t(thread_main);
  t.join();
  std::thread t2(thread_main);
  t2.join();
  return true;
}

void InterpTestCmd::thread_main() {
  auto interp = util::GlobalObject::Instance()->GetInterp();
  std::string cmd = "puts \"run cmd in sub-thread\"";
  std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
  if (TCL_ERROR == Tcl_Eval(interp, cmd.c_str())) {
    std::cout << "eval: " << cmd << " error\n";
  }
}

// end InterpTestCmd


} // namespace App