include("swig_lib")
include("messages")

swig_lib(NAME       swig
         NAMESPACE  app 
         I_FILE     testCmd.i
         SCRIPTS    testCmd.tcl
                    utility.tcl
)


add_library(cmd
    testCmdMgr.cpp
    testCmd.cpp
)
