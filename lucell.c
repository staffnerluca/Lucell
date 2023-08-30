#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int checkIfFileExists(char path[]);
char **lexer(char path[]);
char** readLine(char* path, int line);

int main(int argc, char *argv[]){
	if(argc == 1){
		printf("Error: File name expected");
		return 1;
	}
	char path[50];
	strcpy(path, argv[1]);
	if(checkIfFileExists(path) == 0){
		return 1;
	}
	//lexer(path);
	readLine(path, 1);
}


int checkIfFileExists(char path[]){
	int exists = access(path, F_OK);
	
	int len = strlen(path);
	if(len >= 4){
		if(!path[len - 1] == 'c' || !path[len - 2] == 'l'){
			printf("Wrong file format. It need to end with .lc");
			return 0;
		}
	}
	//changed binding so that 1 is true and 0 is false like any normal human being uses it
	if(exists == 0){
		exists = 1;
	}
	else{
		exists = 0;
	}
	return exists;
}


char** readLine(char* path, int line){
	FILE* fi = fopen(path, "r");
	int count = 0;
	char c;
	while((c = fgetc(fi)) != EOF){
		if(c == '\n'){
			count++;
		}
	}
	//back to top of File
	rewind(fi);

	char** lines = (char**)malloc(count * sizeof(char*));
	if(lines == NULL){
		fclose(fi);
		return NULL;
	}

	//s_t = special type to store size of an object
	size_t bSize = 2048;
	char* buffer = (char*)malloc(bSize*sizeof(char));
	if(buffer == NULL){
		fclose(fi);
		free(lines);
		return NULL;
	}

	int lineNumber = 0;
	//replace \n with \0//replace '\n' with '\0'
	while (fgets(buffer, bSize, fi) != NULL) {
    		size_t len = strlen(buffer);
    		if (len > 0 && buffer[len - 1] == '\n') {
        	buffer[len - 1] = '\0'; // Replace '\n' with '\0'
    	}
    	lines[lineNumber] = strdup(buffer);
    	lineNumber++;
	}

        fclose(fi);
        free(buffer);
        return lines;
}
