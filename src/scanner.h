#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#include "list.h"

/**
 * @file scanner.h
 * @author Alexander Desmond (alexdesmond@knights.ucf.edu)
 * @brief Scanner and tokenizer for pl0 input files
 * @date 2020-02-14
 */

#define MAX_IDENT_LENGTH 11
#define MAX_NUMBER_LENGTH 5

/**
 * @brief Tokenize input file
 * @return list* of all tokens
 */
list * tokenize(char * file_path);

/**
 * @brief Gets next token from input file and determines its type
 * @return token next token in input file
 */
token nextToken(FILE * fp);

/**
 * @brief Gets next char in input buffer, puts it back
 * @return char next char in input buffer
 */
char fpeek(FILE * fp);

/**
 * @brief Skips whitespace
 * If next char in input buffer is whitespace, skips that and all contiguous white space
 * @return bool whether any whitespace was skipped
 */
bool skipWhiteSpace(FILE * fp);

/**
 * @brief Skips comments
 * If next thing in input buffer is the opening of a comment, moves the input buffer past that entire comment
 * @return bool whether a comment was skipped
 */
bool skipComments(FILE * fp);

/**
 * @brief Skips the rest of a string of letters and/or digits
 * Moves the buffer to the end of the current string of letters and digits
 * @return void
 */
void endToken(FILE * fp);

#endif /* SCANNER_H */
