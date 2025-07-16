/**
 * @file jobs.c
 * @brief Handles jobs/background and foreground execution
 *
 * Logic for tracking jobs, background and foreground
 */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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

const char* job_status_names[] = {
    "Running",
    "Stopped",
    "Done"
};

job_t *job_list_head = NULL;
int job_count = 0;


void add_to_jobs(job_t *job) {
    job->next = NULL;
    job->job_id = job_count++;

    if (!job_list_head) {   
        job_list_head = job;
    } else {
        job_t *curr = job_list_head;

        while (curr->next) {
            curr = curr->next;
        }

        curr->next = job;
    }
}

void print_jobs() {
    job_t *curr = job_list_head;

    while (curr) {
        printf("[%d] %s", curr->job_id, job_status_names[curr->status]);
        
        for (int i = 0; curr->command[i] != NULL; i++) {
            printf(" %s", curr->command[i]);
        }

        printf("\n");

        curr = curr->next;
    }
}


/**
 * @brief Checks for background execution in external command
 * 
 * @param argv command tokens
 * @return boolean true or false
 */
int check_for_background(char **argv) {
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "&") == 0) {
            return 1;
        }
    }
    return 0;
}
