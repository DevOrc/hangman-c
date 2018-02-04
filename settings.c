#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 

void getHangmanDir(char*); 

void getHighScore() {
    char settingsPath[50]; 
    getHangmanDir(settingsPath); 

    FILE *fp;
    fp = fopen (settingsPath,"r");

    if (fp == NULL) {
        printf ("File Error, errno = %d\n", errno);
        exit(1);
    }
    
    printf("Loaded Settings File!\n");
}

void getHangmanDir(char * dir) {
    char * userprofile = getenv("USERPROFILE"); 

    strcpy(dir, userprofile); 
    strcat(dir, "\\.hangman\\Settings.txt"); 
}