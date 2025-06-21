Custom Shell Implementation
===========================

Author: Abdus'Samad Bhadmus
Date: 2025

-------------------------------------------------------------------------------

OVERVIEW

This project implements a simple custom Unix shell in C that supports:

- Displaying a prompt with current date and time
- Reading and parsing user commands with arguments
- Handling the built-in 'cd' command to change directories
- Supporting simple output redirection using '>'
- Executing external commands using fork() and execvp()
- Handling Ctrl+C (SIGINT) gracefully without exiting the shell

-------------------------------------------------------------------------------

FILE DESCRIPTIONS

main.c        : Contains the main shell loop. Handles input, parsing, forking, execution, redirection, and built-ins.

functions.c   : Contains utility and built-in function implementations, such as 'cd', prompt display, and signal handler.

shell.h       : Header file for function declarations and required system includes.

Makefile      : Build automation file for compiling the shell program.

-------------------------------------------------------------------------------

FEATURES

- Prompt format: [dd/mm hh:mm]# 
- Supports multiple arguments per command
- Built-in 'cd' command:
    - Changes to the specified directory
    - If no directory is given, defaults to $HOME
- Simple output redirection using '>' (writes command output to a file)
- Executes external commands using a child process
- Captures and handles Ctrl+C (SIGINT) to prevent shell termination

-------------------------------------------------------------------------------

COMPILATION

Use the Makefile to compile the program:

    make

This will build an executable named 'head' from main.c and functions.c.

To clean up object files and the executable:

    make clean

To create a distribution tarball:

    make dist

-------------------------------------------------------------------------------

RUNNING THE SHELL

To run the shell, type:

    ./head

You will see a shell prompt like:

    [04/07 14:30]# 

From here, you can enter normal shell commands. Examples:

    ls -l
    cd /tmp
    pwd
    echo Hello > out.txt

To exit the shell, press Ctrl+D (EOF).

-------------------------------------------------------------------------------

EXAMPLE USAGE

    [04/07 14:30]# cd /var/log
    [04/07 14:30]# ls -la > logs.txt
    [04/07 14:30]# cat logs.txt
    [04/07 14:31]# cd
    [04/07 14:31]# exit   <-- (Ctrl+D)

-------------------------------------------------------------------------------

NOTES

- This shell only supports output redirection ('>') to files.
- Input redirection ('<') and piping ('|') are not supported.
- Commands are parsed by splitting on spaces.
- Maximum number of arguments is set to 64.
- The shell catches SIGINT (Ctrl+C) and displays a fresh prompt instead of exiting.
- EOF (Ctrl+D) will terminate the shell session gracefully.

-------------------------------------------------------------------------------

LICENSE

This project is intended for educational use and comes with no warranty.
