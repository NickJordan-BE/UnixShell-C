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
void handle_pipes(char ***cmds);

#endif