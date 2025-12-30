#ifndef SHELL_H
#define SHELL_H

/*
*
* [shell.h]
*
* Header file for the custom shell.
*
* Author: Abdus'Samad Bhadmus
*
* This file includes necessary system headers and declares
* functions used in the shell implementation.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

void display();
void exit_redirect(int sig);
void change_directory(char **args);

#endif
