set(TARGET_NAME solve)

add_subdirectory(tests)

set(HEADERS quadratic-equation.hpp)

set(SOURCES main.cpp
        quadratic-equation.cpp
        main.cpp)

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})