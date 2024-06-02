set(TARGET_NAME test-move)

set(HEADERS
        move/vec2.hpp
        move/movable.hpp
        move/move.hpp
        rotate/angle.hpp
        rotate/rotable.hpp
        rotate/rotate.hpp
        )

set(SOURCES
        move/tests.cpp
        rotate/angle.cpp
        rotate/tests.cpp
        )

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET_NAME}
        gtest
        gmock
        gtest_main
        )

enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})