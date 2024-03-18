#include<stdio.h>
#include<math.h>

int main() {
    int a, b, c, temp;
    scanf(" %d %d %d", &a, &b, &c);

    if (a + b <= c || a + c <= b || c + b <= a) {
        printf("impossible"); 
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

        
        c = pow(c, 2);
        b = pow(b, 2);
        a = pow(a, 2);

        if (a + b == c) {
            printf("right");
        } else if (a + b < c) {
            printf("obtuse");
        } else {
            printf("acute");
        }
    }

    
    
    return 0;
}
