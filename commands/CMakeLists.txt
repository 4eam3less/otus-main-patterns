set(TARGET_NAME test-commands)

add_subdirectory(move)
add_subdirectory(rotate)
add_subdirectory(handler)
add_subdirectory(fuel-commands)
add_subdirectory(macro-commands)
add_subdirectory(adapters)

set(HEADERS
        command-interface.hpp
        commands.hpp
        handler/handler.hpp
        )

set(SOURCES
        commands-tests.cpp
        handler/handler.cpp
        )

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET_NAME}
        gtest
        gmock
        gtest_main
        )
        
enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})