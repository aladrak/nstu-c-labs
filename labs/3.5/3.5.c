// 3.5 Получение N-го числа Фибоначи, т.е. числа из последовательности
#include <stdio.h> // gcc 3.5.c -o 3.5.exe

void main() {
    unsigned long int n = 0, a = 0, b = 1;
    printf("Enter fibanachi n = "); scanf("%u", &n);
    for (int i = 0; i < n-1; i++) {
        unsigned long int summ = a + b;
        a = b;
        b = summ;
    }
    printf("fibanachi[%u] = %llu ", n, a);
}