include("swig_lib")
include("messages")

swig_lib(NAME       swig_route
         NAMESPACE  route
         I_FILE     hx_route.i
         SCRIPTS    hx_route.tcl
                    utility.tcl
)


add_library(cmd
    testCmdMgr.cpp
    testCmd.cpp
)