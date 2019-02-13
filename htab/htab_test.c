#include <criterion/criterion.h>

#include "htab.h"

struct tuple {
    const char *str;
    size_t val;
};

static size_t hfunc(void *key)
{
    const char *key_str = key;
    size_t hash = 0;
    for (size_t i = 0 ; key_str[i] != '\0' ; i++)
    {
        hash = 31*hash + key_str[i];
    }

    return hash;
}

static bool cmpfunc(void *key1, void *key2)
{
    return !strcmp((char *)key1, (char *)key2);
}

Test(htab, htab_new) {
    htab_t *htab = htab_new(hfunc, cmpfunc);

    cr_assert(htab->cap == 1);
    cr_assert(htab->size == 0);
    cr_assert(htab->nb_elm == 0);
    cr_assert(htab->hfunc);
    cr_assert(htab->cmpfunc);
    cr_assert(htab->tab);
}

Test(htab, htab_add) {
    htab_t *htab = htab_new(hfunc, cmpfunc);

    struct tuple t1 = {"1", 1};
    struct tuple t2 = {"1", 2};
    struct tuple t3 = {"2", 3};

    htab_add(htab, &t1.str, &t1);
    cr_assert(htab->cap == 1);
    cr_assert(htab->size == 1);
    cr_assert(htab->nb_elm == 1);
}
