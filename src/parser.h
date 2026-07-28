#ifndef PARSER
#define PARSER

/* parses a given line and puts the tokens into a given char* array */
int parse(char *cmd, char *tokens[]);
int split_pipe_cmd(char *pipe_cmd, char *cmds[]);

#endif
