#ifndef LIST_H
#define LIST_h

struct node {
    struct node *next, *prev;
    void *data;
};

struct list {
    struct node *first, *last;
};

typedef struct list list_t;


list_t *list_new(void);

void list_push(list_t *list, void *data);
void list_append(list_t *list, void *data);

list_t *list_pop(list_t *list);

#endif
