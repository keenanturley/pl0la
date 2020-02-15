#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "scanner.h"

list * tokenize(char * file_path){
    FILE * fp = fopen(file_path, "r");
    list * tokenList = create_list();
    token newToken;

    while (fpeek(fp) != EOF && (skipWhiteSpace(fp) || skipComments(fp))); // Skips white space and comments
    
    while (fpeek(fp) != EOF){
        newToken = nextToken(fp);
        
        add(tokenList, newToken); // Note: does not yet verify that token was read without error
        
        while (fpeek(fp) != EOF && (skipWhiteSpace(fp) || skipComments(fp))); // Skips white space and comments
    }

    fclose(fp);
    return tokenList;
}

/* TODO: figure out what to do with rest of token name
   (for identifiers and numbers) after current token name has become too long */
token nextToken(FILE * fp)
{
    char tokenName[12];
    token nextToken;
    int i;

    char next = fpeek(fp);
    if (isalpha(next)) {//read an identifier or reserved word
        i = 0;
        do{
            if (i == 12) { //identifier too long
                // TODO: throw error
                tokenName[12] = '\0';
                nextToken.type = nulsym;
                nextToken.name = (char*)malloc(12 * sizeof(char));
                strcpy(nextToken.name, tokenName);

                return nextToken;
            }
            tokenName[i++] = fgetc(fp);

            next = fpeek(fp);
        } while (isalpha(next) || isdigit(next));
        // TODO: check if reserved word
        
        tokenName[i] = '\0';
        nextToken.type = evaluate_token_type(tokenName);
        nextToken.name = (char*)malloc(i * sizeof(char));
        strcpy(nextToken.name, tokenName);
        return nextToken;
    }
    else if (isdigit(next)) {//read a number
        i = 0;
        do{
            if (i == 6){ // number too long
                // TODO: throw error
                tokenName[i] = '\0';
                nextToken.type = nulsym;
                nextToken.name = (char*)malloc(i * sizeof(char));
                strcpy(nextToken.name, tokenName);
                return nextToken;
            }
            tokenName[i++] = fgetc(fp);
            
            next = fpeek(fp);
        } while (isdigit(next));
        if (isalpha(next)){ // Variable does not start with letter. TODO: throw error
            // Perhaps continue to read while the string is still only digits and letters?
        }

        tokenName[i] = '\0';
        nextToken.type = evaluate_token_type(tokenName);
        nextToken.name = (char*)malloc(i * sizeof(char));
        strcpy(nextToken.name, tokenName);
        return nextToken;
    }
    else switch (next){
        case  '+':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = plussym;
            return nextToken;
        case  '-':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = minussym;
            return nextToken;
        case  '*':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = multsym;
            return nextToken;
        case  '/': 
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = slashsym;
            return nextToken;
        case  '(':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = lparentsym;
            return nextToken;
        case  ')':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = rparentsym;
            return nextToken;
        case  '=':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = eqsym;
            return nextToken;
        case  ',':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = commasym;
            return nextToken;
        case  '.':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = periodsym;
            return nextToken;
        case  '<': // <> , <= , <
            tokenName[0] = fgetc(fp);
            tokenName[1] = fgetc(fp);
            if (tokenName[1] == '>'){ // <>
                tokenName[2] = '\0';
                nextToken.name = (char*)malloc(3 * sizeof(char));
                strcpy(nextToken.name, tokenName);
                nextToken.type = neqsym;
                return nextToken;
            }
            else if (tokenName[1] == '='){ // <=
                tokenName[2] = '\0';
                nextToken.name = (char*)malloc(3 * sizeof(char));
                strcpy(nextToken.name, tokenName);
                nextToken.type = leqsym;
                return nextToken;
            }
            else{ // <
                ungetc(tokenName[1], fp);
                tokenName[1] = '\0';
                nextToken.name = (char*)malloc(2 * sizeof(char));
                strcpy(nextToken.name, tokenName);
                nextToken.type = lessym;
                return nextToken;
            }
        case  '>': // > , >=
            tokenName[0] = fgetc(fp);
            tokenName[1] = fgetc(fp);
            if (tokenName[1] == '='){ // >=
                tokenName[2] = '\0';
                nextToken.name = (char*)malloc(3 * sizeof(char));
                strcpy(nextToken.name, tokenName);
                nextToken.type = geqsym;
                return nextToken;
            }
            else{ // >
                ungetc(tokenName[1], fp);
                tokenName[1] = '\0';
                nextToken.name = (char*)malloc(2 * sizeof(char));
                strcpy(nextToken.name, tokenName);
                nextToken.type = gtrsym;
                return nextToken;
            }
        case  ';':
            nextToken.name = (char*)malloc(2 * sizeof(char));
            nextToken.name[0] = fgetc(fp);
            nextToken.name[1] = '\0';
            nextToken.type = semicolonsym;
            return nextToken;
        case  ':': // := , :
            tokenName[0] = fgetc(fp);
            tokenName[1] = fgetc(fp);
            if (tokenName[1] == '='){ // :=
                tokenName[2] = '\0';
                nextToken.name = (char*)malloc(3 * sizeof(char));
                strcpy(nextToken.name, tokenName);
                nextToken.type = becomessym;
                return nextToken;
            }
            else{ // colon by itself is invalid. TODO: throw error
                ungetc(tokenName[1], fp);
                tokenName[1] = '\0';
                nextToken.name = (char*)malloc(2 * sizeof(char));
                strcpy(nextToken.name, tokenName);
                nextToken.type = nulsym;
                return nextToken;
            }
        default: // Invalid symbol. TODO: throw error

            break;
    }

}

char fpeek(FILE * fp)
{
    char c = fgetc(fp);
    ungetc(c, fp);
    return c;
}

bool skipWhiteSpace(FILE * fp){
    char c;
    int i = 0;
    do{
        c = fgetc(fp);
        i++;
    } while (isspace(c)); 
    ungetc(c, fp);
    return (i > 1) ? true : false;
}

bool skipComments(FILE * fp){ // returns true if any comments were skipped, otherwise false
    char c = fpeek(fp);
    if (c == '/'){
        c = fgetc(fp);
        if (fpeek(fp) == '*'){ // comment found
            c = fgetc(fp);
            do{
                c = fgetc(fp);
                if (c == '*' && fpeek(fp) == '/'){ //end of comment found
                    c = fgetc(fp); // next thing on the buffer is the next char after the comment
                    return true;
                }
            } while (c != EOF);
        }
        else{
            ungetc(c, fp);
            return false;
        }
    }
}