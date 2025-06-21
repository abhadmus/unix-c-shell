/*
*
* [functions.c]
*
* Implements shell built-in functions and utility routines.
*
* Author: Abdus'Samad Bhadmus
*
* This file implements:
* - change_directory(): handles the cd built-in command.
* - display(): prints the prompt with current date and time.
*
*/

#include "shell.h"

/*
*
* change_directory: handles the cd built-in command.
* If no argument is provided, change to HOME.
* Otherwise, change to the specified directory.
*
*/

void change_directory(char **args) {
    if (args[1] == NULL) {
        /* No argument provided, change to HOME directory */
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
        } else if (chdir(home) != 0) {
            perror("cd");
        }
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

/*
*
* display: prints the prompt in the format:
* [dd/mm hh:mm]#
*
*/

void display() {
    char buffer[64];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, sizeof(buffer), "[%d/%m %H:%M]# ", t);
    printf("%s", buffer);
    fflush(stdout);
}

/*
*
* sigint_handler: handles Ctrl+C so the shell doesn't exit.
* It prints a new prompt line instead.
*
*/

void exit_redirect(int sig) {
    (void)sig;  // suppress unused parameter warning
    printf("\n");
    display();
    fflush(stdout);
}
