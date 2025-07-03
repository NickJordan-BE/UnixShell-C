#include <stdio.h>
#include <string.h>

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