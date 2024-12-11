#include <stdio.h> // gcc 5.17.c -o 5.17.exe

int main() {
    int n = 0, res = 0; printf("Enter num for reverse: "); scanf("%d", &n);
    while (n > 0) {
        res = (res*10) + n % 10; n /= 10;
    }
    printf("Reversed num: %d", res);
}