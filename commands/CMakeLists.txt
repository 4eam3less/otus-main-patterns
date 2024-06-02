set(HEADERS
        command-interface.hpp
        commands.hpp
        handler.hpp
        )

set(SOURCES-HANDLER
        handler-tests.cpp
        commands-tests.cpp
        )
set(SOURCES-COMMANDS
        handler-tests.cpp
        commands-tests.cpp
        )

add_executable(test-handler 
        ${HEADERS} 
        ${SOURCES-HANDLER}
        )

add_executable(test-commands
        ${HEADERS} 
        ${SOURCES-COMMANDS}
        )

target_link_libraries(test-handler
        gtest
        gmock
        gtest_main
        )

target_link_libraries(test-commands
        gtest
        gmock
        gtest_main
        )

enable_testing()

add_test(test-handler test-handler)
add_test(test-commands test-commands)