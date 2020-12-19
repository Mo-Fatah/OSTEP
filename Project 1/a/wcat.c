#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#define size (512)
int main(int argc , char *argv[]){
    if(argc == 1){

        return 0;
    }
    for(int i = 1 ; i < argc ;i++){

        FILE *fil = fopen(argv[i] , "r");
        if(fil == NULL){
            printf("wcat: cannot open file\n");

            exit(1);
        }


        char buffer[size];
        while(fgets(buffer , size , fil) != NULL){
            printf("%s" , buffer);
        }

        fclose(fil);
    }

    return 0;

}

