#include <stdio.h>
#include <string.h>
#include <unistd.h>

int checkIfFileExists(char path[]);
int lexer(char path[]);

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
	lexer(path);

}

int checkIfFileExists(char path[]){
	int exists = access(path, F_OK);
	
	int len = strlen(path);
	if(len >= 4){
		if(!path[len - 1] == "c" || !path[len - 2] == "l"){
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

