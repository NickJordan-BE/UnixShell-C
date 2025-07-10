#ifndef HANDLER_H
#define HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <../include/commands.h>

typedef void (*CommandFunction) (int argc, char **argv);

typedef struct {
    const char *name;
    CommandFunction function;
} CommandMapping;

CommandFunction get_command(const char *name);

void dispatch_command(int full_argc, char **full_argv);

#endif