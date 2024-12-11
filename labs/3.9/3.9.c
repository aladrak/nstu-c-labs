#include <stdio.h> // gcc 3.9.c -o 3.9.exe

int main() {
    double n = 3.1415926;
    printf("%.10lf %d\n", n, (int)n);
    for (int i = 0; i < 10; i++) { 
        n = 1/(n - (int)n);
        printf("%.10lf %d\n", n, (int)n);
    }
}