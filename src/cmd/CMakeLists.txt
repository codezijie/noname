include("swig_lib")
include("messages")

swig_lib(NAME       swig_app
         NAMESPACE  app
         I_FILE     app.i
         SCRIPTS    test.tcl
                    utility.tcl
)


add_library(cmd
    testCmdMgr.cpp
    testCmd.cpp
)