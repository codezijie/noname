cmake_minimum_required (VERSION 3.9)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
# Use standard target names
cmake_policy(SET CMP0078 NEW)
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.14)
# Allows SWIG_MODULE_NAME to be set
cmake_policy(SET CMP0086 NEW)
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.12)
# Allows <PackageName>_ROOT to be used
cmake_policy(SET CMP0074 NEW)
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.10)
# Allow AUTOUIC on generated source
cmake_policy(SET CMP0071 NEW)
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
# option() behavior
cmake_policy(SET CMP0077 NEW)
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.10)
# Let AUTOMOC and AUTOUIC process GENERATED files.
cmake_policy(SET CMP0071 NEW)
endif()

project(App VERSION 0.0.1
  LANGUAGES CXX
)

set(APP_ROOT_HOME ${PROJECT_SOURCE_DIR}/) 
set(APP_INCLUDE_HOME ${APP_ROOT_HOME}/include)

list(APPEND CMAKE_MODULE_PATH "${APP_ROOT_HOME}/cmake")
include(GetGitInfo)
set(GIT_HASH "")
get_git_hash(GIT_HASH)
message(STATUS "Git hash is ${GIT_HASH}")

# git_BRANCh
set(GIT_BRANCH "")
get_git_branch(GIT_BRANCH)
message(STATUS "Git branch is ${GIT_BRANCH}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# configure a header file to pass some of the CMake settings
configure_file(
  ${APP_ROOT_HOME}/include/version.hh.cmake
  ${APP_ROOT_HOME}/include/version.hh
  )

set(FOR_PUBLISH "for publish" ON)


# Default to bulding optimnized/release executable.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RELEASE)
  set(APP_BUILD_TYPE build_release)
elseif(CMAKE_BUILD_TYPE MATCHES "DEBUG")
  set(APP_BUILD_TYPE build_debug)
  add_definitions(-DDEBUG)
else()
  set(APP_BUILD_TYPE build_release)
endif()


set(CMAKE_VERBOSE_MAKEFILE ON)
# Default c++ standard used unless otherwise specified in target_compile_features.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable compiler specific extensions like gnu++11.
set(CMAKE_CXX_EXTENSIONS OFF)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
SET(INCLUDE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include)

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

if (FOR_PUBLISH AND CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  add_definitions(-DNDEBUG)
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os -Wall -s")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -Wall -s")
endif()

add_compile_options("-fPIC")

option(GUI "build gui" ON)

# Ask CMake to output a compile_commands.json file for use with things like clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# fix clangd " 'stddef.h' file not found " error
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

enable_testing()

add_subdirectory(src)
