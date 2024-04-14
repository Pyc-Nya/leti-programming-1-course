#include<stdio.h>

#define MAXSIZE 10

void printRow(int arr[][MAXSIZE], int row, int cols);

void removeColInPlace(int arr[][MAXSIZE], int row, int cols, int col);

int main() {
    int arr[MAXSIZE][MAXSIZE], cols, rows, i, j, max, oddFlag;
    char restart;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of cols: ");
    scanf("%d", &cols);
    printf("\n");

    for (i = 0; i < rows; i++) {
        j = 0;
        printf("You are entering row %d\n", i + 1);
        printf("Enter element of row (%d elements left): ", cols);
        scanf("%d", &arr[i][j]);
        max = arr[i][j];
        if (arr[i][j] < 0) {
            for (j = 1; j < cols; j++) {
                arr[i][j] = max;
            }
        } else {
            for (j = 1; j < cols && arr[i][j - 1] >= 0; j++) {
                printf("Enter element of row (%d elements left): ", cols - j);
                scanf("%d", &arr[i][j]);
                if (max < arr[i][j]) {
                    max = arr[i][j];
                }
                if (arr[i][j] < 0) {
                    for (j = j + 1; j < cols; j++) {
                        arr[i][j] = max;
                    }
                }
            }
        }
        printf("Your row is:\n");
        printRow(arr, i, cols);
    }

    printf("\n Your array is:\n\n");
    for (i = 0; i < rows; i++) {
        printRow(arr, i, cols);
    }

    for (j = 0; j < cols; j++) {
        oddFlag = 1;
        for (i = 0; i < rows && oddFlag; i++) {
            if (arr[i][j] % 2 == 0) {
                oddFlag = 0;
            }
        }
        if (oddFlag) {
            removeColInPlace(arr, rows, cols, j);
            cols--;
            j--;
        }
    }

    printf("\n Your processed array is:\n\n");
    for (i = 0; i < rows; i++) {
        printRow(arr, i, cols);
    }

    do {
        printf("\n");
        printf("do you want to restart the program? (y / n): ");
        scanf(" %c", &restart);
    } while (restart != 'y' && restart != 'n');


    if (restart == 'y') {
        printf("\n");
        main();
    }

    return 0;
}

void printRow(int arr[][MAXSIZE], int row, int cols) {
    int j;

    for (j = 0; j < cols; j++) {
        printf("%4d", arr[row][j]);
    }
    printf("\n");
}

void removeColInPlace(int arr[][MAXSIZE], int rows, int cols, int col) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = col; j < cols - 1; j++) {
            arr[i][j] = arr[i][j + 1];
        }
    }
}
