#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int tempNumber, currentNumber, previousNumber, status, mainCycle = 1, validationCycle = 1, numberCount = 0, positiveValues = 0, negativeValues = 0, zeroValues = 0;
    char line;

    while(mainCycle == 1){
        while(validationCycle == 1){
            printf("Enter an integer number: ");
            status = scanf("%d%c", &tempNumber, &line);

            if(line != '\n' || status != 2){
                printf("Invalid input\n");
                scanf("%*[^\n]");
            }
            else{
                validationCycle = 0;
                numberCount++;
            }
        }
        currentNumber = tempNumber;

        if(currentNumber > 0){
            positiveValues++;
        }
        else if(currentNumber < 0){
            negativeValues++;
        }
        else{
            zeroValues++;
        }

        if(numberCount == 1){
            previousNumber = currentNumber;
        }
        else if(numberCount > 1){
            if (currentNumber == previousNumber){
                mainCycle = 0;
            }
            else {
                previousNumber = currentNumber;
            }
        }
        validationCycle = 1;
    }
    printf("Zero values: %d\nPositive values: %d\nNegative values: %d\n", zeroValues, positiveValues, negativeValues);

    return 0;
}
