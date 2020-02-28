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
	background(args);
	
    	int rc = fork();
    	if (rc < 0) {
		// fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
    	} 
	else if (rc == 0) {// child process
	
		 // open stdin
		 if (input_file != NULL) {
		        int fd = open(input_file, O_RDONLY);

		        if (dup2(fd, STDIN_FILENO) == -1) {
		            fprintf(stderr, "dup2 failed");
		        }

		        close(fd);
		 }

		 // open stdout
		 if (output_file != NULL) {
		        int fd2;

		        if ((fd2 = open(output_file, O_WRONLY | O_CREAT, 0644)) < 0) {
		            perror("couldn't open output file.");
		            exit(0);
		      	}
		        dup2(fd2, STDOUT_FILENO);
		        close(fd2);
		    }	
		    
		
		if (execvp(args[0], args) == -1) {
			printf("%s: Command not Found\n", args[0]);
			int exitValue = WEXITSTATUS(system(args[0]));
			printf("EXIT VALUE: %d\n",exitValue);
			//int error = EXIT_FAILURE;
			//printf("%s",error);
    		}
    	} else {
		int status;
		// parent goes down this path (original process)
		if(!bg ) {
			waitpid(rc, NULL, 0);
        		//wait(NULL);
		    }
		 bg= 0;
		 wait(NULL);
		
		
	}
return 1;
    
}
int exit_program(){
  return 0;
}
int cd(char **args)
{
	
  	if (args[1] == NULL) {
		//char* s = getenv("PATH");
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

	if(strlen(buf)==1 && buf[0]==10){
	return copy;
}
	//char* bf = buf;
	num_of_words = count_words(bf);
	char** args=((tokenize(bf)));

	char* current;
	copy = malloc(strlen(bf) * sizeof(char *));
    // assume no redirections
        output_file = NULL;
        input_file = NULL;
	//pipe_sym=NULL;

        // split off the redirections
        int j = 0;
        int i = 0;
        while (1) {
            current = args[i++];
            if (current == NULL)
                break;
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
	char *commands[] = {"cd","exit"};
	if (strcmp(args[0], commands[0]) == 0){
		return cd(args);
		
		
	} 
	else if (strcmp(args[0], commands[1]) == 0){
		return exit_program();
	}
	else{

		return process(args);
		
	}
	return 0;
}

void background(char** args) {
	if(strcmp(args[num_of_words-1], "&") == 0) {
   	 bg = 1;
	//printf("background");
    	args[num_of_words-1] = NULL;
}
}
