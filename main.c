
#include "bash.h"
#include <stdlib.h>


static char exited;


char* input_file;
char* output_file;
int num_of_words;
char bg;

int main(){

	char** input;
	exited =1;

	 do {
	    	printPrompt();
		input =read_input();
		if(input!=NULL){
		exited = chooseCommand(input);
		
		free(input);
		}
	  } while (exited);
return 1;
}

