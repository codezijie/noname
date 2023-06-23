file(GLOB_RECURSE GUI_SOURCES *.cpp)

add_executable(App
${GUI_SOURCES}
)

target_compile_definitions(App
PRIVATE
ENABLE_READLINE
)

target_link_libraries(App
PRIVATE
${TCL_LIBRARY}
${TCL_READLINE_LIBRARY}

cmd
app_gui
swig_app
Qt6::Gui
Qt6::Widgets
xkbcommon
)

set_target_properties(App PROPERTIES AUTOMOC true)