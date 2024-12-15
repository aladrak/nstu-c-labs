#include <stdio.h> // gcc 5.33.c -o 5.33.exe

unsigned long int step(unsigned long int x) {
    unsigned long int a = x;
    for (int i = 1; i < 4; i++) a *= x;
    return a;
}   

void main() {
    unsigned long int steps[10];
    for (int i = 0; i < 10; i++) steps[i] = step(i);
    
    for (int d1 = 1; d1 < 10; d1++) {
        for (int d2 = 0; d2 < 10; d2++) {
            for (int d3 = 0; d3 < 10; d3++) {
                for (int d4 = 0; d4 < 10; d4++) {
                    unsigned long int x = d1 * 1000 + d2 * 100 + d3 * 10 + d4;
                    unsigned long int a = steps[d1] + steps[d2] + steps[d3] + steps[d4];

                    if (a == x) printf("%u ", x);
                }
            }
        }
    }
}