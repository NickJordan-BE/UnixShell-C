#ifndef PIPING_H
#define PIPING_H

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

int check_pipes(char **argv);
SplitCmds split_pipes(char **argv);
void execute_pipes(int cmd_count, char ***cmds);
int **create_pipe();
void close_pipes(int **pipes);
void free_pipes(int **pipes);

#endif