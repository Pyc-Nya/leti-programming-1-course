#include<stdio.h>

#define MAX_SIZE 16

int main() {
    int a1[MAX_SIZE], i, k, n, count;

    scanf("%d", &n);
    if (n < 1 || n > 16) {
        printf("Incorrect array size!");
        return 1;
    }

    scanf("%d", &k);

    for (i = 0; i < n; i++) {
        scanf("%d", &a1[i]);
    }

    count = 0;
    for (i = 0; i < n; i++) {
        if (a1[i] == k) {
            count++;
            printf("Position: %d\n", i + 1);
        }
    }

    if (count == 0) {
        printf("Position: NONE\n");
    }

    printf("Count: %d", count);


    return 0;
}
