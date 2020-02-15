#include <stdlib.h>
#include <stdio.h>
#include "list.h"

list *create_list() {
    return create_list(DEFAULT_INITIAL_CAPACITY);
}

list *create_list(int initial_capacity) {
    list * l = malloc(sizeof(list));
    l->capacity = initial_capacity;
    l->size = 0;
    l->tokens = malloc(sizeof(token) * l->capacity);

    return l;
}

void ensure_capacity(list *l) {
    if (l->size < l->capacity) return;
    if (l->size > l->capacity) {
        fprintf(stderr, "ERROR: List capacity overflow\n");
        fprintf(stderr, "   size: %d, capacity: %d\n", l->size, l->capacity);
        exit(EXIT_FAILURE);
    }

    l->capacity *= 2;
    l->tokens = realloc(l->tokens, sizeof(token) * l->capacity);
    
    if (l->tokens == NULL) {
        fprintf(stderr, "ERROR: List reallocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void add(list *l, token t) {
    ensure_capacity(l);
    
    l->tokens[l->size] = t;
    l->size++;
}

token *get(list *l, int i) {
    if (i < 0 || i >= l->size) return NULL; // Invalid index
    return &(l->tokens[i]);
}

list *free_list(list *l) {
    free(l);
    return NULL;
}
