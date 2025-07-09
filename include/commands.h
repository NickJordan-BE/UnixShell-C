#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/parser.h"

void echo_command(int argc, char **argv);
void cd_command(int argc, char **argv);
void exit_command(int argc, char **argv);
void help_command(int argc, char **argv);

#endif