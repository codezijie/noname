/**
 * @file hx_interface.h
 * @author yanqing (yanqing.cao@huaxinjushu.com)
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include "singleton.h"
typedef struct Tcl_Interp Tcl_Interp;

namespace App {

class TestCmdMgr;
class CmdInterface {
  DECLARE_SINGLETON(CmdInterface);

public:
  CmdInterface() = default;
  ~CmdInterface();

  bool Initialize(Tcl_Interp *interp);
  bool DeInitialize();

  bool RunTestCmd(const char *cmdName);

private:
  bool InitRouteSwig(Tcl_Interp *interp);
  TestCmdMgr *testCmdMgr_{nullptr};
};

} // namespace App
