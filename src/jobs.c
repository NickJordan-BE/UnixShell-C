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


/**
 * @brief Adds job to list of jobs
 * 
 * @param job the job to be added
 */
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

/**
 * @brief Removes job from list of jobs
 * 
 * @param job the job to be removed
 */
void remove_job(job_t *job) {
    job_t *cur = job_list_head;

    if (cur == job) {
        job_list_head = NULL;
    }

    while (cur->next) {
        if (cur->next == job) {
            cur->next = cur->next->next;
        }
    }

    free(job);
}

/**
 * @brief Prints all jobs in the list
 * 
 */
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
 * @brief Creates and returns a job
 * 
 * @param pid the pid of the job
 * @param background boolean for bg or fg job
 * @param cmd the command
 */
job_t *create_job(pid_t pid, int background, char **cmd) {
    job_t *cur_job = malloc(sizeof(job_t));
    
    cur_job->pgid = pid;
    cur_job->status = RUNNING;
    cur_job->command = cmd;
    cur_job->is_background = background;
    add_to_jobs(cur_job);

    return cur_job;
}

/**
 * @brief Creates a deep copy of the list of strings
 * 
 * @param argv the list of strings
 * @param argc the lenght of the list
 */
char **serialize_command(char **argv, int argc) {
    char **copy = malloc((argc + 1) * sizeof(char *)); 
    if (!copy) return NULL;

    for (int i = 0; i < argc; i++) {
        copy[i] = malloc(strlen(argv[i]) + 1);
        if (!copy[i]) {
            for (int j = 0; j < i; j++) free(copy[j]);
            free(copy);
            return NULL;
        }
        strcpy(copy[i], argv[i]);
    }
    copy[argc] = NULL;
    return copy;
}

/**
 * @brief Finds and returns job by job_id
 * 
 * @param job_id the job_id of the job
 */
job_t *find_job(char *job_id) {
    job_t *cur = job_list_head;

    while (cur) {
        if (cur->job_id == atoi(job_id)) {
            return cur;
        }
    }

    return NULL;
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
