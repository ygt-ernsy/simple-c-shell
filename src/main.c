#include "command.h"
#include "executer.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *splitcmd[BUFSIZ];
    char *cmd = NULL;
    size_t len = 0;

    while (getline(&cmd, &len, stdin))
    {
        switch (split_pipe_cmd(cmd, splitcmd))
        {
        case -1: // handle error
            perror("Something went wrong while splitting from pipe.\n");
            break;
        case 1: // no pipes
            handlecmd(splitcmd);
            break;
        default: // at least 1 pipe
            handlepipe_cmd(splitcmd);
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

    execute(argc, tokens);

    return 1;
}

int handlepipe_cmd(char **cmds) { return 1; }
