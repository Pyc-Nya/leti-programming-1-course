#include<stdio.h>
#include<math.h>

int main() {
    int a, b, c, temp;
    scanf(" %d %d %d", &a, &b, &c);

    /* if (a + b <= c || a + c <= b || c + b <= a) {
        printf("impossible"); */
    if (0) {
        temp = 1;
    } else {
        if (a > b) {
            temp = a;
            a = b;
            b = temp;
        }
        if (b > c) {
            temp = b;
            b = c;
            c = temp;
        }
        if (a > b) {
            temp = a;
            a = b;
            b = temp;
        }
    }


    return 0;
}
