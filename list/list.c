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

void list_free(list_t *list)
{
    list_clear(list);

    free(list);
}

void list_push(list_t *list, void *data)
{
    assert(list);

    node_t *node = calloc(1, sizeof(*node));
    assert(node);

    node->data = data;
    node->next = list->first;

    list->first = node;
    if (!list->last) {
        list->last = node;
    }

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
    if (!list->first) {
        list->first = node;
    }

    ++list->size;
}

void *list_pop(list_t *list)
{
    assert(list);

    node_t *node = list->first;

    void *data = node->data;

    list->first = node->next;
    if (!list->first) {
        list->last = NULL;
    }

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
    if (!list->last) {
        list->first= NULL;
    }

    --list->size;

    free(node);

    return data;
}

void list_clear(list_t *list)
{
    node_t *node = list->first;

    while (node) {
        node_t *next = node->next;

        free(node);

        node = next;
    }

    list->first = list->last = NULL;
}
