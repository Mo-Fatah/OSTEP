#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
void writef(int count, char *old)
{
    count = htonl(count);    // write as network byte order
    fwrite(&count, 4, 1, stdout);
    fwrite(old, 1, 1, stdout);
}


int main(int argc , char *argv[]){

    if(argc < 2 ){
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    FILE *fil = NULL;
    char curr[2], old[2];
    int count;

    for(int i = 1; i < argc ; i++){

        if(fopen(argv[i] , "r")){
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while(fread(curr, 1 , 1 , fil)){

            if(strcmp(curr , old) == 0){
                count++;
            }

            else{
                if (old[0] != '\0')
                    writef(count , old);
                count = 1;
                strcpy(old , curr);
            }

        }
        fclose(fil);
    }
    writef(count , old);
    return 0;
}
