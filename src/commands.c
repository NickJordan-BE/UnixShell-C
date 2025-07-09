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
    printf("Exiting shelldon...\n");
    exit(0);
}

void help_command(int argc, char **argv) {
    (void)argc;
    (void)argv;
    printf("Supported Commands:\n1. echo\n2. cd\n3. exit\n4. help\n");
}

void history_command(int argc, char **argv) {
    if (argc != 0) {
        char *cmd = argv[0];

        if (strcasecmp(cmd, "-1") == 0) {
            FILE *fp = fopen("shelldon-history.txt", "w");
            printf("Clearing history...\n");

            if (fp == NULL) {
                fprintf(stderr, "Error opening history file.\n");
                return;
            }
            fclose(fp);
        }
    } else {
        FILE *fp = fopen("shelldon-history.txt", "r");

        if (fp == NULL) {
            fprintf(stderr, "Error opening history file.\n");
            return;
        }

        char line[1024];
        int count = 1;

        while (fgets(line, sizeof(line), fp)) {
            printf("%i. %s\n", count, line);
            count++;
        }
        fclose(fp);
    }
}

void sizeof_command(int argc, char **argv) {
    (void)argv;
    printf("%i\n", argc);
}

void clear_command(int argc, char **argv) {
    (void)argc;
    (void)argv;
    printf("\033[H\033[J");
    fflush(stdout);
}

void pwd_command(int argc, char **argv) {
    (void)argc;
    (void)argv;
    char buffer[1024];
    
    if (getcwd(buffer, sizeof(buffer)) == NULL) {
        fprintf(stderr, "Unable to get current directory.\n");
    } else {
        printf("%s\n", buffer);
    }
}