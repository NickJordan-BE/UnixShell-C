/**
 * @file piping.c
 * @brief Handles pipe logic
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../include/external.h"

/**
 * Split commands into pipe structure
 */
typedef struct {
    int count;
    char *** cmds;
} SplitCmds;

/**
 * @brief Checks for pipes in command
 * 
 * @param argv command tokens
 * @return boolean true or false
 */
int check_pipes(char **argv) {
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Splits commands into pipe structure
 * 
 * Splits commands into an array of command lists to be executed
 * 
 * @param argv command tokens
 * @return Struct containing list of commands and number of commands
 */
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

/**
 * @brief Creates pipe director for reading and writing to input and output
 * 
 * @return Array of two pipes for alternating reading and writing
 */
int **create_pipe() {
    int **pipefd = malloc(2 * sizeof(int *));
    pipefd[0] = malloc(2 * sizeof(int));
    pipefd[1] = malloc(2 * sizeof(int));

    if (pipe(pipefd[0]) == -1 || pipe(pipefd[1]) == -1) {
        perror("Pipe Error");
        return NULL;
    }

    return pipefd;
}

/**
 * @brief Closes read and write pipe ends
 * @param pipes array of pipes to be closed
 */
void close_pipes(int **pipes) {
    close(pipes[0][0]);
    close(pipes[1][1]);
    close(pipes[1][0]);
    close(pipes[0][1]);
}

/**
 * @brief Free pipe array and pipe memory
 * @param pipes array of pipes to be closed
 */
void free_pipes(int **pipes) {
    free(pipes[0]);
    free(pipes[1]);
    free(pipes);
}

/**
 * @brief Handles pipe read and write logic
 * 
 * @param pipefd array of pipes
 * @param pos the position of the current commmand
 * @param num_cmds total number of commands in the pipe
 */
void redirect_pipes(int **pipefd, int pos, int num_cmds) {
    if (pos == 0) {
        dup2(pipefd[pos % 2][1], STDOUT_FILENO);
    } else if (pos == num_cmds - 1) {
        dup2(pipefd[(pos + 1) % 2][0], STDIN_FILENO);
    } else {
        dup2(pipefd[(pos + 1) % 2][0], STDIN_FILENO);
        dup2(pipefd[pos % 2][1], STDOUT_FILENO);
    }

    close_pipes(pipefd);
} 

/**
 * @brief Waits for all pids for each fork
 * @param pids array of pids
 * @param num_cmds total number of commands
 */
void waitpid_all(pid_t *pids, int num_cmds) {
    for (int i = 0; i < num_cmds; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }
}

/**
 * @brief Handles main logic for executing pipe commands
 * @param num_cmds number of commands to be executed
 * @param cmds array of command arguments for command calls
 */
void execute_pipes(int num_cmds, char ***cmds) {
    int **pipefd = create_pipe();

    pid_t pids[num_cmds];

    for (int i = 0; i < num_cmds; i++) {
        pid_t pid = fork();
        pids[i] = pid;

        if (pid == 0) {
            redirect_pipes(pipefd, i, num_cmds);
            execvp(cmds[i][0], cmds[i]);
            perror("Shelldon Failed: ");
        }
    }

    close_pipes(pipefd);
    waitpid_all(pids, num_cmds);
    free_pipes(pipefd);
}
