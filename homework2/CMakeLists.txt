set(TARGET_NAME test-move)

set(HEADERS
        vec2.hpp
        movable.hpp
        move.hpp
        angle.hpp
        rotable.hpp
        rotate.hpp
        )

set(SOURCES
        tests.cpp
        angle.cpp
        )

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET_NAME}
        gtest
        gmock
        gtest_main
        )

enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})