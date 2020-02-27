#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void printPrompt();
char** read_input();
void chooseCommand(char** args);

int main(){

	char** input;
	int exited;
	 do {
	    printPrompt();
		input =read_input();
		//printf( " here%s", input[0]);
		chooseCommand(input);
	  } while (exited);
	

/*
 //printf("hello world (pid:%s)\n", input);
    int rc = fork();
	
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
//execl("ls", "-l", "-a", foo, NULL);
        // child (new process)
        //printf("hello, I am child (pid:%d)\n", (int) getpid());
        //char *myargs[3];
        //myargs[0] = "ls";   // program: "wc" (word count)
        //myargs[1] = strdup("p3exec.c"); // argument: file to count
        //myargs[2] = NULL;           // marks end of array
        //execve(myargs[0], myargs);  // runs word count
	char *args[] = {"ls", "-l", "-a", (char *)0};
    	char *env_args[] = { (char*)0};
    	//execve("./example.c", NULL, NULL);
    	//printf("ERROR\n");
	system(input[0]);
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
	printPrompt();

    }
*/
}

void printPrompt(){

	//int ps= setenv("PS1","xxx",0);
	//printf("%s\n", ps);
	char *ps1 =getenv("PS1");
	//printf("%s\n", ps1);
	//echo ${PS1@P}   ;
	if(ps1 != NULL){
		printf("%s", ps1);
	}else{
		printf("%s", "$ ");
	}
}
char** read_input(){

	char buf[100];
	//char *str = malloc (sizeof (char) * strlen(buf)); 
    	fgets(buf, 100, stdin); 
	//char *newline = strchr( buf, '\n' );
	//	if ( newline )
 	//	 *newline = 0;
	//char string[100] = buf;
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
	//printf( " print %s\n", args[1] );
	//return token;
	//str = args[0];
	return args;

}

void chooseCommand(char** args){
	char *commands[] = {"cd","exit"};
	//printf("here2%shello",args[0]);
		if (strcmp(args[0], commands[0]) == 0){
			printf("%s\n","cd path");
		} 
		else if (strcmp(args[0], commands[1]) == 0){

			printf("%s\n","exit path");
		}
		else {
				printf("%s\n","other command");
	
		}
}



