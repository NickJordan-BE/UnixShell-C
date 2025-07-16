/**
 * @file external.c
 * @brief Handles external commands.
 *
 * Logic for executing external commands not built-in to the shell.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/redirection.h"
#include "../include/jobs.h"


/**
 * @brief Forks and Executes external command
 * 
 * @param argc token count
 * @param argv tokens for command (including command name)
 */
void execute_external(int argc, char **argv) {
    pid_t pid = fork();

    int background = check_for_background(argv);

    if (background) {
        argv = argv - 1;
    }
   
    if (pid == 0) {
        argv = handle_redirection(argc, argv);
        execvp(argv[0], argv);
        perror("Shelldon Failed: ");
    }

    if (background) {
        //track_job();
        printf("Job#: 1 Pid#: %i\n", pid);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }

}