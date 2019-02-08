#include <criterion/criterion.h>
#include <stdio.h>

#include "list.h"

struct test {
    int i;
    list_t list;
};

Test(intrlist, list_init) {
    list_t list;
    list_init(&list);

    cr_assert(list.next == &list && list.prev == &list);
}

Test(intrlist, list_push) {
    struct test list;
    struct test node1;
    struct test node2;
    list_init(&list.list);

    list_push(&list.list, &node1.list);
    cr_assert(list.list.next == &node1.list && list.list.prev == &node1.list);
    cr_assert(node1.list.next == &list.list && node1.list.prev == &list.list);

    list_push(&list.list, &node2.list);
    cr_assert(list.list.next == &node2.list && list.list.prev == &node1.list);
    cr_assert(node2.list.next == &node1.list && node2.list.prev == &list.list);
    cr_assert(node1.list.next == &list.list && node1.list.prev == &node2.list);
}

Test(intrlist, list_append) {
    struct test list;
    struct test node1;
    struct test node2;
    list_init(&list.list);

    list_append(&list.list, &node1.list);
    cr_assert(list.list.next == &node1.list && list.list.prev == &node1.list);
    cr_assert(node1.list.next == &list.list && node1.list.prev == &list.list);

    list_append(&list.list, &node2.list);
    cr_assert(list.list.next == &node1.list && list.list.prev == &node2.list);
    cr_assert(node2.list.next == &list.list && node2.list.prev == &node1.list);
    cr_assert(node1.list.next == &node2.list && node1.list.prev == &list.list);
}

Test(intrlist, list_remove) {
    struct test list;
    struct test node1;
    struct test node2;
    list_init(&list.list);

    list_push(&list.list, &node1.list);
    list_push(&list.list, &node2.list);

    list_t *rm = list_remove(&node2.list);
    cr_assert(rm == &node2.list);
    cr_assert(node2.list.next == node2.list.prev);
    cr_assert(list.list.next == &node1.list && list.list.prev == &node1.list);

    rm = list_remove(&node1.list);
    cr_assert(rm == &node1.list);
    cr_assert(node1.list.next == node1.list.prev);
    cr_assert(list.list.next == &list.list && list.list.prev == &list.list);

    rm = list_remove(&node1.list);
    cr_assert(rm == NULL);

    rm = list_remove(&list.list);
    cr_assert(rm == NULL);
}

Test(intrlist, list_pop) {
    struct test list;
    struct test node1;
    struct test node2;
    list_init(&list.list);

    list_push(&list.list, &node1.list);
    list_push(&list.list, &node2.list);

    list_t *rm = list_pop(&list.list);
    cr_assert(rm == &node2.list);

    rm = list_pop(&list.list);
    cr_assert(rm == &node1.list);
}

Test(intrlist, list_strip) {
    struct test list;
    struct test node1;
    struct test node2;
    list_init(&list.list);

    list_push(&list.list, &node1.list);
    list_push(&list.list, &node2.list);

    list_t *rm = list_strip(&list.list);
    cr_assert(rm == &node1.list);

    rm = list_strip(&list.list);
    cr_assert(rm == &node2.list);
}

Test(intrlist, list_entry) {
    struct test list;

    struct test *ret = list_entry(&list.list, struct test, list);

    cr_assert(ret == &list);
}

Test(intrlist, list_foreach) {
    struct test list;
    struct test test1;
    struct test test2;
    struct test test3;

    test1.i = 1;
    test2.i = 2;
    test3.i = 3;

    list_init(&list.list);

    list_push(&list.list, &test2.list);
    list_push(&list.list, &test1.list);
    list_append(&list.list, &test3.list);

    int index = 1;
    struct test *pos;
    list_foreach(&list.list, pos, list) {
        cr_assert(pos->i == index++);
    }
}

Test(intrlist, list_foreach_reverse) {
    struct test list;
    struct test test1;
    struct test test2;
    struct test test3;

    test1.i = 1;
    test2.i = 2;
    test3.i = 3;

    list_init(&list.list);

    list_push(&list.list, &test2.list);
    list_push(&list.list, &test1.list);
    list_append(&list.list, &test3.list);

    int index = 3;
    struct test *pos;
    list_foreach_reverse(&list.list, pos, list) {
        cr_assert(pos->i == index--);
    }
}
