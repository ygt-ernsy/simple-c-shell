#ifndef COMMAND
#define COMMAND

typedef struct {
  int num;
  const char **tokens;
} Command;

Command makecmd(int num, const char **tokens); // for makeing Command stucts
char *getcmd();            // for reading the command inputted
int handlecmd(char **cmd); // this might change I am not sure rn?
int handlepipe_cmd(char **cmds);
void init(); // ???

#endif
