#include <criterion/criterion.h>

#include "list.h"

Test(list_new, new) {
    list_t *list = list_new();
    cr_assert(!list);
    cr_assert(!list->first && !list->last);
    cr_assert(!list->size);
}

Test(list_push, push) {
    list_t *list = list_new();
    int el = 1;
    list_push(list, &el);
    cr_assert(list->first && list->size == 1);
}

/* Test(list_pop, pop) { */
/*     list_t *list = list_new(); */
/*     int *e = list_pop(list); */
/*     cr_assert(*e == 1 && list->size == 0); */
/* } */
