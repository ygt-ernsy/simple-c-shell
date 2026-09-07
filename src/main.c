#include "command.h"
#include "executer.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char *splitcmd[BUFSIZ];
    char *cmd = NULL;
    size_t len = 0;
    int pipes;

    while (getline(&cmd, &len, stdin) != EOF)
    {
        switch (pipes = split_pipe_cmd(cmd, splitcmd))
        {
        case -1: // handle error
            perror("Something went wrong while splitting from pipe.\n");
            break;
        case 1: // no pipes
            handlecmd(splitcmd);
            break;
        default: // at least 1 pipe
            handlepipe_cmd(splitcmd, pipes);
            break;
        }
    }
    return EXIT_SUCCESS;
}

int handlecmd(char **cmd)
{
    char *tokens[BUFSIZ];

    // cmd[0] since if there is no pipe
    // there is only one command
    // hence only 1 entry cmd[0]
    const int argc = parse(cmd[0], tokens);
    if (argc == -1)
        return -1;

    execute(argc, tokens, STDIN_FILENO, STDOUT_FILENO);

    return 1;
}

int handlepipe_cmd(char **cmds, int numcmds)
{
    int pipedes[2];
    char *tokens[BUFSIZ];
    int i;
    int argc;
    int wfd;
    int rfd;

    // first cmd
    argc = parse(cmds[0], tokens);
    if (argc == -1)
        return -1;

    // the first pipe
    pipe(pipedes);
    // setting up the wfd and rfd
    wfd = pipedes[1];
    rfd = pipedes[0];

    // execute the first command
    execute(argc, tokens, STDIN_FILENO, wfd);

    // clear the array
    memset(tokens, 0, sizeof(tokens));

    // execute the commands between first and las
    for (i = 1; i < numcmds - 1; i++)
    {
        // set up new pipe and wfd
        pipe(pipedes);
        wfd = pipedes[1];

        // execute the current cmd (read from the old pipe's rfd)
        argc = parse(cmds[i], tokens);
        if (argc == -1)
            return -1;
        execute(argc, tokens, rfd, wfd);

        // clear the array
        memset(tokens, 0, sizeof(tokens));

        // switch to the current pipe's rfd so the next command can read from it
        rfd = pipedes[0];
    }

    // execute last cmd
    argc = parse(cmds[numcmds - 1], tokens);
    if (argc == -1)
        return -1;

    execute(argc, tokens, rfd, STDOUT_FILENO);

    return 1;
}
