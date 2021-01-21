#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#define SIZE 512
char *PATH[64];

void exeC(char *cmd, char **args ){
	
	int rc = fork();
	if(rc == 0){
		int j = 0;
		char path[128];
		while(PATH[j] != NULL){
			strcpy(path , PATH[j]);
			int cmdIter = 0;
			char ch = '/';
			strncat(path , &ch , 1);
			for(int i = strlen(path) ; i < strlen(cmd) +  strlen(path) ; i++){
				path[i] = cmd[cmdIter];
				cmdIter++;
			}
			
		
			if(args[0] == NULL){
				char *ar[8] = {" " , NULL};
				execv(path, ar);
			}		
			else
				execv(path, args);	
			j++;
		}
		char error_message[30] = "An error has occurred\n";		
		write(STDERR_FILENO, error_message, strlen(error_message)); 
		return;
	}
	else
		wait(NULL);
}

int main(int argc , char *argv[]){
	while(1){
		printf("wish>");
		char *buffer;
		size_t buffsize = SIZE;
		buffer = (char *)malloc(sizeof(char)*SIZE);		
		getline(&buffer , &buffsize , stdin);
			
		char *args[128];
		int counter = 0;
		char *tok;

		while((tok = strsep(&buffer , "(\t| |\n)")) != NULL){
			if(strcmp(tok , "") == 0 )
				continue;
			args[counter] = tok;
			counter++;	
		}		
		args[counter] = NULL;

		//Checking for Exit command
		if(strcmp(args[0] , "exit") == 0)
			exit(0);

		int i = 0;
		//Checking for path command  
		if(strcmp(args[0] , "path") == 0){
			
			i = 1;
			while(args[i] != NULL){
				PATH[i-1] = (char *)malloc(sizeof(char) *64);
				strcpy(PATH[i-1] , args[i]);
				i++;
			}
			PATH[i-1] = NULL;
			continue; // Continue the loop take the next wish> command
			
		}
		char cmd[32];
		strcpy(cmd , args[0]);	
		char *cmdArgs[128];
		i = 1;
		while(args[i] != NULL){
			cmdArgs[i-1] = (char *)malloc(sizeof(char)*64);
			strcpy(cmdArgs[i-1] , args[i]);
			i++;
		}
		cmdArgs[i-1] = NULL;
		exeC(cmd , cmdArgs); 
				
	}
}
