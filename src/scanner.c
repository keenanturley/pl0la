#include <token.h>
#include "scanner.h"

list tokenize(char * file_path){
    FILE * fp = fopen(file_path, "r");
    list * tokenList;

    token = null;

    while (fpeek(fp) != EOF){
        token = nextToken(file_path);
        add(&tokenList, token;
    }

    return tokens
}

token nextToken(char * file_path)
{
    
}

char fpeek(FILE * fp)
{
    char c = fgetc(fp);
    ungetc(c, fp);
    return c;
}