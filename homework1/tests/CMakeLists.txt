set(TARGET_NAME test-solve)

add_executable(${TARGET_NAME}
        ../quadratic-equation.cpp
        tests.cpp)

target_link_libraries(${TARGET_NAME}
        gtest
        gtest_main
        )
enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})