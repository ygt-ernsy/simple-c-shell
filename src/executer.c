#include "executer.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/* executes the given parsed command, the first argument is the number of tokens
 * in the command */
int execute(const int argc, char *const tokens[])
// NOTE: should this function take in a command struct as an argument
// TODO: Impelement waiting for the child process
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
        printf("something went wrong when forking\n"); // This or perror?
        return -1;
    }

    if (pid > 0)
    { // parent
        wait(&pid);
    }
    else if (pid == 0) // child
    {
        // NOTE: is this the way I should do this?
        if (execvp(tokens[0], args) < 0)
            perror("ERROR: execvp");
    }

    return 1;
}
