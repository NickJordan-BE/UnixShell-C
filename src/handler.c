#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <../include/commands.h>

typedef void (*CommandFunction)(int argc, char **argv);

typedef struct {
    const char *name;
    CommandFunction function;
} CommandMapping;

CommandMapping commands[] = {
    {"echo", echo_command},
    {NULL, NULL}
};

CommandFunction get_command(const char *name) {
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcasecmp(name, commands[i].name) == 0) {
            return commands[i].function;
        }
    }
    return NULL;
}

void dispatch_command(int full_argc, char **full_argv) {
    if (full_argc == 0) {
        fprintf(stderr, "Nothing Entered\n");
        return;
    }

    const char *cmd_name = full_argv[0];

    CommandFunction cmd_fn = get_command(cmd_name);

    if (!cmd_fn) {
        fprintf(stderr, "Unknown Command: %s\n", cmd_name);
        return;
    }

    return cmd_fn(full_argc - 1, full_argv + 1);
}
