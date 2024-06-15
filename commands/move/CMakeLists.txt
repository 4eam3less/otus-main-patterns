set(TARGET_NAME test-move)

set(HEADERS
        vec2.hpp
        movable.hpp
        move.hpp
        )

set(SOURCES
        tests.cpp
        )

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET_NAME}
        gtest
        gmock
        gtest_main
        )

enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})