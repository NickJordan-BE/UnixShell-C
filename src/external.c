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

void execute_external_pipe(int cmd_num, char **argv, int pipefd[2]) {
    (void)pipefd;
    (void)cmd_num;
    for (int i = 0; argv[i] != NULL; i++) {
        printf("%s", argv[i]);
    }
    // pid_t pid = fork();

    // if (pid == 0) {
    //     if (cmd_num == 0) {
    //         dup2(pipefd[1], STDOUT_FILENO);
    //         close(pipefd[0]);
    //     } else {
    //         dup2(pipefd[0], STDIN_FILENO);
    //         close(pipefd[1]);
    //     }
    //     execvp(argv[0], argv);
    //     perror("Shelldon Failed: ");
    // } else if (pid > 0 ) {
    //     int status;
    //     close(pipefd[0]);
    //     close(pipefd[1]);
    //     waitpid(pid, &status, 0);
    // } else {
    //     perror("Fork Failed: ");
    // }
}