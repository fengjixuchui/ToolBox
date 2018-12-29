#include <criterion/criterion.h>
#include <signal.h>

#include "list.h"

TestSuite(list);

Test(list, new) {
    list_t *list = list_new();

    cr_assert(list);
    cr_assert(!list->first && !list->last);
    cr_assert(!list->size);

    list_free(list);
}

Test(list, push) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_push(list, &e);
    struct node *node = list->first;
    /* Test if the first node is pointed by first and last */
    cr_assert(list->last == node);
    /* Test extremity form node */
    cr_assert(!node->next && !node->prev);
    /* Check stored value */
    cr_assert(*(int *)node->data == e);
    /* Check list size */
    cr_assert(list->size == 1);

    list_push(list, &e2);
    struct node *node2 = list->first;
    /* Test if the first node is pointed only by first */
    cr_assert(list->last != node2);
    /* Test extremity form node */
    cr_assert(!node2->prev);
    /* Test interconnexion between nodes */
    cr_assert(node->prev == node2 && node2->next == node);
    /* Check stored value */
    cr_assert(*(int *)node2->data == e2);
    /* Check list size */
    cr_assert(list->size == 2);

    list_free(list);
}

Test(list, pop) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_push(list, &e);
    list_push(list, &e2);

    int *p = list_pop(list);
    cr_assert(*p == e2);
    cr_assert(list->size == 1);
    cr_assert(list->first == list->last);

    p = list_pop(list);
    cr_assert(*p == e);
    cr_assert(list->size == 0);
    cr_assert(list->first == list->last);

    /* Check if the list is empty */
    cr_assert(!list->first && !list->last);

    list_free(list);
}

Test(list, append) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_append(list, &e);
    struct node *node = list->last;
    /* Test if the first node is pointed by first and last */
    cr_assert(list->first == node);
    /* Test extremity form node */
    cr_assert(!node->next && !node->prev);
    /* Check stored value */
    cr_assert(*(int *)node->data == e);
    /* Check list size */
    cr_assert(list->size == 1);

    list_append(list, &e2);
    struct node *node2 = list->last;
    /* Test if the first node is only pointed by last */
    cr_assert(list->first != node2);
    /* Test extremity form node */
    cr_assert(!node2->next);
    /* Test interconnexion between nodes */
    cr_assert(node2->prev == node && node->next == node2);
    /* Check stored value */
    cr_assert(*(int *)node2->data == e2);
    /* Check list size */
    cr_assert(list->size == 2);

    list_free(list);
}

Test(list, strip) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;

    list_append(list, &e);
    list_append(list, &e2);

    int *p = list_strip(list);
    cr_assert(*p == e2);
    cr_assert(list->size == 1);
    cr_assert(list->first == list->last);

    p = list_strip(list);
    cr_assert(*p == e);
    cr_assert(list->size == 0);
    cr_assert(list->first == list->last);

    /* Check if the list is empty */
    cr_assert(!list->first && !list->last);

    list_free(list);
}

Test(list, insert) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;
    int e3 = 3;

    list_push(list, &e);
    list_append(list, &e3);

    list_insert(list, 1, &e2);
    struct node *node = list->first->next;
    /* Test reverse linkage */
    cr_assert(list->last->prev == node);
    /* Test interconnexion between nodes */
    cr_assert(node->prev == list->first && node->next == list->last);
    cr_assert(list->first->next == node && list->last->prev == node);
    /* Check stored value */
    cr_assert(*(int *)node->data == e2);
    /* Check order */
    cr_assert(*(int *)list->first->data == e && *(int *)list->last->data == e3);
    /* Check list size */
    cr_assert(list->size == 3);

    free(list);
}

Test(list, get) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;
    int e3 = 3;

    list_append(list, &e);
    list_append(list, &e2);
    list_append(list, &e3);

    int *p = list_get(list, 1);
    /* Check stored value */
    cr_assert(*p == e2);

    free(list);
}

Test(list, remove) {
    list_t *list = list_new();

    int e = 1;
    int e2 = 2;
    int e3 = 3;

    list_append(list, &e);
    list_append(list, &e2);
    list_append(list, &e3);

    int *p = list_remove(list, 1);
    /* Check stored value */
    cr_assert(*p == e2);
    /* Test interconnexion between nodes */
    cr_assert(list->first->next == list->last && list->last->prev == list->first);
    /* Check list size */
    cr_assert(list->size == 2);

    free(list);
}

Test(list, clear) {
    list_t *list = list_new();

    int e = 0;

    list_push(list, &e);

    list_clear(list);

    /* Check if the list is empty */
    cr_assert(!list->first && !list->last);

    list_free(list);
}
