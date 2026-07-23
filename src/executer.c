#include "executer.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * executes the given parsed command, the first argument is the number of tokens
 * in the command
 * */
int execute(const int argc, char *const tokens[])
// NOTE: should this function take in a command struct as an argument
{
    char *args[argc];

    // I probably don't need to copy the given array to make it null terminated
    for (int i = 0; i < argc - 1; i++)
    {
        args[i] = tokens[i];
    }

    // Null terminate the array
    args[argc - 1] = NULL;

    int pid = fork();
    if (pid < 0)
    {
        perror("fork"); // This or perror?
        return -1;
    }

    if (pid > 0)
    { // parent
        int status;
        int w = waitpid(pid, &status, 0);
        if (w < 0)
        {
            perror("waitpid");
            return -1; // NOTE: should I use exit() here?
        }
        // NOTE: should I return the status here?
    }
    else if (pid == 0) // child
    {
        // NOTE: is this the way I should do this?
        int e = execvp(tokens[0], args);
        if (e < 0)
        {
            perror("ERROR: execvp");
            return -1; // NOTE: should I use exit here?
        }
    }

    return 1;
}
