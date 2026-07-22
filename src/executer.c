#include "executer.h"
#include <stdio.h>
#include <unistd.h>

/* executes the given parsed command, the first argument is the number of tokens
 * in the command */
int execute(const int argc, char *const tokens[])
// TODO: Impelement waiting for the child process
{
    // step1: fork the current process
    // step2: if 0 (child) execvp the given command with the given arguments
    // step3: if parent ?

    char *args[argc];

    // I probably don't need to copy the given array to make it null terminated
    // TODO: Find a better way
    for (int i = 0; i < argc - 1; i++)
    {
        args[i] = tokens[i];
    }

    // Null terminate the array
    args[argc - 1] = NULL;

    int pid = fork();

    if (pid == 0) // child
    {
        // NOTE: is this the way I should do this?
        if (execvp(tokens[0], args) < 0) // this is not executing
            perror("ERROR: execvp");
    }
    else if (pid < 0)
    {
        // NOTE: should I use perror?
        printf("something went wrong when forking\n");
        return -1;
    }

    return 1;
}
