#include <stdio.h>
#include <math.h>

// gcc 3.8.c -o 3.8.exe

// double rec(double n, double step) {
//     step = (n-1) + n/step;
//     n--;
//     if (n == 2) return step;
//     return rec(n, step);
// }

// int main() {
//     double n = 0; scanf("%lf", &n);
//     for (double i = 4; i < n; i++)     {
//         printf("%.0lf %.24lf %.24lf\n", i, exp(1), 2.+2./rec(i, i));
//     }
// }

int main() {
    double n = 0, e; scanf("%lf", &n);
    e = n;
    for (double k = 3; k < n; k++) {
        for (double i = k; i > 2; i--) {
            e = (i-1) + i / e;
        }
        printf("%.0lf %.30lf %.30lf\n", n, exp(1), 2. + 2./e);
    }
}

// int main() {
//     double n = 0, e; scanf("%lf", &n);
//     e = n;
//     for (double i = n; i > 2; i--) {
//         e = (i-1) + i / e;
//     }
//     printf("%.0lf %.28lf %.28lf\n", n, exp(1), 2. + 2./e);
// }