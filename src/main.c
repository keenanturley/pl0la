#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "list.h"
#include "scanner.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: ./pm0la (file-path)\n");
        exit(EXIT_FAILURE);
    }

    char *file_path = argv[1];

    // Print out source program
    printf("Source Program:\n");
    print_file(file_path);
    printf("\n");

    // Tokenize the file
    list * token_list = tokenize(file_path);

    // Print out lexeme table
    printf("Lexeme Table:\n");
    print_lexeme_table(token_list);
    printf("\n");

    // Print out lexeme list
    printf("Lexeme List:\n");
    print_lexeme_list(token_list);
}
