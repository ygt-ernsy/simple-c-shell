#include "parser.h"
#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: The implementation here is ought to cause problems later
// the parser should be able to differantiate different commands
// and be able to do that even when there isn't a ' ' between a
// command and a '|', example: command1|command2
// so I need to not only account for possible connectors between commands
// but also find some way to relay that so it can be handled
//
// TODO: How should the parsing be handled? Would a command be parsed, if so
// will this be a 2 dimentional array containing strings? Won't that be too
// complex?
// How will I handle multple command chains? Will here be a limit?
//
// NOTE: Some ideas:
// a function that relays the connector symbol or returns a -1 or smth

/* parses a given line and puts the individual words into a given char* array */
int parse(char *cmd, char *tokens[])
{
    char word[BUFSIZ];
    int i = 0;
    char c;

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

/* writes the first word of a given line into char *word and replaces the read
 * section of the line with blank */
static int getword(char *word, char *cmd, int lim)
// TODO:
// I can modify this to detect | and take them as seperate tokens but
// I would need a buffer system for that I think
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

    for (; isalnum(*c) && lim-- > 0; c++, i++)
    {
        *word++ = *c; // NOTE: Is this safe?

        // this is so getword skips the already read parts in the next iteration
        // TODO: Find a better way to handle this
        *(cmd + i) = ' ';
    }

    *word++ = '\0';

    return word[0];
}

/* returns the position of '|', -1 if not present */
int check_for_pipe(char *cmd)
{
    char *c = cmd;
    int i;

    if (cmd == NULL)
        return -1;

    for (i = 0; *(c + i) != '|' && i < strlen(cmd); i++)
        ;

    if (*c == '|')
        return i;

    return -1;
}
