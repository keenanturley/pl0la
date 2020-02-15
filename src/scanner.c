#include <token.h>
#include "scanner.h"

list tokenize(char * file_path){
    FILE * fp = fopen(file_path, "r");
    list * tokens;



    return tokens
}

int fpeek(FILE * fp)
{
    int c = fgetc(fp);
    ungetc(c, fp);
    return c;
}