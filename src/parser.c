#include "parser.h"
#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* parses a given line and puts the individual words into a given char* array */
int parse(char *lineptr, char *tokens[])
{
    char word[BUFSIZ];
    int i = 0;
    char c;

    // TODO: is BUFSIZ correct way?
    while (getword(word, lineptr, BUFSIZ) >= 0)
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
static int getword(char *word, char *lineptr, int lim)
{
    char *c = lineptr;
    int i = 0;

    if (lineptr == NULL)
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
        *(lineptr + i) = ' ';
    }

    *word++ = '\0';

    return word[0];
}
