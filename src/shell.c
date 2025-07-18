/**
 * @file shell.c
 * @brief Main shell loop
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "../include/parser.h"
#include "../include/handler.h"

/**
 * @brief Ends current process and reprompts shell at SIGINT
 */
void sigint_handler() {
    printf("\nshelldon>> ");
    fflush(stdout);
}

/**
 * @brief Shell loop for prompting, calling parsing, history tracking and function handling.
 */ 
void shell_loop() {
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    FILE *fp = fopen("shelldon-history.txt", "a+");

    if (fp == NULL) {
        fprintf(stderr, "Error opening history file.");
        exit(EXIT_FAILURE);
    }
    
    char buffer[1024];

    while (1) {  
        printf("shelldon>> ");
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        if (strlen(buffer) > 0) {
            fprintf(fp, "%s", buffer);
            fflush(fp);
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        ParseResult res = parse_line(buffer);
        
        dispatch_command(res.count, res.tokens);
    }

    fclose(fp);
}