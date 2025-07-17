#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "../include/redirection.h"
#include "../include/jobs.h"

/**
 * @brief Waits for foreground job
 * 
 * @param pid the pid of the job
 * @param job the current job being executed
 */
void wait_for_process(pid_t pid, job_t *job) {
    int status;
    if (waitpid(pid, &status, WUNTRACED) > 0) {
        if (WIFSIGNALED(status)) {
            remove_job(job);
            printf("Interrupted");
        } else if (WIFSTOPPED(status)) {
            job->status = STOPPED;
            printf("Stopped");
        } else if (WIFEXITED(status)) {
            remove_job(job);
        } else {
            remove_job(job);
            printf("Didnt Exit good");
        }
    } else {
        printf("Error with waitpid");
    }
}

/**
 * @brief executes external commands
 * 
 * @param argc token count
 * @param argv token list
 */
void execute_external(int argc, char **argv) {
    int background = check_for_background(argv);

    if (background) {
        argv[argc - 1] = NULL;
        argc--;
    }

    pid_t pid = fork();
    
    if (pid == 0) {
        argv = handle_redirection(argc, argv); 
        setpgid(getpid(), 0);

        if (execvp(argv[0], argv) < 0) {
            printf("Command not found: %s\n", argv[0]);
        }
        
        perror("Shelldon Failed: ");
        exit(EXIT_FAILURE);
    } 

    job_t *cur_job = create_job(pid, background, serialize_command(argv, argc));

    if (!background) {
        wait_for_process(pid, cur_job);
    } else {
        printf("[%d], %d\n", cur_job->job_id, pid);
    }

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    return;
}

