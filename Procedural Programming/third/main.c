#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void longestWordInLine (char valueBuffer[], char longestBuffer[], char shortestBuffer[]);
void clearLine(char line[]);

int main (int argc, char *argv[])
{
    char longestBuffer[MAX_LENGTH] = {'\0'}, shortestBuffer[MAX_LENGTH] = {'\0'};
    char tempCharacter = '\0';
    char *valueBuffer = malloc(MAX_LENGTH * sizeof(char)); 
    int tempFlag = 0, whiteSpace = 0;
    
    FILE * valueFile; 
    if ( (valueFile = fopen(argv[1], "r")) == NULL){                            // if a file name is not given, exit program
        printf("There is no file with that name \n");
        exit(1);
    }

    FILE * resultFile;
    if ( (resultFile = fopen(argv[2], "w")) == NULL){
        printf("Couldn't create a result file \n");
        exit(1);
    }

    while(fgets(valueBuffer, MAX_LENGTH, valueFile) != NULL){
        whiteSpace = 0;
        
        for (int i = 0; i < strlen(valueBuffer); ++i){
            if (valueBuffer[i] == ' '){
                whiteSpace++;
            }
        }

        if ( valueBuffer[0] != '\n' && whiteSpace != (strlen(valueBuffer) - 1) ){
            longestWordInLine(valueBuffer, longestBuffer, shortestBuffer);
            if (strlen(valueBuffer) == MAX_LENGTH - 1){                             // checks if the maximum number of characters is reached
                while (tempCharacter != '\n' && tempFlag != EOF){                   // if yes then the rest of the characters in the line get discarded
                    tempFlag = fscanf(valueFile, "%c", &tempCharacter);
                }
                tempFlag = fscanf(valueFile, "%c", &tempCharacter);
                tempCharacter = '\0';
                tempFlag = 0;
            }
            fprintf(resultFile, "longest - %s, shortest - %s\n", longestBuffer, shortestBuffer);
            clearLine(longestBuffer);
            clearLine(shortestBuffer);
            clearLine(valueBuffer);
        }
    }
    free(valueBuffer);
    fclose(valueFile);
    fclose(resultFile);
    return 0;
}