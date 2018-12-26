add_library(list list.c)

add_executable(list.test
    test.c
)

target_link_libraries(list.test
    list
    criterion
)
