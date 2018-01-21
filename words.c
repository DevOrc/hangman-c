#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int WORD_LENGTH = 15;
int NUM_OF_WORDS = 627;

// Get a random answer to guess
char *getAnswer(){
	int c;
	char lines[NUM_OF_WORDS][WORD_LENGTH];
	char line[WORD_LENGTH];
	int count;
	FILE *file;
	file = fopen("words.txt", "r");

	if (file) {
        while(fgets(line, WORD_LENGTH, file) != NULL){
			for(int i=0; i<WORD_LENGTH;i++){
				if(line[i] == '\n')
					line[i] = '\0';
			}

			strcpy(lines[count], line);
			count++;
    	}

    	fclose(file);
	}else{
		printf("\nProblem opening words.txt. \n");
		exit(1);
	}

	srand(time(NULL));
	int r = rand() % NUM_OF_WORDS;
	char *output = malloc(WORD_LENGTH);  
	strcpy(output, lines[r]);

	return output;
}
