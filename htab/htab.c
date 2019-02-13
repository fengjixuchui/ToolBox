#include <stdlib.h>

#include <assert.h>

#include "htab.h"

static void htab_extend(htab_t *htab);
static struct bucket *buck_new(void *key, void *elm);
static inline struct bucket *head_buck(htab_t *htab, size_t index);
static struct bucket *find_buck(htab_t *htab, void *key);

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

void htab_add(htab_t *htab, void *key, void *elm)
{
    assert(htab);
    assert(key);
    assert(elm);

    /* If the htab is full, extend */
    if (htab->size == htab->cap) {
        htab_extend(htab);
    }

    /* Compute index, create new element and find the head */
    size_t index = htab->hfunc(key) % htab->cap;
    struct bucket *buck = buck_new(key, elm);
    struct bucket *head = head_buck(htab, index);

    if (intrlist_isempty(&head->list)) {
        ++htab->size;
    }
    else {
        /* Cheak for doublon */
        struct bucket *buck_for;
        intrlist_foreach(&head->list, buck_for, list) {
            if (htab->cmpfunc(buck->key, buck_for->key)) {
                free(buck);
                return;
            }
        }
    }

    /* No doublon or empty bucket */
    intrlist_push(&head->list, &buck->list);
    ++htab->nb_elm;
}

void *htab_find(htab_t *htab, void *key)
{
    struct bucket *buck = find_buck(htab, key);
    if (!buck) {
        return NULL;
    }

    return buck->elm;
}

void *htab_del(htab_t *htab, void *key)
{
    struct bucket *buck = find_buck(htab, key);
    if (!buck) {
        return NULL;
    }

    intrlist_remove(&buck->list);
    return buck->elm;
}

static struct bucket *find_buck(htab_t *htab, void *key)
{
    size_t index = htab->hfunc(key);
    struct bucket *head = head_buck(htab, index);

    struct bucket *buck;
    intrlist_foreach(&head->list, buck, list) {
        if (htab->cmpfunc(key, buck->key)) {
            return buck;
        }
    }

    return NULL;
}

static void htab_extend(htab_t *htab)
{
    size_t old_cap = htab->cap;

    htab->cap *= 2;
    htab->tab = realloc(htab->tab, htab->cap * sizeof(*htab->tab));

    /* Init new buckets */
    for (size_t i = old_cap; i < htab->cap; ++i) {
        intrlist_init(&htab->tab[i].list);
    }

    /* Relocate all entries if needed */
    for (size_t i = 0; i < old_cap; ++i) {
        struct bucket *head = head_buck(htab, i);

        struct bucket *buck;
        struct bucket *prev = head;
        intrlist_foreach(&head->list, buck, list) {
            size_t new_index = htab->hfunc(buck->elm) % htab->cap;
            if (new_index != i) {
                /* Remove and push in new index */
                intrlist_remove(&buck->list);
                intrlist_push(&htab->tab[new_index].list, &buck->list);
                buck = prev;
            }

            prev = buck;
        }
    }
}

static struct bucket *buck_new(void *key, void *elm)
{
    struct bucket *buck = malloc(sizeof(*buck));
    if (!elm) {
        free(buck);
        return NULL;
    }

    buck->key = key;
    buck->elm = elm;

    return buck;
}

static inline struct bucket *head_buck(htab_t *htab, size_t index)
{
    return &htab->tab[index];
}
