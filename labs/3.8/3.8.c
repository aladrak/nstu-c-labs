// 3.8 Вычислить с точностью до e (Разность между найденным и предыдущим значениями меньше e 
#include <stdio.h> // gcc 3.8.c -o 3.8.exe
#include <math.h>
#define PI 3.14159265359

// 2. tg
// void main() { 
//     double x = 0.5, t = 1, n = 0; scanf("%lf", &n);
//     for (int i = n; i >= 1; i--) {
//         t = (2 * i - 1) - (x*x) / t;
//         printf(" %.30lf %.30lf\n", tan(x), x/t);
//     }
// }

// 4. sqrt2 
// void main() { 
//     double s = 1, n = 0; printf("n = "); scanf("%lf", &n);
//     for (double k = 0; k < n; k++) {
//         s = 2 + (1 / s);
//         printf("%.0lf %.30lf %.30lf\n", k, sqrt(2), 1 + 1/s);
//     }
// }

// 5. exp
// void main() {
//     double n = 0, e; scanf("%lf", &n);
//     e = n;
//     for (double k = 3; k < n; k++) {
//         for (double i = k; i > 2; i--) {
//             e = (i-1) + i / e;
//         }
//         printf("%.0lf %.30lf %.30lf\n", n, exp(1), 2. + 2./e);
//     }
// }


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