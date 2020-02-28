#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "tokenizer.h"
#include "bash.h"

char* input_file;
char* output_file;
int num_of_words;
char bg;

int process(char** args){
	//checks if the argument has a '&'
	background(args);
	
    	int rc = fork();
	
    	if (rc < 0) {
		// fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
    	} 
	else if (rc == 0) {// child process
		
		 // redirection of input
		 if (input_file != NULL) {
		        int fd = open(input_file, O_RDONLY);

		        if (dup2(fd, STDIN_FILENO) == -1) {
		            fprintf(stderr, "dup2 failed");
		        }

		        close(fd);
		 }
		
		 // redirection of output
		 if (output_file != NULL) {
		        int fd2;

		        if ((fd2 = open(output_file, O_WRONLY | O_CREAT, 0644)) < 0) {
		            perror("couldn't open output file.");
		            exit(0);
		      	}
		        dup2(fd2, STDOUT_FILENO);
		        close(fd2);
		    }	
		    
		//executes given command
		if (execvp(args[0], args) == -1) {
			printf("%s: Command not Found\n", args[0]);
			int exitValue = WEXITSTATUS(system(args[0]));
			printf("EXIT VALUE: %d\n",exitValue);
			//int error = EXIT_FAILURE;
			//printf("%s",error);
    		}
    	} else {
		int status;
		// parent process
		if(!bg ) {
			waitpid(rc, &status, 0);
        		//wait(NULL);
		    }
		 bg= 0;
		 //wait(NULL);
		
		
	}
	return 1;
    
}

int exit_program(){
  	return 0;
}

int cd(char **args){
	//changes directory in the parent process, else it will change only in the child
	
  	if (args[1] == NULL) {
		//char* s = getenv("PATH");
		//printf("path = %s\n", s);
		//chdir(s);
    		printf("bash: expected argument to \"cd\"\n");
  	} else {
	    	if (chdir(args[1]) != 0) {
	      	perror("bash");
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
	char** copy;
	char buf[100];
    	fgets(buf, 100, stdin); 
	char* bf = buf;

	if(strlen(buf)==1 && strcmp(buf," ")){
		return NULL;
	}
	//tokenizes the string
	num_of_words = count_words(bf);
	char** args=((tokenize(bf)));

	char* current;
	copy = malloc(strlen(bf) * sizeof(char *));

        output_file = NULL;
        input_file = NULL;
	//pipe_sym=NULL;

        // checks for redirections and creates a new argument
        int j = 0;
        int i = 0;
        while (1) {
            current = args[i++];
            	if (current == NULL){
                break;
		}
	 	switch (*current) {
		    case '<':
		        if (current[1] == 0)
		            current = args[i++];
		        else
		            ++current;
		        input_file = current;
		       
		        break;

		    case '>':
		        if (current[1] == 0)
		            current = args[i++];
		        else
		            ++current;
		        output_file = current;
		    
		        break;
		
		    default:
		        copy[j++] = current;
		        break;
		}
        }
        copy[j] = NULL;

	return copy;

}

int chooseCommand(char** args){
	//built in commands
	char *commands[] = {"cd","exit"};
	if (strcmp(args[0], commands[0]) == 0){
		return cd(args);
		
	} 
	else if (strcmp(args[0], commands[1]) == 0){
		return exit_program();
	}
	else{
	//if not a built in commands then create a child process
		return process(args);
		
	}
	return 0;
}

//if the last symbol is a & symbol then activate the background boolean
void background(char** args) {
	if(strcmp(args[num_of_words-1], "&") == 0) {
   	 bg = 1;
    	args[num_of_words-1] = NULL;
}
}
