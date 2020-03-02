
#include "bash.h"
#include <stdlib.h>


static char exited;

int main(){

	char** input;
	exited =1;

	 do {
	    	printPrompt();
		input =read_input();
		/*if(input!=NULL){
		check_for_pipe(input);
		exited = chooseCommand(input);
		}*/
		exited = chooseCommand(input);
		free(input);
	  } while (exited);
return 1;
}

