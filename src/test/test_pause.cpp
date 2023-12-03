#include <iostream>
#include <string>
#include <tcl.h>
#include <tclDecls.h>

using namespace std;

Tcl_Interp *interp = nullptr;

void myPause() {
  string cmd;
  bool isPause = true;
  do {
    cout << "pause> ";
    getline(cin, cmd);
    if (cmd == "resume") {
      isPause = false;
    } else {
      Tcl_Eval(interp, cmd.c_str());
    }
  } while (isPause);
}
int myResume(ClientData data, Tcl_Interp *interp, int argc,
             const char *argv[]) {
  cout << "[info] test2 ..." << endl;
  return TCL_OK;
}

int testCmd(ClientData data, Tcl_Interp *interp, int argc, const char *argv[]) {

  cout << "[info] do something 1" << endl;

  myPause();

  cout << "[info] do something 2" << endl;

  return TCL_OK;
}
int TclAppInit(Tcl_Interp *interp) {
  Tcl_CreateCommand(interp, "test2", myResume, NULL, NULL);
  Tcl_CreateCommand(interp, "testp", testCmd, NULL, NULL);
  return TCL_OK;
}

int main(int argc, char *argv[]) {
  interp = Tcl_CreateInterp();

  Tcl_Init(interp);

  Tcl_Main(argc, argv, TclAppInit);

  Tcl_DeleteInterp(interp);

  return 0;
}
