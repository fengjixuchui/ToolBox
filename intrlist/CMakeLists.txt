add_library(intrlist intrlist.c)

add_executable(intrlist.test
    test.c
    intrlist.c
)

target_link_libraries(intrlist.test
    criterion
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_compile_options(intrlist.test PRIVATE -g -fsanitize=address -fno-omit-frame-pointer -lcriterion)
