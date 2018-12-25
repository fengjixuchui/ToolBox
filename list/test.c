#include <criterion/criterion.h>
#include <signal.h>

#include "list.h"

TestSuite(list);

Test(list, new) {
    list_t *list = list_new();

    cr_assert(list);
    cr_assert(!list->first && !list->last);
    cr_assert(!list->size);
}

Test(list, push) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_push(list, &e);
    struct node *node = list->first;
    cr_assert(list->last == node);
    cr_assert(*(int *)node->data == e);
    cr_assert(list->size == 1);

    list_push(list, &e2);
    node = list->first;
    cr_assert(list->last != node);
    cr_assert(*(int *)node->data == e2);
    cr_assert(list->size == 2);
}

Test(list, pop) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_push(list, &e);
    list_push(list, &e2);

    int *p = list_pop(list);
    cr_assert(*p == 2);
    cr_assert(list->size == 1);
    cr_assert(list->first == list->last);

    p = list_pop(list);
    cr_assert(*p == 1);
    cr_assert(list->size == 0);
    cr_assert(list->first == list->last);

    /* Check if the list is empty */
    cr_assert(!list->first && !list->last);
}

Test(list, append) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_append(list, &e);
    struct node *node = list->first;
    cr_assert(list->last == node);
    cr_assert(*(int *)node->data == e);
    cr_assert(list->size == 1);

    list_append(list, &e2);
    node = list->last;
    cr_assert(list->first != node);
    cr_assert(*(int *)node->data == e2);
    cr_assert(list->size == 2);
}

Test(list, strip) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_append(list, &e);
    list_append(list, &e2);

    int *p = list_strip(list);
    cr_assert(*p == 2);
    cr_assert(list->size == 1);
    cr_assert(list->first == list->last);

    p = list_strip(list);
    cr_assert(*p == 1);
    cr_assert(list->size == 0);
    cr_assert(list->first == list->last);

    /* Check if the list is empty */
    cr_assert(!list->first && !list->last);
}

Test(list, clear) {
    list_t *list = list_new();

    int e = 0;

    list_push(list, &e);

    list_clear(list);

    /* Check if the list is empty */
    cr_assert(!list->first && !list->last);
}
