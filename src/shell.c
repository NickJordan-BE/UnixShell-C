#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "../include/parser.h"
#include "../include/handler.h"
#include "../include/piping.h"

void sigint_handler() {
    printf("\nshelldon>> ");
    fflush(stdout);
}

// Shell loop for prompting, calling parsing and function handling
void shell_loop() {
    FILE *fp = fopen("shelldon-history.txt", "a+");
    signal(SIGINT, sigint_handler);

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

        if (check_pipes(res.tokens) == 1) {      
            SplitCmds cmds = split_pipes(res.tokens);
            handle_pipes(cmds.count, cmds.cmds);
        } else {
            dispatch_command(res.count, res.tokens);
        }
    }

    fclose(fp);
}