#include <stdlib.h>

#include <assert.h>

#include "htab.h"

static void htab_extend(htab_t *htab);
static struct bucket *elm_new(void *elm);
static inline struct bucket *head_elm(htab_t *htab, size_t index);

htab_t *htab_new(size_t (*hfunc)(void *), bool (*cmpfunc)(void *, void *))
{
    assert(hfunc);

    htab_t *htab = malloc(sizeof(*htab));

    htab->cap = 1;
    htab->size = 0;
    htab->nb_elm = 0;
    htab->hfunc = hfunc;
    htab->cmpfunc = cmpfunc;

    htab->tab = calloc(htab->cap, sizeof(*htab->tab));

    for (size_t i = 0; i < htab->cap; ++i) {
        intrlist_init(&htab->tab[i].list);
    }

    return htab;
}

void htab_add(htab_t *htab, void *elm)
{
    assert(htab);
    assert(elm);

    /* If the htab is full, extend */
    if (htab->size == htab->cap) {
        htab_extend(htab);
    }

    /* Compute index, create new element and find the head */
    size_t index = htab->hfunc(elm) % htab->cap;
    struct bucket *buck = elm_new(elm);
    struct bucket *head = head_elm(htab, index);

    if (intrlist_isempty(&head->list)) {
        ++htab->size;
    }
    else {
        /* Cheak for doublon */
        struct bucket *buck_for;
        intrlist_foreach(&head->list, buck_for, list) {
            if (htab->cmpfunc(buck->elm, buck_for->elm)) {
                free(buck);
                return;
            }
        }
    }

    /* No doublon or empty bucket */
    intrlist_push(&head->list, &buck->list);
    ++htab->nb_elm;
}

static struct bucket *elm_new(void *elm)
{
    struct bucket *buck = malloc(sizeof(*buck));
    if (!elm) {
        return NULL;
    }

    buck->elm = elm;

    return buck;
}

static inline struct bucket *head_elm(htab_t *htab, size_t index)
{
    return &htab->tab[index];
}
