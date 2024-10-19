
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
swig
)
