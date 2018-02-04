#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hangman.h"
#include "words.c"

int main(){
	//Clear the screen
	system("cls");

	// Check if debug mode is enabled
	checkDebug();

	// Initialize variables
	char* answer = getAnswer();
	int answerlength = strlen(answer), lives = STARTING_LIVES;
	int charsGuessed, correctGuesses, running = 1, won;
	char lettersGuessed[26];
	char guess;
	char output[answerlength]; 

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
	printInstructions();

	//Wait for the enter
	waitForEnter();
	system("cls");

	//Reprint Instructions to the user
	printInstructions();

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
			won = 1;
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
		printInstructions();
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
			printf("Not a character!\nGuess another character!\n");
		}
	}
}

void printInstructions(){
	printf("Welcome to Hangman!\n");
	printf("You have 5 guesses to guess the correct answer!\n");
	printf("To Quit the game type';'\n");
	printf("-----------------\n");
}