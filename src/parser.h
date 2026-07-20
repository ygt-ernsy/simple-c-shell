#ifndef PARSER
#define PARSER

/* parses a given line and puts the tokens into a given char* array */
int parse(char *cmd, char *tokens[]);
static int getword(char *word, char *cmd, int lim);
static int check_for_pipe(char *cmd);

#endif
