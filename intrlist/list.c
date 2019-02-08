#include <stdlib.h>

#include <assert.h>

#include "list.h"

list_t *list_new()
{
    list_t *list = malloc(sizeof(*list));

    if (!list) {
        return NULL;
    }

    list->prev = list;
    list->next = list;

    return list;
}

void list_init(list_t *list)
{
    list->prev = list;
    list->next = list;
}

void list_push(list_t *list, list_t *node)
{
    assert(list);
    assert(node);

    node->prev = list;
    node->next = list->next;
    list->next = node;
    node->next->prev = node;
}


void list_append(list_t *list, list_t *node)
{
    assert(list);
    assert(node);

    node->next = list;
    node->prev = list->prev;
    list->prev = node;
    node->prev->next = node;
}

list_t *list_remove(list_t *elm)
{
    assert(elm);

    if (elm->next == elm && elm->prev == elm) {
        return NULL;
    }

    elm->prev->next = elm->next;
    elm->next->prev = elm->prev;

    elm->prev = elm;
    elm->next = elm;

    return elm;
}
