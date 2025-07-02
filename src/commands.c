#include <stdio.h>


void echo_command(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }

    printf("\n");
}