#ifndef LIST_H
#define LIST_H

/**
 * @file list.h
 * @author Keenan Turley (keenan.turley@knights.ucf.edu)
 * @brief Simple ArrayList implementation for lexical analyzer tokens
 * @date 2020-02-14
 *
 */

#include "token.h"

typedef struct list {
    token *tokens; // Dynamic array of tokens
    int size;
    int capacity;
} list;

/**
 * @brief Create a list
 *
 * Dyanmically allocates and returns a list with the default initial capicity,
 * defined above.
 * The caller should call free_list() when finished with the list.
 *
 * @return list* The created list
 */
list *create_list();

/**
 * @brief Ensure there's enough space for another token
 *
 * Checks the given list's size against its capacity.
 *
 * If the size is less than the capacity, nothing is done.
 * If the size is greater than the capacity, an error is logged to stderr and
 * the program is exited with EXIT_FAILURE.
 * If the size is equal to the capacity, the list is reallocated with twice
 * capacity as before. (capacity *= 2)
 *
 * If the reallocation fails, an error will be logged to stderr and the
 * program will exit with EXIT_FAILURE.
 *
 * @param l The list whose capacity to ensure
 */
void ensure_capacity(list *l);

/**
 * @brief Add a token to the end of the list
 *
 * @param l The list to add to
 * @param t The token to add
 */
void add(list *l, token t);

/**
 * @brief Returns the token at index i in the list
 *
 * @param l The list to look in
 * @param i The index of the desired token
 * @return token* A pointer to the desired token
 */
token *get(list *l, int i);

/**
 * @brief Frees the list and its components
 *
 * @param l The list to free
 * @return list* Always NULL
 */
list *free_list(list *l);

#endif /* LIST_H */
