#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "list.h"

list_t *list_new()
{
    list_t *list = calloc(1, sizeof(*list));
    assert(list);

    return list;
}

void list_push(list_t *list, void *data)
{
    assert(list);

    node_t *node = calloc(1, sizeof(*node));
    assert(node);

    node->data = data;
    node->next = list->first;
    list->first = node;

    ++list->size;
}

void list_append(list_t *list, void *data)
{
    assert(list);

    node_t *node = calloc(1, sizeof(*node));
    assert(node);

    node->data = data;
    node->prev = list->last;
    list->last = node;

    ++list->size;
}

void *list_pop(list_t *list)
{
    assert(list);

    node_t *node = list->first;

    void *data = node->data;

    list->first = node->next;

    --list->size;

    free(node);

    return data;
}

void *list_strip(list_t *list)
{
    assert(list);

    node_t *node = list->last;

    void *data = node->data;

    list->last = node->prev;

    --list->size;

    free(node);

    return data;
}