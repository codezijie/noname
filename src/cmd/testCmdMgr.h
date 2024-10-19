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
  bool InitAppSwig(Tcl_Interp *interp);
  TestCmdMgr *testCmdMgr_{nullptr};
};

} // namespace App
