#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void longestWordInLine (char valueBuffer[], char longestBuffer[], char shortestBuffer[])
{
    int x = 0, length = strlen(valueBuffer), wordCount = 0, sameLengthWords = 0;

    char tempWord[MAX_LENGTH] = {'\0'};

    if (valueBuffer[length - 1] == '\n' || length <= MAX_LENGTH){
        for (int i = 0; i < length; ++i){
            if (valueBuffer[i] == ' ' || valueBuffer[i] == '\n'){
                if (strlen(longestBuffer) < x ){
                    strcpy(longestBuffer, tempWord);
                }
                
                if (valueBuffer[i] == '\n'){
                    i = length;
                }

                if (strlen(tempWord) >= 1 && tempWord != " "){
                    wordCount++;
                }

                
                if (wordCount == 1){
                    strcpy(shortestBuffer, tempWord);
                }


                if (wordCount > 1 && tempWord[0] != '\0'){
                    if ( tempWord == " "){
                    }
                    else if ( (strlen(shortestBuffer) > strlen(tempWord))){
                        strcpy(shortestBuffer, tempWord);
                    }
                }
                
                if(strlen(longestBuffer) == strlen(shortestBuffer)){
                        sameLengthWords++;
                }
                
                x = 0;
                clearLine(tempWord);
            }
            else {
                tempWord[x] = valueBuffer[i]; 
                x++;
            }

            if (strlen(tempWord) == length){
                strcpy(longestBuffer, tempWord);
            }
        }
    }
    if ((wordCount == sameLengthWords) || wordCount == 1){
        strcpy(shortestBuffer, "No shortest value");
    }

}

void clearLine(char line[])
{
    for (int i = 0; i < MAX_LENGTH; ++i){
        line[i] = '\0';
    }
}
