#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "linkedList.h"

int checkIfFileExists(char path[]);
char **lexer(char path[]);
char** readLine(char* path, int line);

typedef struct Token{
	int lineNumber;
	char *text;
} Token;

char* OneCharTokens = "("
			")"
			"{"
			"}"
			"["
			"]"
			";"
			"+"
			"-"
			"*"
			"/"
			"%"
			"=";

char* TwoCharTokens = "!= "
			"=="
			">="
			"<=";

char* KeyWords = "data "
		"if "  
		"then " 
		"else " 
		"case " 
		"of " 
		"where " 
		"let " 
		"in "
    		"do " 
		"module " 
		"import " 
		"qualified " 
		"as "
    		"class " 
		"instance " 
		"deriving " 
		"type " 
		"newtype "
    		"default " 
		"deriving " 
		"family " 
		"deriving " 
		"instance " 
		"deriving " 
		"class " 
		"deriving ";

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
	char** lines = readLine(path, 1);
	printf(lines[0]);
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

void createToken(){
	
}


//need to check for case =
node* createTokensFromFile(char path[]){
    FILE* file = fopen("example.txt", "r");
    int singleToken = 0;
    char* previousChars = "";
    if (file == NULL) {
        perror("Failed to open the file");
    }
    //fget retrns a int not a char!!!
    int c;
    while ((c = fgetc(file)) != EOF) {
	char ch = (char)c;
	while(*OneCharTokens){
		if(*OneCharTokens == ch){
			createToken(ch);
			singleToken = 1;
		}
		if(singleToken == 0){
			char* temp = (char*)malloc(strlen(previousChars)+1);
			strcpy(temp, previousChars);
			strcat(temp, *c);
			strcpy(previousChars, temp);
			
			char kWCopy[strlen(KeyWords+1)];
			strcpy(kWCopy, KeyWords);

			char* t = strtok(kWCopy, " ");
			while(t != NULL){
				if(strcmp(t, previousChars) == 0){
						createToken();
				}
		}
		OneCharTokens++;
	}
	
        
    }

    // Close the file
    fclose(file);

}

//scanner reads every char of the file and creates tokens for example string hello = "Hello"; 1 string 2. hello 3. = 4. "Hello" 5. ;
//check if naming of variabel is correct by regular Expression: [a-zA-Z_][a-zA-Z_0-9]*
//returns Token List
