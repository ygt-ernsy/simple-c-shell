#include "parser.h"
#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: The new split_pipe_cmd works but I can't create enough arrays for every
// command block even though split_pipe_cmd returns the num of commands, so I
// thought about making the command a struct which has a char *cmd and a
// char **tokens. This way I think I can create a function for creating commands
// so I can use a for loop for parsing and creating commands

/* parses a given line and puts the individual words into a given char* array */
int parse(char *cmd, char *tokens[])
{
    char word[BUFSIZ];
    int i = 0;

    // TODO: is BUFSIZ correct way?
    while (getword(word, cmd, BUFSIZ) >= 0)
    {
        char *token = malloc((BUFSIZ + 1) * sizeof(char));

        if (token == NULL)
            return -1;

        strlcpy(token, word, BUFSIZ);
        tokens[i++] = token;
    }

    return 1;
}

/* takes a cmd with pipes and splits it to commands and puts them into char*
 * cmds[], returns the number of cmds or -1 when something goes wrong */
int split_pipe_cmd(char *pipe_cmd, char *cmds[])
// TODO: find a better name
{
    int p = check_for_pipe(pipe_cmd); // get the first pipe location
    char c[BUFSIZ];
    int index = 0;

    while (p > 0)
    {
        // skip spaces
        while (isspace(*pipe_cmd))
            pipe_cmd++;

        // get the command
        int i = 0;
        for (; i < p; i++)
            c[i] = *pipe_cmd++;
        // make c null terminated
        c[i + 1] = '\0';

        // p is 1 bigger than the length of cmd
        char *cmd = malloc(p * sizeof(char));
        if (cmd == NULL)
            return -1;

        strlcpy(cmd, c, BUFSIZ);
        cmds[index++] = cmd; // TODO: how can I handle index out of bounds?

        // clearning c so it can be used again
        memset(c, '\0', sizeof(c));

        p = check_for_pipe(pipe_cmd);
    }

    while (isspace(*pipe_cmd))
        pipe_cmd++;

    for (int i = 0; *pipe_cmd != '\0' && *pipe_cmd != '\n'; i++)
    {
        c[i] = *pipe_cmd++;
    }

    *pipe_cmd = '\0';

    char *cmd = malloc(BUFSIZ * sizeof(char));
    strlcpy(cmd, c, BUFSIZ);
    cmds[index++] = cmd;

    // clear for good measure ?
    // on subsocuent uses I encountered issue that were fixed with this line
    memset(c, '\0', sizeof(c));

    return index;
}

/* writes the first word of a given line into char *word and replaces the read
 * section of the line with blank */
static int getword(char *word, char *cmd, int lim)
{
    char *c = cmd;
    int i = 0;

    if (cmd == NULL)
        return -1;

    while (isspace(*c))
    {
        i++;
        c++;
    }

    if (*c == '\0' || *c == '\n')
        return -1;

    // added to prevent core dumps when a command contains a punct
    for (; (ispunct(*c) || isalnum(*c)) && lim-- > 0; c++, i++)
    {
        *word++ = *c; // NOTE: Is this safe?

        // this is so getword skips the already read parts in the next iteration
        // TODO: Find a better way to handle this
        *(cmd + i) = ' ';
    }

    *word++ = '\0';

    return word[0];
}

/* returns the position of the first '|', -1 if not present */
int check_for_pipe(char *cmd)
{
    char *c = cmd;
    int i;

    if (cmd == NULL)
    {
        return -1;
    }

    int len = strlen(cmd);

    for (i = 0; *c != '|' && i < len; c++, i++)
        ;

    if (*c == '|')
    {
        *c = ' ';
        return i;
    }

    return -1;
}
