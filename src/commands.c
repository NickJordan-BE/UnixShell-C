/**
 * @file commands.c
 * @brief Contains all built-in functions
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <regex.h>
#include <signal.h>
#include "../include/parser.h"
#include "../include/jobs.h"

/**
 * @brief Echos input to shell
 * 
 * @param argc token count
 * @param argv command tokens
 */
void echo_command(int argc, char **argv) {
    if (argv[0][0] != '"' || argv[argc - 1][strlen(argv[argc - 1]) - 1] !=  '"') {
        fprintf(stderr, "Unknown\n");
        return;
    }

    memmove(argv[0], argv[0] + 1, strlen(argv[0]));

    if (argc == 1) {
        argv[0][strlen(argv[0]) - 1] = '\0';
    } else {
        argv[argc - 1][strlen(argv[argc - 1]) - 1] = '\0';
    }

    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }

    printf("\n");
}

/**
 * @brief Changes current directory
 * 
 * @param argc token count
 * @param argv command tokens
 */
void cd_command(int argc, char **argv) {
    if (argc != 1) {
        fprintf(stderr, "Incorrect Argument Numbers");
    }
    
    char *path = argv[0];

    if (chdir(path) != 0) {
        fprintf(stderr, "Directory change failed.");
    } else {
        printf("Directory changed successfully.\n");
    }
}

/**
 * @brief Exits shell
 * 
 * @param argc token count
 * @param argv command tokens
 */
void exit_command(int argc, char **argv) {
    (void)argc, (void)argv;
    free_tokens();
    printf("Exiting shelldon...\n");
    exit(0);
}

/**
 * @brief Displays supported commands
 * 
 * @param argc token count
 * @param argv command tokens
 */
void help_command(int argc, char **argv) {
    (void)argc, (void)argv;
    printf("Supported Commands:\n1. echo\n2. cd\n3. exit\n4. help\n5. history\n6. sizeof\n7. clear\n8. pwd\n9. grep");
}

/**
 * @brief Displays command history
 * 
 * @param argc token count
 * @param argv command tokens
 */
void history_command(int argc, char **argv) {
    if (argc != 0) {
        char *cmd = argv[0];

        if (strcasecmp(cmd, "-1") == 0) {
            FILE *fp = fopen("shelldon-history.txt", "w");
            printf("Clearing history...\n");

            if (fp == NULL) {
                fprintf(stderr, "Error opening history file.\n");
                return;
            }
            fclose(fp);
        }
    } else {
        FILE *fp = fopen("shelldon-history.txt", "r");

        if (fp == NULL) {
            fprintf(stderr, "Error opening history file.\n");
            return;
        }

        char line[1024];
        int count = 1;

        while (fgets(line, sizeof(line), fp)) {
            printf("%i. %s\n", count, line);
            count++;
        }
        fclose(fp);
    }
}

/**
 * @brief Displays how many arguments passed into command
 * 
 * @param argc token count
 * @param argv command tokens
 */
void sizeof_command(int argc, char **argv) {
    (void)argv;
    printf("%i\n", argc);
}

/**
 * @brief Clears display and resest cursor
 * 
 * @param argc token count
 * @param argv command tokens
 */
void clear_command(int argc, char **argv) {
    (void)argc, (void)argv;
    printf("\033[H\033[J");
    fflush(stdout);
}

/**
 * @brief Prints current working directory
 * 
 * @param argc token count
 * @param argv command tokens
 */
void pwd_command(int argc, char **argv) {
    (void)argc, (void)argv;
    char buffer[1024];
    
    if (getcwd(buffer, sizeof(buffer)) == NULL) {
        fprintf(stderr, "Unable to get current directory.\n");
    } else {
        printf("%s\n", buffer);
    }
}

/**
 * @brief Checks for patterns in files
 * 
 * @param argc token count
 * @param argv command tokens
 */
void grep_command(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Invalid number of arguments.");
    }

    regex_t regex;
    int reg_res;
    memmove(argv[0], argv[0] + 1, strlen(argv[0]));
    argv[0][strlen(argv[0]) - 1] = '\0';
    char *path = argv[0], *pattern = argv[1];

    reg_res = regcomp(&regex, pattern, REG_EXTENDED);

    if (reg_res) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    FILE *fp = fopen(path, "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != 1 && strlen(line) != 0) {
        reg_res = regexec(&regex, line, 0, NULL, 0);

        if (!reg_res) {
            printf("%s\n", line);
        }
    }

    regfree(&regex);
    free(line);
    fclose(fp);
}

/**
 * @brief Prints all background jobs
 * 
 * @param argc token count
 * @param argv command tokens
 */
void jobs_command(int argc, char **argv) {
    (void)argc;
    (void)argv;
    print_jobs();
}

/**
 * @brief Brings job to the foreground
 * 
 * @param argc token count
 * @param argv command tokens
 */
void fg_command(int argc, char **argv) {
    if (argc != 1) {
        return;
    }
    job_t *job;

    if (!(job = find_job(argv[0]))) {
        printf("No Job with Given Job ID\n");
        return;
    }

    if (job->pgid > 0) {
        kill(job->pgid, SIGCONT);           
        waitpid(job->pgid, NULL, 0);        
        remove_job(job);
    }
}

/**
 * @brief Resumes job in the background
 * 
 * @param argc token count
 * @param argv command tokens
 */
void bg_command(int argc, char **argv) {
    if (argc != 1) {
        return;
    }
    job_t *job;

    if (!(job = find_job(argv[0]))) {
        printf("No Job with Given Job ID\n");
        return;
    }

    if (job->pgid > 0) {
        kill(job->pgid, SIGCONT);
        job->status = RUNNING;
        printf("[%d] %d resumed in background\n", job->job_id, job->pgid);
    }
}