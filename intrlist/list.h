#ifndef LIST_H
#define LIST_H

#include <stddef.h>

struct list {
    struct list *prev;
    struct list *next;
};

typedef struct list list_t;

#define typeof __typeof__

#define container_of(ptr, type, member) ({			\
        const typeof(((type *)0)->member) * __mptr = (ptr);	\
        (type *)((char *)__mptr - offsetof(type, member)); })

#define list_entry(head, type, member) container_of(head, type, member)

#define list_foreach(list, cur, member) \
        for (cur = list_entry((list)->next, typeof(*cur), member); \
             &cur->member != list; \
             cur = list_entry(cur->member.next, typeof(*cur), member))

#define list_foreach_reverse(list, cur, member) \
        for (cur = list_entry((list)->prev, typeof(*cur), member); \
             &cur->member != list; \
             cur = list_entry(cur->member.prev, typeof(*cur), member))

/* Init sentinel */
void list_init(list_t *list);

void list_push(list_t *list, list_t *node);
void list_append(list_t *list, list_t *node);

list_t *list_remove(list_t *elm);
#define list_pop(list) list_remove((list)->next)
#define list_strip(list) list_remove((list)->prev)

#endif
