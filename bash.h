
#ifndef _BASH_
#define _BASH_


/**
gets the currrent working directory 
and prints it to act as a prompt
**/
void printPrompt();

/**
asks user for input
tokenizes the string
checks for "> , < or |"
**/
char** read_input();

/**
check  if the first argument contains a built in command
**/
int  chooseCommand(char** args);

/**
forks the process and executes the command accordingly
**/
int process(char**args);

/**
exists the program when the exit command is read
**/
int exit_program();

/**
changes directory if a path is sent
**/
int cd(char** args);


void check_for_pipe(char** args);
void seperateCommands(char ** args, int pointer);
/** checks the string for an '&' symbol
and activates the bg boolean
**/
void background(char** args);

#endif
