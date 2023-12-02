

%{
#include "testCmdMgr.h"
#include <stdio.h>
%}

%inline %{

void test(const char* cmdName) {
  if (!App::CmdInterface::Instance()->RunTestCmd(cmdName)) {
    printf("error: run %s failed\n", cmdName);
  }
}


%}
