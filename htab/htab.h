#ifndef HTAB_H
#define HTAB_H

#include <stddef.h>

/* An htab need an hash function given by the user */
struct htab_elm {
    size_t key;
    void *data;
};

struct htab {
    size_t cap;
    size_t size;
    size_t (*hfunc)(void *);
    struct htab_elm *tab;
};

typedef struct htab htab_t;

/* Create a new htab */
htab_t *htab_new();
/* Delete the htab */
void htab_free(htab_t *htab, size_t (*hfunc)(void *));

/* Add a new element in the htab */
void htab_add(htab_t *htab, void *data);
/* Remove an element of the htab */
void *htab_del(htab_t *htab);
/* Find a match in the htab */
void *htab_find(htab_t *htab, void *data);

#endif
