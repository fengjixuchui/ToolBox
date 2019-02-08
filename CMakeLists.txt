cmake_minimum_required (VERSION 3.0)
project (ToolBox LANGUAGES C)

add_compile_options(-Wall -Wextra -std=c99)

add_subdirectory(list)
add_subdirectory(vect)
add_subdirectory(intrlist)

add_custom_target(test ALL
     COMMAND ${CMAKE_SOURCE_DIR}/test.sh
     DEPENDS list list.test vect vect.test intrlist intrlist.test
     COMMENT "Running test ..."
)
