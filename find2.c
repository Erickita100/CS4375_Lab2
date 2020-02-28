
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//main program
int main(int argc, char *arvg[]){
    char d[30];                                     //array of characters

        scanf("%s", d);                             //read input from user
    int t= find2(d,".");
    if (t==1)
        printf("Found %s\n", d);                    //to be printed if item is found
    else
        printf("Could not find %s\n", d); //to be printed if item is not found

    exit(0);
}
int find2(char d[],char a[] )                        //find function
{
    DIR *dp;                                        //first directory 
    DIR *dp1;
    struct dirent *dirp;                            //second directory 
    char o[70];
    char g[80];
    strcpy(o,a);
    strcpy(g,o);
    if ((dp1=opendir(d)) != NULL)                   //opens first directory
        return 1;
    if ((dp=opendir(a)) == NULL)                    //opens second directory
        return 0;
    while ((dirp=readdir(dp))!=NULL){
        strcpy(o,g);
        strcat(o,"/");
        strcat(o,dirp->d_name);
        if (strcmp(dirp->d_name,d)==0)
            return 1;
        else if ((strcmp(dirp->d_name,".")==0)||(strcmp(dirp->d_name,"..")==0))
            continue;
        else if (find2(d,o)==0)
            continue;
        else
            return 1;
    }
    return 0;
}
