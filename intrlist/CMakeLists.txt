add_library(intrlist list.c)

add_executable(intrlist.test
    test.c
    list.c
)

target_link_libraries(intrlist.test
    criterion
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_compile_options(intrlist.test PRIVATE -g -fsanitize=address -fno-omit-frame-pointer -lcriterion)
