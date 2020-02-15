#include "token.h"
#include "scanner.h"

list * tokenize(char * file_path){
    FILE * fp = fopen(file_path, "r");
    list * tokenList = create_list();
    token = null;

    skipWhiteSpace(FILE * fp);
    while (fpeek(fp) != EOF){
        token = nextToken(file_path);
        if (1 == 1){ // TODO: Check that there was no error in reading token
            add(tokenList, token);
        }
        skipWhiteSpace(FILE * fp);
    }

    fclose(fp);
    return tokenList;
}

token nextToken(FILE * fp)
{
    char tokenName[12];
    token nextToken;

    char next = fpeek(fp);
    if (isalpha(next)) //read an identifier or reserved word
    {
        int i = 0;
        do{
            if (i == 12)
            {
                //identifier too long, TODO: throw error
                tokenName[12] = '\0';
                nextToken.token_type = nulsym;
                nextToken.name = (char*)malloc(12 * sizeof(char));
                strcpy(nextToken.name, tokenName);

                return nextToken;
            }
            tokenName[i++] = fgetc(fp);

            next = fpeek(fp);
        } while (isalpha(next) || isdigit(next));
        // TODO: check if reserved word

        tokenName[i] = '\0';
        nextToken.token_type = identsym;
        nextToken.name = (char*)malloc(i * sizeof(char));
        strcpy(nextToken.name, tokenName);
        return nextToken;
    }
    else if (isdigit(next)) //read a number
    {
        
    }
    else switch (next){
        case  '+':

            break;
        case  '-':

            break;
        case  '*':

            break;
        case  '/': // /, /*

            break;
        case  '(':

            break;
        case  ')':

            break;
        case  '=':

            break;
        case  ',':

            break;
        case  '.':

            break;
        case  '<': // <> , <= , <
            
            break;
        case  '>': // > , >=

            break;
        case  ';':

            break;
        case  ':': // := , :

            break;
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
