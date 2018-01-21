#include <time.h>

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