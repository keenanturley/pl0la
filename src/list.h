#ifndef LIST_H
#define LIST_H

#include "token.h"

/* Array List implementation */
typedef struct list {
    token *tokens; // Dynamic array of tokens
    int size;
    int capacity;
} list;

const int DEFAULT_INITIAL_CAPACITY = 8;

list *create_list();

list *create_list(int initial_capacity);

void ensure_capacity(list *l);

void add(list *l, token t);

token *get(list *l, int i);

list *free_list(list *l);

#endif /* LIST_H */
