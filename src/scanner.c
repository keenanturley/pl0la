#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "scanner.h"
#include "list.h"

list * tokenize(char * file_path){
    FILE * fp = fopen(file_path, "r");
    list * tokenList = create_list();

    while (skipWhiteSpace(fp) || skipComments(fp)); // Skips white space and comments

    while (fpeek(fp) != EOF){ // Continue to add tokens til end of file
        add(tokenList, nextToken(fp)); 
        while (skipWhiteSpace(fp) || skipComments(fp)); // Skips white space and comments
    } 

    fclose(fp);
    return tokenList;
}

token nextToken(FILE * fp){
    char tokenName[(MAX_IDENT_LENGTH + 1)];
    token nextToken;
    int i;

    char next = fpeek(fp);
    if (isalpha(next)) { // Read an identifier or reserved word
        i = 0;
        do{
            if (i >= MAX_IDENT_LENGTH) { // Identifier too long
                tokenName[MAX_IDENT_LENGTH] = '\0';
                fprintf(stderr, "Error: Identifier starting with \"%s\" too long. Max length 11 characters\n", tokenName);
                exit(EXIT_FAILURE);
            }
            tokenName[i++] = fgetc(fp);

            next = fpeek(fp);
        } while (isalpha(next) || isdigit(next));

        tokenName[i] = '\0';
        nextToken.type = evaluate_token_type(tokenName);
        nextToken.name = strdup(tokenName);
        return nextToken;
    }

    else if (isdigit(next)) { // Read a number
        i = 0;
        do{
            if (i >= MAX_NUMBER_LENGTH){ // Number too long
                do{
                    if (i >= MAX_IDENT_LENGTH){ // Number too long and Not an identifier
                        tokenName[MAX_IDENT_LENGTH] = '\0';
                        fprintf(stderr, "Error: Number starting with \"%s\" too long. Max length 5 digits\n", tokenName);
                        exit(EXIT_FAILURE);
                    }
                    tokenName[i++] = fgetc(fp);

                    next = fpeek(fp);
                } while(isdigit(next));
                if (isalpha(next)){ // Variable does not start with letter.
                    do{
                        if (i >= MAX_IDENT_LENGTH){ // Variable does not start with letter AND identifier too long
                            tokenName[MAX_IDENT_LENGTH] = '\0';
                            fprintf(stderr, "Error: Identifier starting with \"%s\" does not begin with a letter\n", tokenName);
                            fprintf(stderr, "Error: Identifier starting with \"%s\" too long. Max length 11 characters\n", tokenName);
                            exit(EXIT_FAILURE);
                        }
                        tokenName[i++] = fgetc(fp);

                        next = fpeek(fp);
                    } while (isalpha(next) || isdigit(next));
                    fprintf(stderr, "Error: Identifier \"%s\" does not begin with a letter\n", tokenName);
                    exit(EXIT_FAILURE);
                }
                // Number just too long, next token not a letter
                tokenName[i] = '\0';
                fprintf(stderr, "Error: Number starting with \"%s\" too long. Max length 5 digits\n", tokenName);
                exit(EXIT_FAILURE);
            }
            tokenName[i++] = fgetc(fp);

            next = fpeek(fp);
        } while (isdigit(next));
        if (isalpha(next)){ // Variable does not start with letter.
            do{
                if (i >= MAX_IDENT_LENGTH){ // Variable does not start with letter AND identifier too long
                    tokenName[MAX_IDENT_LENGTH] = '\0';
                    fprintf(stderr, "Error: Identifier starting with \"%s\" does not begin with a letter\n", tokenName);
                    fprintf(stderr, "Error: Identifier starting with \"%s\" too long. Max length 11 characters\n", tokenName);
                    exit(EXIT_FAILURE);
                }
                tokenName[i++] = fgetc(fp);

                next = fpeek(fp);
            } while (isalpha(next) || isdigit(next));
            tokenName[i] = '\0';
            fprintf(stderr, "Error: Identifier \"%s\" does not begin with a letter\n", tokenName);
            exit(EXIT_FAILURE);
        }
        // Number appropriately sized. This is an actual number token
        tokenName[i] = '\0';
        nextToken.type = numbersym;
        nextToken.name = strdup(tokenName);
        return nextToken;
    }

    else switch (next){ // Read special characters
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
                nextToken.name = strdup(tokenName);
                nextToken.type = neqsym;
                return nextToken;
            }
            else if (tokenName[1] == '='){ // <=
                tokenName[2] = '\0';
                nextToken.name = strdup(tokenName);
                nextToken.type = leqsym;
                return nextToken;
            }
            else{ // <
                ungetc(tokenName[1], fp);
                tokenName[1] = '\0';
                nextToken.name = strdup(tokenName);
                nextToken.type = lessym;
                return nextToken;
            }
        case  '>': // > , >=
            tokenName[0] = fgetc(fp);
            tokenName[1] = fgetc(fp);
            if (tokenName[1] == '='){ // >=
                tokenName[2] = '\0';
                nextToken.name = strdup(tokenName);
                nextToken.type = geqsym;
                return nextToken;
            }
            else{ // >
                ungetc(tokenName[1], fp);
                tokenName[1] = '\0';
                nextToken.name = strdup(tokenName);
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
                nextToken.name = strdup(tokenName);
                nextToken.type = becomessym;
                return nextToken;
            }
            else{ // colon by itself is invalid
                tokenName[1] = '\0';
                fprintf(stderr, "Error: \"%s\" is an invalid symbol\n", tokenName);
                exit(EXIT_FAILURE);
            }
        default: // Invalid symbol
            tokenName[0] = fgetc(fp);
            tokenName[1] = '\0';
            fprintf(stderr, "Error: \"%s\" is an invalid symbol\n", tokenName);
            exit(EXIT_FAILURE);
    }
}

char fpeek(FILE * fp){
    char c = fgetc(fp);
    ungetc(c, fp);
    return c;
}

bool skipWhiteSpace(FILE * fp){ // returns true if any white space is skipped, otherwise false
    char c;
    int i = 0;
    do{
        c = fgetc(fp);
        i++;
    } while (isspace(c));
    ungetc(c, fp);
    return (i > 1) ? true : false;
}

bool skipComments(FILE * fp){ // returns true if any comments are skipped, otherwise false
    char c = fpeek(fp);
    if (c == '/'){
        c = fgetc(fp);
        if (fpeek(fp) == '*'){ // comment found
            c = fgetc(fp);
            do{
                c = fgetc(fp);
                if (c == '*' && fpeek(fp) == '/'){ //end of comment found
                    c = fgetc(fp); // after this line, next thing on the buffer is the next char after the comment
                    return true;
                }
            } while (c != EOF);
            fprintf(stderr, "Error: Comment never closed\n");
        }
        else{
            ungetc(c, fp);
        }
    }
    return false;
}

void endToken(FILE * fp){ // skips the rest of the string of letters and digits
    char next;
    do{
        next = fgetc(fp);
    } while (isalpha(next) || isdigit(next));
    ungetc(next, fp);
    return;
}
