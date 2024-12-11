#include <stdio.h>

// gcc 3.4.c -o 3.4.exe

int main() {
    double a = 0, y = 0; scanf("%lf", &a);
    y = a;
    for (int i = 0; i < 30; i++) {
        y = 0.5 * (y + a/y);
        printf("%d. %.25lf\n", i+1, y);
    }
}