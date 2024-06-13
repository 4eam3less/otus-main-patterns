set(TARGET_NAME test-fuel-commands)

set(HEADERS
        fuel-manager-interface.hpp
        fuel-commands.hpp
        mock-fuel.hpp
        )

set(SOURCES
        fuel-commands-tests.cpp
        )

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET_NAME}
        gtest
        gmock
        gtest_main
        )

enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})