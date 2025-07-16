/**
 * @file handler.c
 * @brief Handles function calling for shell loop.
 *
 * Logic for dispatching built-in and external commands.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <../include/commands.h>
#include <../include/external.h>
#include <../include/piping.h>

// Pointer to a function with parameters argc and **argv
typedef void (*CommandFunction)(int argc, char **argv);

/**
 * @brief Stores the command name and the corresponding function
 */
typedef struct {
    const char *name;
    CommandFunction function;
} CommandMapping;

// Implemented commands
CommandMapping commands[] = {
    {"echo", echo_command},
    {"cd", cd_command},
    {"exit", exit_command},
    {"help", help_command},
    {"history", history_command},
    {"pwd", pwd_command},
    {"sizeof", sizeof_command},
    {"clear", clear_command},
    {"grep", grep_command},
    {"jobs", jobs_command},
    {NULL, NULL}
};

/**
 * @brief Finds the corresponding command via name 
 * 
 * Finds if the command name is implemented and returns the corresponding 
 * function, otherwise returns NULL.
 * 
 * @param name the name of the function
 * @return The corresponding function or NULL
 */
CommandFunction get_command(const char *name) {
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcasecmp(name, commands[i].name) == 0) {
            return commands[i].function;
        }
    }
    return NULL;
}

/**
 * @brief Handles command execution structure
 *  
 * Dispatches parsed tokens to corresponding function to be executed.
 * If the function does not exist, it tries to fork and run an external command.
 * 
 * @param full_argc num of tokens
 * @param full_argv list of tokens
 */
void dispatch_command(int full_argc, char **full_argv) {
    if (full_argc == 0) {
        fprintf(stderr, "Nothing Entered\n");
        return;
    }

    if (check_pipes(full_argv) == 1) {
        SplitCmds cmds = split_pipes(full_argv);
        execute_pipes(cmds.count, cmds.cmds);
        return;
    }

    const char *cmd_name = full_argv[0];

    CommandFunction cmd_fn = get_command(cmd_name);
   

    if (cmd_fn) {
        cmd_fn(full_argc - 1, full_argv + 1);
    } else {
        execute_external(full_argc, full_argv);
    }
}


