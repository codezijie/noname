
add_executable(App
main.cpp
init.cpp
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
swig_route
Qt6::Gui
Qt6::Widgets
)
