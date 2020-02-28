
#ifndef _BASH_
#define _BASH_

void printPrompt();
char** read_input();
int  chooseCommand(char** args);
int process(char**args);
int exit_program();
int cd(char** args);
void background(char** args);

#endif
