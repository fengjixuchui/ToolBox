add_library(htab htab.c)

target_link_libraries(htab
    intrlist
)

add_executable(htab.test
    htab.c
    htab_test.c
)

target_link_libraries(htab.test
    intrlist
    criterion
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_compile_options(htab.test PRIVATE -g -fsanitize=address -fno-omit-frame-pointer -lcriterion)
