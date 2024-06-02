cmake_minimum_required(VERSION 3.25)
project(otus_main_patterns)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.0
)
FetchContent_MakeAvailable(googletest)

#add_subdirectory("quadratic-equation")
#add_subdirectory("move")
add_subdirectory("commands")