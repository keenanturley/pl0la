//scanner.h
#include <stdio.h>
#include "list.c"

/**
 * @file scanner.h
 * @author Alexander Desmond (alexdesmond@knights.ucf.edu)
 * @brief Scanner and tokenizer for pl0 input files
 * @date 2020-02-14
 * 
 */

#define MAX_IDENT_LENGTH 11
#define MAX_NUMBER_LENGTH 5

list * tokenize(char * file_path);
token nextToken(FILE * fp);
char fpeek(FILE * fp);
bool skipWhiteSpace(FILE * fp);
bool skipComments(FILE * fp);
void endToken(FILE * fp);