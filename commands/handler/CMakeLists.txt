set(TARGET_NAME test-handler)

set(HEADERS
        handler.hpp
        handler.cpp
        )

set(SOURCES
        handler.cpp
        handler-tests.cpp
        )

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET_NAME}
        gtest
        gmock
        gtest_main
        )

enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})