
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    	 
  	char s[100];
    // printing current working directory 
    printf("%s\n", getcwd(s, 100)); 
  
    // using the command 
    char * dir = ("../Desktop");
    chdir(dir); 
  
    // printing current working directory 
    printf("%s\n", getcwd(s, 100)); 
  
    // after chdir is executed 
    return 0; 
}
