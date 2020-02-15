#include <token.h>
#include "scanner.h"

list tokenize(char * file_path){
    FILE * fp = fopen(file_path, "r");
    list * tokenList;
    token = null;

    skipWhiteSpace(FILE * fp);
    while (fpeek(fp) != EOF){
        token = nextToken(file_path);
        if (1 == 1){ // TODO: Check that there was no error in reading token
            add(&tokenList, token);
        }
        skipWhiteSpace(FILE * fp);
    }

    fclose(fp);
    return tokenList;
}

token nextToken(FILE * fp)
{
    
    if (isalpha(fpeek(fp)))
    {
        //read an identifier or reserved word
    }
    else if (isdigit(fpeek(fp)))
    {
        //read a number
    }

}

char fpeek(FILE * fp)
{
    char c = fgetc(fp);
    ungetc(c, fp);
    return c;
}
void skipWhiteSpace(FILE * fp){
    char c;
    do{
        c = fgetc(fp);
    } (while isspace(c) != 0); 
    ungetc(c, fp);
}