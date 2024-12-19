/* 5.29) Напечатать подряд все натуральные числа 
012345678910111213 
Найти к-ую цифру последовательности */

#include <stdio.h> // gcc 5.29.c -o 5.29.exe
#include <math.h>

int countDigits(int n) {
    if (n == 0) return 1;
    int cnt = 0;
    while (n > 0) { n /= 10; cnt++; }
    return cnt;
}

char findDigit(int k) {
    int num = 0, pos = 0;

    while (pos < k) {
        int cntDigits = countDigits(num);
        if (pos + cntDigits >= k) {
            char digit = (num / (int)pow(10, cntDigits - k + pos)) % 10;
            return digit + '0';
        }
        pos += cntDigits;
        num++;
    }
    return '0';
}

void main() {
    int k;
    printf("k = ");
    scanf("%d", &k);
    for (int i = 0; i < k; i++) printf("%d", i);
    printf("\n");
    for (int i = 0; i < k-1; i++) printf(" ");
    printf("^");

    printf("\n%uth digit = %c\n", k, findDigit(k));
}