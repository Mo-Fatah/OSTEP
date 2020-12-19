#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#define size (100)
int main(int argc , char *argv[]){
    FILE *fil = fopen(argv[1] , "r");
    if(fil == NULL){
        printf("cannot open file\n");
        exit(1);
    }
    else{
        printf("Found.. the contents is :\n\n");
    }
    char buffer[size];
    while(fgets(buffer , size , fil) != NULL){
        printf("%s" , buffer);
    }

    fclose(fil);
    return 0;
}

