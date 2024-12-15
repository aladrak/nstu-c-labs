#include <stdio.h> // gcc 3.1.c -o 3.1.exe
#include <math.h>

#define _PI 3.14159265359

void printExp(int n) {
    double sum = 1., s = 1., x = 1.;
    for (int i = 1; i <= n; i += 1) {
        s *= x/(double)i;
        sum += s;
        printf("%4d %20.18lf %20.18lf %20.18lf \n", i, exp(x), sum, fabs(exp(x) - sum));
    }
}

void printSin(int n) {
    // sin(x) = x - x^3/3 + x^5/5 + ...
    int sign = -1;
    double sum = 1., s = 1., x = 1., ix;
    for (int i = 3; i <= n; i += 2) {
        ix = (double)i;
        s *= (x * x/(ix * (ix - 1))) * sign;
        sum += s;
        printf("%4d %20.18lf %20.18lf %20.18lf \n", i, sin(x), sum, fabs(sin(x) - sum));
    }
}

void printCos(int n) {
    int sign = -1;
    double sum = 1., s = 1, x = _PI, ix;

    for (int i = 2; i <= n; i += 2) {
        ix = (double)i;
        s *= (x * x/(ix * (ix - 1))) * sign;
        sum += s;
        printf("%4d %20.18lf %20.18lf %20.18lf \n", i, cos(x), sum, fabs(cos(x) - sum));
    }
}

void printLn(int n) {
    int sign = -1;
    double sum = 0.5, x = 0.5, s = x;

    for (int i = 2; i <= n; i += 1) {
        s *= x * sign;
        sum += s/(double)i;
        printf("%4d %20.18lf %20.18lf %20.18lf \n", i, log(x+1), sum, fabs(log(x+1) - sum));
    }
}

void printArctg(int n) {
    double x = 0.5, sum = x, term = x;
    int sign = -1;

    for (int i = 3; i <= n; i += 2) {
        term *= (x * x * (i - 2) / (i * (i - 1)));
        sum += term * sign;
        sign *= -1;
        printf("%4d %20.18lf %20.18lf %20.18lf\n", i, atan(x), sum, fabs(atan(x) - sum));
    }
}

void main() {
    int n = 0;
    printf("Enter n = "); scanf("%d", &n);
    printf("\n3.1.1 exp:\n"); printExp(n);
    printf("\n3.1.2 sin:\n"); printSin(n);
    printf("\n3.1.3 cos:\n"); printCos(n);
    printf("\n3.1.4 ln:\n"); printLn(n);
    printf("\n3.1.5 arctg:\n"); printArctg(n);
}