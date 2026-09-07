#include "executer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Forks a new process to execute the given parsed command.
 *
 * Parameters:
 *   argc   - The total number of tokens, including the command itself.
 *   tokens - An array of strings representing the command and its arguments.
 *   infd   - The file descriptor to use for the command's standard input.
 *   outfd  - The file descriptor to use for the command's standard output.
 *
 * Returns:
 *   The raw termination status of the child process (to be parsed with
 *   WIFEXITED/WEXITSTATUS macros), or -1 if a system call like fork or waitpid
 * fails.
 */
int execute(const int argc, char *const tokens[], int infd, int outfd)
// NOTE: should this function take in a command struct as an argument
{
    char *args[argc + 1];

    // I probably don't need to copy the given array to make it null terminated
    for (int i = 0; i < argc; i++)
    {
        args[i] = tokens[i];
    }

    // Null terminate the array
    args[argc] = NULL;

    int pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(-1);
    }

    if (pid > 0)
    { // parent
        int status;
        int w = waitpid(pid, &status, 0);
        if (w < 0)
        {
            perror("waitpid");
            exit(-1); // NOTE: should I use exit() here?
        }
        // NOTE: should I return the status here?
        return status;
    }
    else if (pid == 0) // child
    {
        dup2(infd, STDIN_FILENO);   // make stdin infd
        dup2(outfd, STDOUT_FILENO); // make stdout outfd

        // NOTE: is this the way I should do this?
        int e = execvp(tokens[0], args);
        if (e < 0)
        {
            perror("execvp");
            exit(-1); // NOTE: should I use exit here?
        }
    }

    return 1;
}
