/*
*
* main.c
* The main loop of the custom shell.
*
* Author: Abdus'Samad Bhadmus
*
* This file contains the shell's main loop that:
* - Prints a prompt (with date/time)
* - Reads a command from standard input
* - Tokenizes the command into arguments
* - Checks for built-in commands (like cd)
* - Parses a simple redirection operator (">")
* - Forks a child process to execute the command using execvp()
* - Waits for the child process to finish before prompting again
*
*/

#include "shell.h"

#define MAX_ARGS 64      /* Maximum number of arguments */
#define ACTIVE 1        /* Sets terms as active */
#define INACTIVE 0      /* Sets terms as inactive */
#define INITIALIZE 0        /* Used to initialize variables */
#define SET_READ_AND_WRITE 0666     /* Used to set the opening setting to reading and writing */

int main() {
    char *line = NULL;
    size_t len = INITIALIZE;
    ssize_t read_lines;
    char *args[MAX_ARGS];

    /* Set up signal handler for SIGINT (Ctrl+C) */
    signal(SIGINT, exit_redirect);

    while (ACTIVE) {
        /* Display the prompt */
        display();

        /* Read a line from stdin */
        read_lines = getline(&line, &len, stdin);
        if (read_lines == -1) {
            /* EOF encountered (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove trailing newline if present */
        if (line[read_lines - 1] == '\n')
            line[read_lines - 1] = '\0';

        /* Skip empty lines */
        if (strlen(line) == 0)
            continue;

        /* Tokenize input into arguments */
        int i_arg = INITIALIZE;
        int redirect = INACTIVE;
        char *output_file = NULL;
        char *token = strtok(line, " ");
        while (token != NULL && i_arg < MAX_ARGS - 1) {
            /* Check if token is a redirection operator */
            if (strcmp(token, ">") == 0) {
                redirect = ACTIVE;
                token = strtok(NULL, " ");
                if (token != NULL) {
                    output_file = token;
                } else {
                    fprintf(stderr, "Error: No output file specified\n");
                }
                break;  /* Stop processing further tokens */
            }
            args[i_arg++] = token;
            token = strtok(NULL, " ");
        }
        args[i_arg] = NULL;  /* Null-terminate the arguments array */

        if (args[0] == NULL) {
            /* No command entered */
            continue;
        }

        /* Check for built-in command: cd */
        if (strcmp(args[0], "cd") == 0) {
            change_directory(args);
            continue;
        }

        /* Fork a child process to execute the command */
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {  /* Child process */
            /* If redirection is specified, open the file and redirect stdout */
            if (redirect && output_file != NULL) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, SET_READ_AND_WRITE);
                if (fd < 0) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fd, STDOUT_FILENO) < 0) {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }
            /* Execute the command */
            if (execvp(args[0], args) < 0) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {  /* Parent process */
            int status;
            waitpid(pid, &status, 0);
        }
    }
    free(line);
    return 0;
}
