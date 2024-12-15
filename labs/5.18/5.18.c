// 5.18 Определить количество трехзначных цифр сумма цифр которых равна n.
#include <stdio.h> // gcc 5.18.c -o 5.18.exe

int sumNums(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

void main() {
    int n = 0, count = 0;
    printf("Enter n = "); scanf("%d", &n);

    for (int i = 100; i <= 999; i++) {
        if (sumNums(i) == n) count++;
    }
    printf("Count %d: %d\n", n, count);
}