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
//char** pipe1;
//char** pipe2;
//char is_pipe;
int num_of_words;
char bg;

int process(char** args){
	//checks if the argument has a '&'
<<<<<<< HEAD
	//background(args);
	/*int my_pipe[2];
	if(pipe1!=NULL){
		//int my_pipe[2];
		pipe(my_pipe);	
	}*/
=======
	background(args);
	//int my_pipe[2];
	//if(pipe1!=NULL){
		//int my_pipe[2];
	//	pipe(my_pipe);	
	//}
>>>>>>> 5d62ea7b5f079068801528c059d2c366b43c5f4f
    	int rc = fork();
	int status;
    	if (rc < 0) {
		// fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
    	} 
	else if (rc == 0) {// child process
		
		 // redirection of input
		 // open stdin
		 if (input_file != NULL) {
		        int fd = open(input_file, O_RDONLY);

		        if (dup2(fd, STDIN_FILENO) == -1) {
		            fprintf(stderr, "dup2 failed");
		        }

		        close(fd);
		 }
<<<<<<< HEAD
		
		 // redirection of output
		if (output_file != NULL) {
=======

		 // open stdout
		 if (output_file != NULL) {
>>>>>>> 5d62ea7b5f079068801528c059d2c366b43c5f4f
		        int fd2;

		        if ((fd2 = open(output_file, O_WRONLY | O_CREAT, 0644)) < 0) {
		            perror("couldn't open output file.");
		            exit(0);
		      	}
		        dup2(fd2, STDOUT_FILENO);
		        close(fd2);
		    }	
<<<<<<< HEAD
		/*if(pipe1!=NULL){
			printf("hello");
			close(my_pipe[0]);   /*Closes read side of pipe*/
			//close(1);       //STDOUT closed
			//dup2(my_pipe[1],1);
					//args[0] = pipe1[0];
					//printf("%s\n", pipe1[0]);
			//execvp(pipe1[0], pipe1);
					
		//}*/
			//printf("LLLL");
=======
		//if(pipe1!=NULL){
		//	printf("hello");
		//	close(my_pipe[0]);   /*Closes read side of pipe*/
		//	close(1);       //STDOUT closed
		//	dup2(my_pipe[1],1);
					//args[0] = pipe1[0];
					//printf("%s\n", pipe1[0]);
		//	execvp(pipe1[0], pipe1);
					
		//}
			printf("LLLL");
>>>>>>> 5d62ea7b5f079068801528c059d2c366b43c5f4f
				//executes given command
		if(execvp(args[0], args) == -1) {
			printf("%s: Command not Found\n", args[0]);
			int exitValue = WEXITSTATUS(system(args[0]));
			printf("Program terminated with exit code: %d\n",exitValue);
			}
			
		

    	} else {
<<<<<<< HEAD
		/*if(pipe2!=NULL){
			wait(&rc);        //waits till the child send output to pipe
       			close(my_pipe[1]);
        		close(0);       //stdin closed
        		dup2(my_pipe[0],0);
        		execvp(pipe2[0],pipe2);
		}*/
=======
		//if(pipe2!=NULL){
		//	wait(&rc);        //waits till the child send output to pipe
       		//	close(my_pipe[1]);
        	//	close(0);       //stdin closed
        	//	dup2(my_pipe[0],0);
        	//	execvp(pipe2[0],pipe2);
		//}
>>>>>>> 5d62ea7b5f079068801528c059d2c366b43c5f4f
		
		// parent process
		if(!bg ) {
			waitpid(rc, &status, 0);
		    }
		 bg= 0;
		
		
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
		        if (current[1] == 0){
		            current = args[i++];}
		        else{
		            ++current;}
		        input_file = current;
		       
		        break;

		    case '>':
		        if (current[1] == 0){
		            current = args[i++];}
		        else{
		            	++current;}
		        output_file = current;
		    
		        break;
		    /*case '|':
			if (current[1]==0){
			    current = args[i++];
			}else{
				++current;}
			pipe_arg = current;
			printf("here");
			//copy[j] = NULL;
			
			//return copy;
			break;*/
		    default:
		        copy[j++] = current;
		        break;
		}
        }
        copy[j] = NULL;

	return copy;

}
/*
void check_for_pipe(char** args){

	int  counter =0;
  	char** p = args;
  	for(;*p!=NULL;p++){
		if(strcmp(*p,"|")==0){
		is_pipe ='1';
    		//printf("| found");
		seperateCommands(args,counter);
		}
	is_pipe ='0';
     	counter++;
  }
	
}

void seperateCommands(char ** args, int pointer){
	//char** tokens = (char **)malloc((sizeof(char *))*(count_words(str)+1));
	pipe1 = (char **)malloc((sizeof(char *))*(pointer+1));
	pipe2 = (char **)malloc((sizeof(char *))*(num_of_words-pointer+1));
	for(int i =0; i <pointer;i++){
		pipe1[i] = copy_word(args[i]);
		
		//printf("pointer = %d %s\n",pointer, pipe1[i]);
	}
	int count =0;
	for(int i =pointer+1; i <num_of_words;i++){
		pipe2 [count]= copy_word(args[i]);
		//printf("@pointer = %d %s\n",pointer, pipe2[count]);
		count++;
	}
}*/
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
