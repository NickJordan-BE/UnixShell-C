#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void handle_redirection(int argc, char **argv) {
    int fd = 0;
    if (argc >= 3 && strcmp(argv[argc - 2], "<") == 0) {
        fd = open(argv[argc - 1], O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "open failed");
            return;
        }
        dup2(fd, STDIN_FILENO);
    } else if (argc >= 3 && strcmp(argv[argc - 2], ">") == 0 ) {
        fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            fprintf(stderr, "open(w) failed");
            return;
        }
        dup2(fd, STDOUT_FILENO);
    } else if (argc >= 3 && strcmp(argv[argc - 2], ">>") == 0) {
        fd = open(argv[argc - 1], O_APPEND | O_CREAT, 0644);
        if (fd == -1) {
            fprintf(stderr, "open(a) failed");
            return;
        }
        dup2(fd, STDOUT_FILENO);
    }
    close(fd);
}
