#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "list.h"
#include "token.h"

void print_file(char *file_path) {
    // Try to open the file
    FILE *fp = fopen(file_path, "r");

    // Handle failure
    if (fp == NULL) {
        fprintf(stderr, "ERROR: Failed to open file: %s", file_path);
        exit(EXIT_FAILURE);
    }

    char * line = NULL;
    size_t n = 0;
    int line_num = 0;

    while (getline(&line, &n, fp) != -1) {
        printf("%s", line);
    }

    // Free the line from getline
    free(line);

    // Release lock by closing file
    fclose(fp);
}

void print_lexeme_table(list *l) {
    // Headers
    printf("%-11s    %s\n", "lexeme", "token type");
    for (int i = 0; i < l->size; i++) {
        token *t = get(l, i);
        printf("%-11s    %d\n", t->name, t->type);
    }
}

void print_lexeme_list(list *l) {
    for (int i = 0; i < l->size; i++) {
        token *t = get(l, i);
        printf("%d ", t->type);
        if (t->type == identsym) {
            printf("%s ", t->name);
        }
        if (t->type == numbersym) {
            printf("%s ", t->name);
        }
    }
    printf("\n");
}

void print_lexeme_list_symbolic(list *l) {
    for (int i = 0; i < l->size; i++) {
        token *t = get(l, i);
        printf("%s ", token_to_string(t->type));
        if (t->type == identsym) {
            printf("%s ", t->name);
        }
        if (t->type == numbersym) {
            printf("%s ", t->name);
        }
    }
    printf("\n");
}
