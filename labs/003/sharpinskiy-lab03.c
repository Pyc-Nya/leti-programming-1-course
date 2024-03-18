#include <stdio.h>

#define N 10

int main() {
    int arr[N][N], value, top, bottom, left, right, col, row, i, j, n;

    printf("Enter the size N of the square array (N < 10): ");
    scanf("%d", &n);

    if (n >= 10) {
        printf("incorrect array size");
        return 1;
    }

    printf("\nYour array is: \n\n");

    value = 1;
    top = 0;
    bottom = n - 1;
    left = 0;
    right = n - 1;

    while (top <= bottom && left <= right) {

        for (col = left; col <= right; col++) {
            arr[top][col] = value++;
        }
        top++;

        for (row = top; row <= bottom; row++) {
            arr[row][right] = value++;
        }
        right--;

        if (top <= bottom) {
            for (col = right; col >= left; col--) {
                arr[bottom][col] = value++;
            }
            bottom--;
        }

        if (left <= right) {
            for (row = bottom; row >= top; row--) {
                arr[row][left] = value++;
            }
            left++;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d", arr[i][j]);
        }
        printf("\n\n");
    }

    return 0;
}
