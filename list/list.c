#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "list.h"

static node_t *node_new(node_t *prev, node_t *next, void *data);
static void node_free(node_t *node);
static node_t *list_get_node(list_t *list, size_t index);

list_t *list_new()
{
    list_t *list = calloc(1, sizeof(*list));
    assert(list);

    return list;
}

void list_free(list_t *list)
{
    assert(list);

    list_clear(list);

    free(list);
}

static node_t *node_new(node_t *prev, node_t *next, void *data)
{
    node_t *node = calloc(1, sizeof(*node));
    assert(node);

    node->prev = prev;
    node->next = next;
    node->data = data;

    if (prev) {
        prev->next = node;
    }

    if (next) {
        next->prev = node;
    }

    return node;
}

static void node_free(node_t *node)
{
    assert(node);

    if (node->prev) {
        node->prev->next = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    }

    free(node);
}

static node_t *list_get_node(list_t *list, size_t index)
{
    assert(list);

    if (index >= list->size) {
        return NULL;
    }

    node_t *node;

    if (index <= list->size / 2) {
        node = list->first;
        for ( ; index > 0; --index) {
            node = node->next;
        }
    }
    else {
        index = list->size - index - 1;

        node = list->last;
        for ( ; index > 0; --index) {
            node = node->prev;
        }

    }

    return node;
}

void *list_get(list_t *list, size_t index)
{
    node_t *node = list_get_node(list, index);

    return node->data;
}

void list_push(list_t *list, void *data)
{
    assert(list);

    node_t *node = node_new(NULL, list->first, data);

    list->first = node;
    if (!list->last) {
        list->last = node;
    }

    ++list->size;
}

void list_append(list_t *list, void *data)
{
    assert(list);

    node_t *node = node_new(list->last, NULL, data);

    list->last = node;
    if (!list->first) {
        list->first = node;
    }

    ++list->size;
}

void list_insert(list_t *list, size_t index, void *data)
{
    assert(list);

    /* Out of bounds */
    if (index > list->size) {
        return;
    }

    /* Head insert */
    if (index == 0) {
        return list_push(list, data);
    }

    /* Tail insert */
    if (index == list->size) {
        return list_append(list, data);
    }

    node_t *ith = list_get_node(list, index);

    node_new(ith->prev, ith, data);

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
    else {
        list->first->prev = NULL;
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
    else {
        list->last->next = NULL;
    }

    --list->size;

    free(node);

    return data;
}

void *list_remove(list_t *list, size_t index)
{
    assert(list);

    /* Out of bounds */
    if(index > list->size) {
        return NULL;
    }

    /* Head pop */
    if (index == 0) {
        return list_pop(list);
    }

    /* Tail pop */
    if (index == list->size - 1) {
        return list_strip(list);
    }

    node_t *node = list_get_node(list, index);
    void *data = node->data;

    node_free(node);

    --list->size;

    return data;
}

void list_clear(list_t *list)
{
    assert(list);

    node_t *node = list->first;

    while (node) {
        node_t *next = node->next;

        free(node);

        node = next;
    }

    list->first = list->last = NULL;
}
