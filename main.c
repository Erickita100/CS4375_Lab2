#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

static char exited;
void printPrompt();
char** read_input();
void chooseCommand(char** args);
void process(char**input);
int exit_program();
int cd(char** args);
int main(){

	char** input;
	exited =1;
	 do {
		
	    printPrompt();
		input =read_input();
		//printf( " loop %d", exited);
		//chooseCommand(input);
		process(input);
	  } while (exited);
}

void process(char** input){
 	//printf("process %s\n", input[0]);
    	int rc = fork();
    	if (rc < 0) {
		// fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
    	} 
	else if (rc == 0) {// child process
		chooseCommand(input);
		//system("ls");
    	} else {
		// parent goes down this path (original process)
		int wc = wait(NULL);
		
	}
    
}
int exit_program(){
	printf("%d", exited );
	exited =0;
	printf("%d", exited );
  return 1;
}
int cd(char **args)
{
  if (args[1] == NULL) {
    printf("bash: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("bash:");
    }
  }
  return 1;
}

void printPrompt(){
	char s[100];
	if(getcwd(s, 100)!= NULL){
		printf("%s$ ", getcwd(s, 100));
	}else{
		printf("%s", "$ ");
	}
}
char** read_input(){
	char buf[100];
    	fgets(buf, 100, stdin); 
	char *token = (char *)malloc(((sizeof(char)) * strlen(buf))+1);
   	// Extract the first token
  	 token = strtok(buf, " \n\r\t");
   	// loop through the string to extract all other tokens
	char ** args = (char **)malloc((sizeof(char *))*(strlen(token)+1));
	int count =0;
   	while( token != NULL ) {
		args[count]=token;
		count++;
	      //printf( " %s", token ); //printing each token
      		token = strtok(NULL, " ");
   	}
	args[count]=0;
	return args;

}

void chooseCommand(char** args){
	char *commands[] = {"cd","exit"};
	if (strcmp(args[0], commands[0]) == 0){
		//printf("%s\n","cd path");
		cd(args);
		
	} 
	else if (strcmp(args[0], commands[1]) == 0){
		printf("%s\n","exit path");
		exit_program();
	}
	else {
		printf("%s\n","other command");
		
	}

}



