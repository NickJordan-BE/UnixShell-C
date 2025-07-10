#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_external(int argc, char **argv);
void execute_external_pipe(int cmd_num, char **argv, int pipefd[2]);

#endif