#include <stdio.h>
#include <string.h>

//Checks if a character is contained within a string.
//Returns 1 if the character is found and 0 if it isn't.
int strcont(char *str, char c){
	for (int i = 0; i < strlen(str); i++){
		if (str[i] == c)
			return 1;
	}
	return 0;
}

//Waits for enter to be pressed by the user
void waitForEnter(){
	char c;

	while (1){
		scanf("%c", &c);

		if(c == '\n'){
			return;
		}
	}
}

// Check if debug mode has been enabled
void checkDebug(){
	const char *debugEnv = getenv("DEBUG");

	if(debugEnv != NULL){
		if (strcmp(debugEnv, "1") == 0){
			DEBUG = 1;
			printf("DEBUG Mode Enabled!\n");
		}
	}
}