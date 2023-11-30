/**
 * @file hx_interface.cpp
 * @author yanqing (yanqing.cao@huaxinjushu.com)
 * @brief
 * @version 0.1
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "testCmdMgr.h"
#include "testCmd.h"
#include <iostream>
namespace App {

extern const char *swig_route_tcl_inits[];

} // namespace App
extern "C" {
extern int Swig_route_Init(Tcl_Interp *interp);
}
extern void evalTclInit(Tcl_Interp *interp, const char *[]);
namespace App {

IMPLEMENT_SINGLETON(CmdInterface);

CmdInterface::~CmdInterface() {
  if (nullptr != testCmdMgr_) {
    delete testCmdMgr_;
    testCmdMgr_ = nullptr;
  }
}
bool CmdInterface::Initialize(Tcl_Interp *interp) {
  if (!InitRouteSwig(interp)) {
    return false;
  }
  testCmdMgr_ = new TestCmdMgr();
  return true;
}

bool CmdInterface::DeInitialize() {
  // TODO
  return true;
}

bool CmdInterface::InitRouteSwig(Tcl_Interp *interp) {
  int ret = ::Swig_route_Init(interp);
  if (ret != 0) {
    std::cout << "error: Route_init=" << ret << std::endl;
    return false;
  }
  ::evalTclInit(interp, App::swig_route_tcl_inits);
  return true;
}

bool CmdInterface::RunTestCmd(const char *cmdName) {
  auto cmd = testCmdMgr_->GetTestCmdByName(cmdName);
  if (nullptr == cmd) {
    return false;
  }
  cmd->GenFakeData();
  return cmd->Run();
}

} // namespace App
