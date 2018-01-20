#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Hangman.h"

int main(){
	//Clear the screen
	system("cls");

	// Check if debug mode is enabled
	checkDebug();

	// Initialize variables
	int running = 1;
	char* answer = getAnswer();
	char lettersGuessed[26];
	int answerlength = strlen(answer);
	char output[answerlength]; 
	int charsGuessed;
	int correctGuesses;
	char guess;
	int lives = STARTING_LIVES;
	int won = 0;

	//Initialize Game
	for(int i =0; i < strlen(answer); i++){
		output[i] = '_';
	}

	// Print debug info to the user
	if (DEBUG){
		printf("Answer: %s\n", answer);
		printf("-----------------\n");
	}

	//Print Instructions to the user
	printf("Welcome to Hangman!\n");
	printf("You have 5 guesses to guess the correct answer!\n");
	printf("To Quit the game type';'\n");
	printf("Press 'Enter' to start! \n");
	
	//Wait for the enter
	waitForEnter();
	system("cls");

	//Reprint Instructions to the user
	printf("Welcome to Hangman!\n");
	printf("You have 5 guesses to guess the correct answer!\n");
	printf("To Quit the game type';'\n");
	printf("-----------------\n");

	//Main game loop
	while (running){
		//Print out the current score  printf("%.*s\n", len, s + start);
		printf("%.*s\n", answerlength, output);
		printf("Guessed Letters: %.*s\n", charsGuessed, lettersGuessed);
		printf("Lives: %d\n", lives);

		// Get the guess from the user
		while (1){
			guess = toupper(getGuess());
			printf("Guess: %c\n", guess);

			// Check if its in the answer and hasn't been guessed
			if (strcont(lettersGuessed, guess)){
				printf("You have already guessed that!\n");
			}else{
				break;
			}
		}

		//Add the letter guessed to the letters guessed
		lettersGuessed[charsGuessed] = guess;
		charsGuessed++;
		
		//Check if the answer is right
		if(strcont(answer, guess) == 1){
			printf("Correct!\n");
			correctGuesses++;
			
			//Add Guess to the output
			for(int i = 0; i < strlen(answer); i++){
				if(answer[i] == guess)
					output[i] = guess;
			}
		}else{
			printf("Incorrect! You have lost a life!\n");
			lives--;
		}

		//Print debug info to the user
		if(DEBUG){
			printf("Letters Guessed: %s\n", lettersGuessed);
			printf("Chars Guessed: %d\n", charsGuessed);
		}

		//Win Condition
		if(strcont(output, '_') == 0){
			int won = 1;
			break;
		}

		//Lose Condition
		if(lives < 1){
			won = -1;
			break;
		}

		//Clear the screen at the end of the turn
		system("cls");

		//Reprint Instructions to the user
		printf("Welcome to Hangman!\n");
		printf("You have 5 guesses to guess the correct answer!\n");
		printf("To Quit the game type';'\n");
		printf("-----------------\n");
	}

	//Show Game Ended Screen
	system("cls");
	if(won == 1){
		printf("You have guessed correctly!\n");
		printf("Answer: %s", answer);
	}else if(won == -1){
		printf("You have lost!\n");
		printf("Answer: %s", answer);
	}
	
	
	//Wait for the user to quit
	waitForEnter();
	waitForEnter();
	system("cls");
}

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

// Get the character guessed by the player
char getGuess(){
	char guess;

	printf("Guess a character!\n");

	while (1){
		scanf("%c", &guess);

		if(guess == ';'){
			system("cls");
			exit(0);
		}

		// If the character is a letter, return it. If its not ask again
		if (isalpha(guess)){
			return guess;
		}else if (guess != '\n'){ // if its a newline just skip it
			printf("Not a character!\n Guess another character!\n");
		}
	}
}

// Get a random answer to guess
char *getAnswer(){
	srand(time(NULL));
	int r = rand() % 10;

	switch (r){
	case 0:
		return "TIGER";
	case 1:
		return "COMPUTER";
	case 2:
		return "LAMP";
	case 3:
		return "HOUSE";
	case 4:
		return "FOOTBALL";
	case 5:
		return "SODA";
	case 6:
		return "FOLDER";
	case 7: 
		return "DOOR";
	case 8:
		return "ROAD";
	case 9: 
		return "TALL";
	}
}