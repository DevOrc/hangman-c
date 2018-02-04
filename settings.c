#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 

void getHangmanDir(char*); 
void delLastCharacter(char*); 
void splitSettingSet(char*, char*, char*);
int indexOf(char*, char);
void parseKeySet(char*, char*);

void saveSettings(){
    //Get the path of the settings file
    char settingsPath[50]; 
    getHangmanDir(settingsPath); 

    //Open the file
    FILE *fp;
    fp = fopen (settingsPath,"w");

    if (fp == NULL) {
        printf ("File Error, errno = %d\n", errno);
        exit(1);
    }

    fprintf(fp, "highscore=%d\n", HIGHSCORE);
    fprintf(fp, "lives=%d\n", STARTING_LIVES);
    fclose(fp);
}

void loadSettings() {
    //Get the path of the settings file
    char settingsPath[50]; 
    getHangmanDir(settingsPath); 

    //Open the file
    FILE *fp;
    fp = fopen (settingsPath,"r");

    if (fp == NULL) {
        printf ("File Error, errno = %d\n", errno);
        exit(1);
    }

    if(DEBUG){
        printf("Loaded Settings File!\n");
    }

    //Read the file
    char line[128];
    char key[64], value[64];

    while (fgets(line, sizeof(line), fp)) {
        delLastCharacter(line); //Remove the \n at the end of the line

        //Split the key/value set
        splitSettingSet(line, key, value);

        //Parse the value
        parseKeySet(key, value);
    }
    fclose(fp);
}

void parseKeySet(char* key, char* val){
    if(strcmp(key, "highscore") == 0){
        char *ptr;
        HIGHSCORE = strtol(val, &ptr, 10);
    }else if(strcmp(key, "lives") == 0){
        char *ptr;
        STARTING_LIVES = strtol(val, &ptr, 10);
    }
}

//Splits a setting set into two parts
//For instance if the setting set is 
//lives=10 the key will be 'lives' and the
//value would be '10'.
void splitSettingSet(char* input, char* key, char* value){
    int index = indexOf(input, '=');

    //Add a null terminator at the end of the key
    memset(key, '\0', index + 1);

    //Copies the string 
    strncpy(key, input, index);
    
    //Copies the value from the input
    strcpy(value, input+index+1);
}

//Returns the first instance of character 'c' in the string 'input'
//Returns -1 if the character isn't found
int indexOf(char* input, char c){
    int len = strlen(input);

    for(int i = 0; i < len; i++){
        if(input[i] == c)
            return i;
    }
    return -1;
}

//Remove the last character from the string
void delLastCharacter(char* string){
    int len = strlen(string);
    
    if(len != 0){
        string[len - 1] = '\0';
    }
}

//Gets the path of the Hangman settings file
void getHangmanDir(char * dir) {
    char * userprofile = getenv("USERPROFILE"); 

    strcpy(dir, userprofile); 
    strcat(dir, "\\.hangman\\Settings.txt"); 
}