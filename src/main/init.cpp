
#include "init.h"
#include "tcl.h"
#include "tclreadline.h"
#include "testCmdMgr.h"
#include <array>
#include <cstring>
#include <stdlib.h>

#ifdef ENABLE_READLINE
static int tclReadlineInit(Tcl_Interp *interp) {
  std::array<const char *, 6> readline_cmds = {
      // "history event",
      "eval $auto_index(::tclreadline::ScriptCompleter)",
      "::tclreadline::readline builtincompleter true",
      "::tclreadline::readline customcompleter ::tclreadline::ScriptCompleter",
      "proc ::tclreadline::prompt1 {} { return \"App> \" }",
      "proc ::tclreadline::prompt2 {} { return \"...> \" }",
      "::tclreadline::Loop"};

  for (auto cmd : readline_cmds) {
    if (TCL_ERROR == Tcl_Eval(interp, cmd)) {
      printf("eval cmd: %s error\n", cmd);
      return TCL_ERROR;
    }
  }
  return TCL_OK;
}
#endif

static int TclAppInit(Tcl_Interp *interp) {
  if (Tcl_Init(interp) == TCL_ERROR) {
    return TCL_ERROR;
  }
#ifdef ENABLE_TCLX
  if (Tclx_Init(interp) == TCL_ERROR) {
    return TCL_ERROR;
  }
#endif
#ifdef ENABLE_READLINE
  if (Tclreadline_Init(interp) == TCL_ERROR) {
    return TCL_ERROR;
  }
  Tcl_StaticPackage(interp, "tclreadline", Tclreadline_Init,
                    Tclreadline_SafeInit);
  if (Tcl_EvalFile(interp, TCLRL_LIBRARY "/tclreadlineInit.tcl") != TCL_OK) {
    printf("Failed to load tclreadline\n");
  }
#endif
  // initialize command
  App::CmdInterface::Instance()->Initialize(interp);

#ifdef ENABLE_READLINE
  if (TCL_ERROR == tclReadlineInit(interp)) {
    printf("init tclreadline error\n");
  }
#endif
  return TCL_OK;
}

void InitRoute() {}

int InitRoute(int args, char **argv) {
  // TODO: deal with arguments

  Tcl_Main(1, argv, TclAppInit);
  return 0;
}

char *unencode(const char *inits[]) {
  size_t length = 0;
  for (const char **e = inits; *e; e++) {
    const char *init = *e;
    length += strlen(init);
  }
  char *unencoded = new char[length / 3 + 1];
  char *u = unencoded;
  for (const char **e = inits; *e; e++) {
    const char *init = *e;
    size_t init_length = strlen(init);
    for (const char *s = init; s < &init[init_length]; s += 3) {
      char code[4] = {s[0], s[1], s[2], '\0'};
      char ch = atoi(code);
      *u++ = ch;
    }
  }
  *u = '\0';
  return unencoded;
}

void evalTclInit(Tcl_Interp *interp, const char *inits[]) {
  char *unencoded = unencode(inits);
  // printf("unencoded==> %s\n", unencoded);
  if (Tcl_Eval(interp, unencoded) != TCL_OK) {
    Tcl_Eval(interp, "$errorInfo");
    const char *tclErrInfo = Tcl_GetStringResult(interp);
    fprintf(stderr, "Error: TCL init script: %s.\n", tclErrInfo);
    fprintf(stderr, "       Try deleting TclInitVar.cc and rebuilding.\n");
    exit(0);
  }
  delete[] unencoded;
}
