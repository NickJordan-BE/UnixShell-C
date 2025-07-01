#include <stdio.h>
#include <string.h>
#include "../include/parser.h"

// Shell loop for prompting, calling parsing and function handling
void shell_loop(void) {
    char buffer[1024];

    while (1) {
        
        printf("shelldon>> ");
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        char **token = parse_line(buffer);

    }
}