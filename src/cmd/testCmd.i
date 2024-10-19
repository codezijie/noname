

%{
#include "testCmdMgr.h"
#include "gui.h"
#include <stdio.h>
%}

%inline %{

void test(const char* cmdName) {
  if (!App::CmdInterface::Instance()->RunTestCmd(cmdName)) {
    printf("error: run %s failed\n", cmdName);
  }
}

void runGui() {
  gui::Gui::GetGui()->run();
}

%}
