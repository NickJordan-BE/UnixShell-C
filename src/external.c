#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/redirection.h"

void execute_external(int argc, char **argv) {
    pid_t pid = fork();

    handle_redirection(argc, argv);

    if (pid == 0) {
        execvp(argv[0], argv);
        fprintf(stderr, "Unknown Command");
    } else if (pid > 0 ) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        fprintf(stderr, "Fork Failed");
    }
}
