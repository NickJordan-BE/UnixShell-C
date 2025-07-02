#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_TOKENS 64
#define DELIM " \t\r\n"

typedef struct {
    int count;
    char **tokens;
} ParseResult;

ParseResult parse_line(char *line);

#endif

