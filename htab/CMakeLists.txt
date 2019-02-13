add_library(htab htab.c)

target_link_libraries(htab
    intrlist
)

add_executable(htab.test
    htab_test.c
    htab.c
)

target_link_libraries(htab.test
    criterion
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_compile_options(htab.test PRIVATE -g -fsanitize=address -fno-omit-frame-pointer -lcriterion)
