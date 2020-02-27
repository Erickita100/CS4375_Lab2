#include <stdio.h> 
#include <dirent.h> 

int main(void) 
{ 
    struct dirent *de;  // Pointer for directory entry 
    int count;
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("."); 
    DIR *drr = opendir(".");
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    // for readdir() 
    while ((de = readdir(dr)) != NULL){ 
            printf("%s\n", de->d_name); 
	    count++;
    }
    struct dirent *da;
    char *directories[count];
    int i = 0;
    while(i<count){
	while((da = readdir(drr)) != NULL){
		directories[i] =da->d_name;
		i++;
	} 
    }
    for(int j = 0; j < count; j++){
	printf("%s ",directories[j]);
    }
    printf("\n YEAH \n");
    closedir(dr);     
    return 0;
}
