

add_executable(testDemo 
test_demo.cpp
)

target_link_libraries(testDemo
PRIVATE
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(NAME testDemo
    COMMAND "${EXECUTABLE_OUTPUT_PATH}/testDemo"
    WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}"
)