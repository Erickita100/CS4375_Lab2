#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "tokenizer.h"

static char exited;
void printPrompt();
char** read_input();
int  chooseCommand(char** args);
int process(char**args);
int exit_program();
int cd(char** args);

int main(){

	char** input;
	exited =1;

	 do {
	    	printPrompt();
		input =read_input();
		//printf( " loop %d", exited);
		exited = chooseCommand(input);
		//process(input);
		//printf( " loop %d", input[0]);
		free(input);
	  } while (exited);
}

int process(char** args){
 	//printf("command %s", args[0]);
    	int rc = fork();
    	if (rc < 0) {
		// fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
    	} 
	else if (rc == 0) {// child process
		//chooseCommand(input);
		//system(args[0]);
		/*
		if(strcmp(args[1], ">") && args[2] != NULL){
			int fd0 = open(args[2], O_RDONLY);
        		dup2(fd0, STDIN_FILENO);
        		close(fd0);
			/*
			close(STDOUT_FILENO); 
			open(args[2], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
			args[1]=NULL;
			args[2]=NULL;
*/
		//}
		//printf("OOOOOO%s", args[0] );
		if (execvp(args[0], args) == -1) {
	         
     		 perror("bash");
    		}
    	} else {
		// parent goes down this path (original process)
		 wait(NULL);
		
	}
return 1;
    
}
int exit_program(){
	//printf("%d", exited );
	//exited =0;
	//printf("%d", exited );
  return 0;
}
int cd(char **args)
{	//printf("LLLLLL%s$LLLL ",args[1]);
	
  	if (args[1] == NULL) {
		//char* s = getenv("PATH");
		//chdir(s);
    		printf("bash: expected argument to \"cd\"\n");
  	} else {
	    	if (chdir(args[1]) != 0) {
	      	perror("bash:");
	    	}
		//system("ls");
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
	char* bf = buf;
	char** args=((tokenize(bf)));
  	//print_tokens(tokens);	   
  	//free_tokens(tokens);

/*
	char *token = (char *)malloc(((sizeof(char)) * strlen(buf))+1);
   	// Extract the first token
  	 token = strtok(buf, " \n\t\r);
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
*/
	return args;

}

int chooseCommand(char** args){
	//printf("first%s\n",args[0]);
	char *commands[] = {"cd","exit"};
	if (strcmp(args[0], commands[0]) == 0){
		//printf("second%s\n",args[0]);
		//process(args);
		return cd(args);
		//return 1;
		
	} 
	else if (strcmp(args[0], commands[1]) == 0){
		//printf("%s\n","exit path");
		return 0;
		//return ;
	}
	else{/*
		//printf("LLLLL%s",args[0]);
		if( args[1] != NULL && strcmp(args[1], ">")){
			if(args[2] == NULL){
				printf("bash: expected argument to \"ls >\"\n");
			}
			args[1]=NULL;
			args[2]=NULL;
			//return process(args);
		}
		//printf("%s\n",args[0]);
		//process(args);
		//return 3;
*/
	
		return process(args);
		
	}
	//process(args);
	return 0;
}



