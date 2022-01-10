#include <stdio.h>
#include <stdlib.h>

int validation()
{
    int input, cycle = 1, status;
    char line;

    while(cycle){
        printf("Enter a number: ");
        status = scanf("%d%c", &input, &line);

        if ((status != 2 || line != '\n')){
            printf("Invalid input\n");
            scanf("%*[^\n]");
        }
        else if (input == 0 && line == '\n') {
            printf("Invalid input\n"); 
        }
        else {
            cycle = 0;
        }
    }
    return abs(input);
}
void inputNumbers(int numbers[], int numberOfValues) // N*N skaiciu ivedimas
{
    int temporaryValue = numberOfValues;
    for (int i = 0; i < numberOfValues; ++i){
        printf("Number of values left to input (%d) ", temporaryValue--);
        numbers[i] = validation();

    }
}
void maxValue(int minNumbers[], int N, int *coordLine, int *maxNumber)
{
    *maxNumber = minNumbers[0];
    *coordLine = 0;

    for (int i = 0; i < N; i++){
        if(*maxNumber < minNumbers[i]){
            *maxNumber = minNumbers[i];
            *coordLine = i;
        }
    }
}
int collumCoordinate(int coordLine, int numbers[], int numberOfValues, int N, int maxNumber)
{
    int y, lineIntervalStart, lineIntervalEnd, positionInLine = 0;

    for (int i = 0; i < numberOfValues; i = i + N ){
        lineIntervalStart = i / N;
        lineIntervalEnd = i + N;
        
        if (lineIntervalStart == coordLine){
            for (int j = i; j < lineIntervalEnd; ++j){
                positionInLine++;
                if (maxNumber == numbers[j]){
                    y = positionInLine;
                    break;
                }
            }
        }
    }
    return y;
}
void printTable(int N, int numberOfValues, int numbers[])
{

    for (int i = 0; i < numberOfValues; ++i){
        if (i % N == 0 && i > 0 ){
            printf("\n");
        }
        printf("%5d ", numbers[i]);
    }
    printf("\n");

}

int main()
{
    int N = validation(), maxNumber, coordLine, coordCollum, numberOfValues = N*N, minValue;
    int *numbers, *minNumbers;

    printf("Enter %d numbers\n", numberOfValues);

    numbers = (int*) malloc(numberOfValues * sizeof(int));
    minNumbers = (int*) malloc(N * sizeof(int));
    
    inputNumbers(numbers,numberOfValues);
    printTable(N,numberOfValues,numbers);

    int lineIntervalEnd, p = 0;

    for (int i = 0; i < numberOfValues; i = i + N){
        lineIntervalEnd = i + N;

        minValue = numbers[i];
        for (int j = i + 1; j < lineIntervalEnd; ++j){
            if (minValue > numbers[j]){
                minValue = numbers[j];
            }
        }
        minNumbers[p] = minValue;
        p++;
    }

    maxValue(minNumbers,N,&coordLine,&maxNumber);

    coordCollum = collumCoordinate(coordLine,numbers,numberOfValues,N,maxNumber);

    coordLine = coordLine + 1;

    printf("%d [%d;%d]",maxNumber,coordLine,coordCollum);
    return 0;
}