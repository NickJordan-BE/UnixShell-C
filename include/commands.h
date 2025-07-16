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
void history_command(int argc, char **argv);
void pwd_command(int argc, char **argv);
void clear_command(int argc, char **argv);
void sizeof_command(int argc, char **argv);
void grep_command(int argc, char **argv);
void jobs_command(int argc, char **argv);

#endif