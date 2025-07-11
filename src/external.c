#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/redirection.h"

void execute_external(int argc, char **argv) {
    pid_t pid = fork();

    if (pid == 0) {
        argv = handle_redirection(argc, argv);
        execvp(argv[0], argv);
        perror("Shelldon Failed: ");
    } else if (pid > 0 ) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("Fork Failed: ");
    }
}