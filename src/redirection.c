#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char **handle_redirection(int argc, char **argv) {
    int fd = 0;
    int found = 0;
    if (argc >= 3 && strcmp(argv[argc - 2], "<") == 0) {
        fd = open(argv[argc - 1], O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "open failed");
            return argv;
        }
        found = 1;
        dup2(fd, STDIN_FILENO);
    } else if (argc >= 3 && strcmp(argv[argc - 2], ">") == 0 ) {
        fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            fprintf(stderr, "open(w) failed");
            return argv;
        }
        found = 1;
        dup2(fd, STDOUT_FILENO);
    } else if (argc >= 3 && strcmp(argv[argc - 2], ">>") == 0) {
        fd = open(argv[argc - 1], O_APPEND | O_CREAT, 0644);
        if (fd == -1) {
            fprintf(stderr, "open(a) failed");
            return argv;
        }
        found = 1;
        dup2(fd, STDOUT_FILENO);
    }
    close(fd);

    if (found) {
        argv[argc - 2] = "\0"; 
    }

    return argv;
}
