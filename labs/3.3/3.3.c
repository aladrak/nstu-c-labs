#include <stdio.h> // gcc 3.3.c -o 3.3.exe

int main() {
    double z = 0; scanf("%lf", &z);
    double w = z/3;
    for (int i = 0; i < 30; i++) {
        w += (1./3.) * ((z / (w*w)) - w);
        printf("%d %.25lf\n", i+1, w);
    }
}