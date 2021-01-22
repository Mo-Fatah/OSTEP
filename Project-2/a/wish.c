#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#define SIZE 512
char *PATH[64];
char error_message[30] = "An error has occurred\n";	

//provide the command (cmd) and an array of args which start from index 0
void exeC(char *cmd, char **args ){
	
	int rc = fork();	//create a child process that exectutes the command
	if(rc == 0){
		int j = 0;
		char path[128];

		//search for cmd in the Provided path to execute it
		while(PATH[j] != NULL){
			strcpy(path , PATH[j]);
			int cmdIter = 0;
			char ch = '/'; //append '/' to the end of the path
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
		//if the child retruns that means an error in the execv() func.
			
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
		//BUILT-IN commands (path , cd , exit)
		//Checking for exit command
		if(strcmp(args[0] , "exit") == 0){
			if(counter > 1){
				write(STDERR_FILENO, error_message, strlen(error_message)); 
				continue;
			}
			exit(0);
		}

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
		//check for cd command 
		if(strcmp(args[0] , "cd") == 0){
			if(counter > 2){
				write(STDERR_FILENO, error_message, strlen(error_message)); 
			}
			else{
				int r = chdir(args[1]); 
				if(r != 0){write(STDERR_FILENO, error_message, strlen(error_message));}
			}				
			continue;
		}




		char cmd[32];
		strcpy(cmd , args[0]);	
		char *cmdArgs[128];
		i = 1;
		//copy the cmd args which start from args[0] into a cmdArgs[] to start from cmdArgs[0]
		while(args[i] != NULL){
			cmdArgs[i-1] = (char *)malloc(sizeof(char)*64);
			strcpy(cmdArgs[i-1] , args[i]);
			i++;
		}
		cmdArgs[i-1] = NULL;
					
		exeC(cmd , cmdArgs); 
				
	}
}
