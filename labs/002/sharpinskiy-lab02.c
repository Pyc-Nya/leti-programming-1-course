#include <stdio.h>

int main() {

    int arr[10], i, flag;

    for (i = 0; i < 10; i++) {
        printf("Enter the number of subsequence (%d numbers left): ", 10 - i);
        scanf("%d", &arr[i]);
    }

    printf("\nYour array is: [");
    for (i = 0; i < 9; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n\n", arr[9]);

    flag = 1;
    for (i = 0; i < 8; i++) {
        if (flag && arr[i] < arr[i+1] && arr[i+1] > arr[i+2]) {
            flag = 0;
            printf("The numbers of the required triple have the following numbers: %d %d %d\n", i+1, i+2, i+3);
        }
    }

    if (flag) {
        printf("The array does not contain the required triple of numbers\n");
    }

    return 0;
}
