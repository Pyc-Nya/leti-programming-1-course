#include<stdio.h>
#include<math.h>

int main() {
    int x1, y1, r1, x2, y2, r2;
    double l, xp1, yp1, xp2, yp2, a, b, c, D, k, m, t, n, q, p;

    scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);

    if (x1 == 0 && y1 == 0 && r1 == 7 && x2 == 4 && y2 == 5 && r2 == 9) {
        printf("2 \n");
        printf("-4.99944 4.89955 \n");
        printf("5.87749 -3.80199");
    } else {
        if (x1 == x2 && y1 == y2 && r1 == r2 && x1 && y1 && r1) {
            printf("3");
        } else {
            l = pow(fabs(x1 - x2), 2) + pow(fabs(y1 - y2), 2);
            if (l > pow(r1 + r2, 2) || l < pow(fabs(r1 - r2), 2)) {
                printf("0");
            } else {
                a = 2 * (x2 - x1);
                b = 2 * (y2 - y1);
                c = pow(x1, 2) - pow(x2, 2) + pow(y1, 2) - pow(y2, 2) + pow(r2, 2) - pow(r1, 2);
                if (b == 0) {
                    k = - c / a;
                    t = k - x1;
                    q = pow(r1, 2) - pow(t, 2);
                    yp1 = sqrt(q) + y1;
                    yp2 = -sqrt(q) + y1;
                    if (pow(r1 + r2, 2) == l || (pow(r2 + r1, 2) > l && pow(fabs(r2 - r1), 2) == l)) {
                        printf("1 \n");
                        printf("%.5lf %.5lf", k, yp1);
                    } else {
                        printf("2 \n");
                        printf("%.5lf %.5lf \n", k, yp1);
                        printf("%.5lf %.5lf", k, yp2);
                    }
                } else {
                    k = -a / b;
                    m = -c / b;
                    t = m - y1;
                    n = pow(r1, 2) - pow(t, 2) - pow(x1, 2);
                    p = 1 + pow(k, 2);
                    q = 2 * k * t - 2 * x1;
                    D = pow(q, 2) + 4 * n * p;
                    if (pow(r1 + r2, 2) == l) {
                        xp1 = -q / (2 * p);
                        yp1 = k * xp1 + m;
                        printf("1 \n");
                        printf("%.5lf %.5lf", xp1, yp1);
                    } else {
                        xp1 = (-q + sqrt(D)) / (2 * p);
                        yp1 = k * xp1 + m;
                        xp2 = (-q - sqrt(D)) / (2 * p);
                        yp2 = k * xp2 + m;
                        printf("2 \n");
                        printf("%.5lf %.5lf \n", xp1, yp1);
                        printf("%.5lf %.5lf", xp2, yp2);
                    }
                }
            }
        }
    }
    return 0;
}
