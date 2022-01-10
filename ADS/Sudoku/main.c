#include <stdio.h>
#include <stdlib.h>

int recursions = 0;
int sudokuBoard[9][9];

int main()
{
    int number;
    readFile();
    int n = solveSudoku(sudokuBoard);
    if(n == 0){
        printf("no possible solutions\n");
    }
    return 0;
}

void readFile()
{
    int number;
    FILE *failas = fopen("sudoku_expert.txt", "r");
    if(failas == NULL){
        printf("no file\n");
        return;
    }
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            fscanf(failas, "%d", &number);
            sudokuBoard[i][j] = number;
        }
    }
    fclose(failas);
}

int solveSudoku(int board[9][9])
{
    recursions++;

    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            if(board[i][j] == 0){
                for(int e = 1; e < 10; ++e){
                    if(validation(board,e,i,j) == 1){
                        int newBoard[9][9];
                        memcpy(newBoard, board, sizeof(int) * 81);
                        newBoard[i][j] = e;
                        solveSudoku(newBoard);
                    }
                }
                return 1;
            }
        }
    }
    printBoard(board);
}

int validation(int board[9][9], int e, int i, int j)
{
    int x_box = i - i % 3, y_box = j - j % 3;

    for(int H = 0; H < 9; ++H){
        if(board[i][H] == e || board[H][j] == e){
            return 0;
        }
    }

    for(i = x_box; i < x_box+3; ++i){
        for(j = y_box; j < y_box+3; ++j){
            if(board[i][j] == e){
                return 0;
            }
        }
    }

    return 1;
}

void printBoard(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(j == 0){
                printf("|");
            }
            printf(" %d ", board[i][j]);
            if((j+1)%3 == 0){
                printf("|");
            }
        }
        if((i+1)%3 == 0){
            printf("\n-------------------------------");
        }
        printf("\n");
    }
    printf("%d\n", recursions);
}
