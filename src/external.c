#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/redirection.h"
#include "../include/jobs.h"
#include "../include/main.h"

void execute_external(int argc, char **argv) {
    int background = check_for_background(argv);

    if (background) {
        argv[argc - 1] = NULL;
        argc--;
    }

    pid_t pid = fork();
    job_t *cur_job = malloc(sizeof(job_t));

    
    if (pid == 0) {
        argv = handle_redirection(argc, argv); 
        execvp(argv[0], argv);
        perror("Shelldon Failed: ");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {

        cur_job->pgid = pid;
        cur_job->status = RUNNING;
        cur_job->command = argv;
        cur_job->is_background = background;
        add_to_jobs(cur_job);

        if (!background) {
            int status;
            waitpid(pid, &status, 0);
            cur_job->status = DONE;
        } else {
            printf("[%d], %d\n", cur_job->job_id, pid);
        }
    }
}