#include <stdio.h>
#include <stdlib.h>

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


    // Release lock by closing file
    fclose(fp);
}
