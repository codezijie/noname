file(GLOB_RECURSE GUI_SOURCES *.cpp)


add_library(gui
${GUI_SOURCES}
)

set_target_properties(gui PROPERTIES AUTOMOC true)
