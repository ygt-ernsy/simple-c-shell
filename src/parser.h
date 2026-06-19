#ifndef PARSER
#define PARSER

/* parses a given line and puts the tokens into a given char* array */
int parse(char *lineptr, char *tokens[]);
static int getword(char *word, char *lineptr, int lim);

#endif
