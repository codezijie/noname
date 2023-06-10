
find_package(TCL)

set(TCL_READLINE_POSSIBLE_NAMES tclreadline-2.1.0
    tclreadline-2.3.2 tclreadline-2.3.6 tclreadline-2.3.7 tclreadline-2.3.8
    )
find_library(TCL_READLINE_LIBRARY
  NAMES tclreadline ${TCL_READLINE_POSSIBLE_NAMES}
  PATHS ${TCL_LIB_PATHS}
  )
if (TCL_READLINE_LIBRARY)
  message(STATUS "TCL readline library: ${TCL_READLINE_LIBRARY}")
endif()

find_path(TCL_READLINE_H tclreadline.h)
if (TCL_READLINE_H)
  message(STATUS "TCL readline header: ${TCL_READLINE_H}")
endif()

option(BUILD_TCLX "Build with tclX included" ON)
if (BUILD_TCLX AND TCLX_LIBRARY)
  message(STATUS "TclX library: ${TCLX_LIBRARY}")
endif()
if (BUILD_TCLX AND TCLX_H)
  message(STATUS "TclX header: ${TCLX_H}")
endif()

find_package(SWIG 3.0 REQUIRED)
include(UseSWIG)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS serialization system thread unit_test_framework)
message(STATUS "Boost_VERSION: ${Boost_VERSION}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "boost_dir: " ${Boost_DIR})

find_package(FMT REQUIRED)

include_directories(${APP_ROOT_HOME}/include)
include_directories(${APP_ROOT_HOME}/include/cmd)
include_directories(${APP_ROOT_HOME}/include/utility)
include_directories(${APP_ROOT_HOME}/include/geometry)

include_directories(${TCL_INCLUDE_PATH})
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(database)
add_subdirectory(main)
add_subdirectory(cmd)
add_subdirectory(test)
add_subdirectory(geometry)
add_subdirectory(util)