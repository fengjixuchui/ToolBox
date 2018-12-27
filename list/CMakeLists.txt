add_library(list list.c)

add_executable(list.test
    test.c
    list.c
)

target_link_libraries(list.test
    criterion
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_compile_options(list.test PRIVATE -g -fsanitize=address -fno-omit-frame-pointer -lcriterion)
