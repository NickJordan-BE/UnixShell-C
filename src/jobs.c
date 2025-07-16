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
