set(TARGET_NAME IoC)

set(HEADERS IoC.hpp)

set(SOURCES IoC.cpp)

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})

# target_link_libraries(${TARGET_NAME}
#         gtest
#         gtest_main
#         )
# enable_testing()
# add_test(${TARGET_NAME} ${TARGET_NAME})
