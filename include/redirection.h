#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char **handle_redirection(int argc, char **argv);


#endif