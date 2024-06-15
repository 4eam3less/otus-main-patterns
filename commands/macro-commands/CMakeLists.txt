set(TARGET_NAME test-macro-commands)

set(HEADERS
        macro-command.hpp
        macro-move.hpp
        command-exeption.hpp
        )

set(SOURCES
        macro-commands-tests.cpp
        )

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET_NAME}
        gtest
        gmock
        gtest_main
        )

enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})