file(GLOB_RECURSE GUI_SOURCES *.cpp)

add_library(app_gui
  ${GUI_SOURCES}
)