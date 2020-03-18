/**
 * @file main.c
 * @author Keenan Turley (keenan.turley@knights.ucf.edu)
 * @author Alexander Desmond (alexdesmond@knights.ucf.edu)
 * @brief The PL/0 Lexical Analyzer
 * @date 2020-02-15
 *
 */

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
    printf("\n");

    printf("Lexeme List (Symbolic Representation):\n");
    print_lexeme_list_symbolic(token_list);

    // Free the token list
    free_list(token_list);

    return EXIT_SUCCESS;
}
