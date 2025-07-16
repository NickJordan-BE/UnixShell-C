#ifndef JOBS_H
#define JOBS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    RUNNING,
    STOPPED,
    DONE
} job_status_t;

typedef struct Job {
    int job_id;
    int is_background;
    job_status_t status;
    char **command;
    pid_t pgid;
    struct Job *next;
} job_t;

int check_for_background(char **argv);
int add_to_jobs(job_t *job);
void print_jobs();

#endif