/**
 * @file parser.c
 * @brief For parsing input into tokens
 *
 * Implements tokenization logic
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_TOKENS 64
#define DELIM " \t\r\n"


/**
 * @brief Result from parsing
 * 
 * Used to store the count of the tokens and the token list
 */
typedef struct {
    int count;
    char **tokens;
} ParseResult;


ParseResult result;

/**
 * @brief Parses line into a list of tokens
 * 
 * @param line the line to be parsed
 * @return ParseResult struct with list of tokens and number of tokens
 */
ParseResult parse_line(char *line) {

    int bufsize = MAX_TOKENS, position = 0;
    result.tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!result.tokens) {
        fprintf(stderr, "allocation failed\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIM);
    while (token != NULL) {
        result.tokens[position++] = token;

        if (position >= bufsize) {
            bufsize += MAX_TOKENS;
            result.tokens = realloc(result.tokens, bufsize * sizeof(char*));
            if (!result.tokens) {
                fprintf(stderr, "reallocation failed\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIM);
    }
    result.tokens[position] = NULL;
    result.count = position;
    return result;
}

/**
 * @brief Frees token memory allocation
 */
void free_tokens() {
    free(result.tokens);
    result.tokens = NULL;
}