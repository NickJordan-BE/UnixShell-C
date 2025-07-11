/**
 * @file main.c
 * @brief Entry point for shell
 *
 */
#include "../include/shell.h"

/** 
 * @brief Used for clean entry, starting the shell loop.
 * 
 * @return exit condition
 */
int main() {
    shell_loop();
    return 0;
}