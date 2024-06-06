set(TARGET_NAME test-rotate)

set(HEADERS
        angle.hpp
        rotable.hpp
        rotate.hpp
        )

set(SOURCES
        angle.cpp
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