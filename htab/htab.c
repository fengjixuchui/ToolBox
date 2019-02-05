#include <stdlib.h>

#include <assert.h>

#include "htab.h"

static struct htab_elm *elm_new(size_t key, void *data, struct htab_elm *next);
static inline struct htab_elm *head_elm(htab_t *htab, size_t index);

htab_t *htab_new(size_t (*hfunc)(void *), bool (*cmpfunc)(void *, void *))
{
    assert(hfunc);

    htab_t *htab = malloc(sizeof(*htab));

    htab->cap = 1;
    htab->size = 0;
    htab->hfunc = hfunc;
    htab->cmpfunc = cmpfunc;

    htab->tab = calloc(htab->cap, sizeof(*htab->tab));

    return htab;
}

void htab_add(htab_t *htab, void *data)
{
    assert(htab);
    assert(data);

    /* If the htab is full, extend */
    if (htab->size == htab->cap) {

    }

    /* Index from hfunc */
    size_t index = htab->hfunc(data) % htab->cap;

    /* Get head of list */
    struct htab_elm *elm = head_elm(htab, index);
    if (!elm) {
        /* Fill new space */
        htab->tab[index] = elm_new(index, data, NULL);
    }
    else {
        /* Push front */
        elm->next = elm_new(index, data, elm->next);
        assert(elm->next);
    }
}

void *htab_del(htab_t *htab, void *data)
{
    size_t index = htab->hfunc(data) % htab->cap;

    struct htab_elm *elm = head_elm(htab, index);


}


static struct htab_elm *elm_new(size_t key, void *data, struct htab_elm *next)
{
    assert(data);
    assert(next);

    struct htab_elm *elm = malloc(sizeof(*elm));

    elm->key = key;
    elm->data = data;
    elm->next = next;

    return elm;
}

static inline struct htab_elm *head_elm(htab_t *htab, size_t index)
{
    return htab->tab[index];
}
