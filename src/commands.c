#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/parser.h"

void echo_command(int argc, char **argv) {
    if (argv[0][0] != '"' || argv[argc - 1][strlen(argv[argc - 1]) - 1] !=  '"') {
        fprintf(stderr, "Unknown\n");
        return;
    }

    memmove(argv[0], argv[0] + 1, strlen(argv[0]));

    if (argc == 1) {
        argv[0][strlen(argv[0]) - 1] = '\0';
    } else {
        argv[argc - 1][strlen(argv[argc - 1]) - 1] = '\0';
    }

    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }

    printf("\n");
}

void cd_command(int argc, char **argv) {
    if (argc != 1) {
        fprintf(stderr, "Incorrect Argument Numbers");
    }
    
    char *path = argv[0];

    if (chdir(path) != 0) {
        fprintf(stderr, "Directory change failed.");
    } else {
        printf("Directory changed successfully.\n");
    }
}

void exit_command(int argc, char **argv) {
    (void)argc;
    (void)argv;
    free_tokens();
    exit(0);
}

void help_command(int argc, char **argv) {
    (void)argc;
    (void)argv;
    printf("Supported Commands:\n1. echo\n2. cd\n3. exit\n4. help\n");
}