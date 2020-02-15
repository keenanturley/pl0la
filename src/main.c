#include <stdlib.h>
#include <stdio.h>
#include "util.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: ./pm0la (file-path)\n");
        exit(EXIT_FAILURE);
    }

    char *file_path = argv[1];

    // Print out source program
    printf("Source Program:\n");
    print_file(file_path);

}
