#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../include/external.h"

typedef struct {
    int count;
    char *** cmds;
} SplitCmds;

int check_pipes(char **argv) {
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            return 1;
        }
    }
    return 0;
}

SplitCmds split_pipes(char **argv) {
    SplitCmds split_cmds;
    split_cmds.cmds = malloc(sizeof(char**) * 8); 
    split_cmds.count = 0;

    char **cur_cmd = malloc(sizeof(char*) * 16);  
    int i = 0, j = 0, k = 0;

    while (argv[i] != NULL) {
        if (strcmp(argv[i], "|") == 0) {
            cur_cmd[j] = NULL;
            split_cmds.cmds[k] = cur_cmd;

            cur_cmd = malloc(sizeof(char*) * 16);
            k++;
            j = 0;
        } else {
            cur_cmd[j] = argv[i];
            j++;
        }
        i++;
    }
    cur_cmd[j] = NULL;
    split_cmds.cmds[k] = cur_cmd;
    split_cmds.count = k + 1;

    return split_cmds;
}


void handle_pipes(char ***cmds) {
    int pipefd[2];
    
    if (pipe(pipefd) == -1) {
        perror("Pipe Error");
        return;
    }

    // for (int i = 0; cmds[i] != NULL; i++) {
    //     execute_external_pipe(i, cmds[i], pipefd);
    //     close(pipefd[0]);
    //     close(pipefd[1]);
    // }

    pid_t pid1 = fork();

    if (pid1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        execvp(cmds[0][0], cmds[0]);
        perror("Shelldon Failed: ");
    } 

    pid_t pid2 = fork();

    if (pid2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        execvp(cmds[1][0], cmds[1]);
        perror("Shelldon Failed: ");
    }

    int status1;
    int status2;
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
}
