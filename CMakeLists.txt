cmake_minimum_required (VERSION 3.0)
project (ToolBox LANGUAGES C)

add_compile_options(-Wall -Wextra -std=c99)

add_subdirectory(list)

add_custom_target(test
    COMMAND ${CMAKE_SOURCE_DIR}/test.sh
    DEPENDS list.test
    COMMENT "Running test ..."
)
