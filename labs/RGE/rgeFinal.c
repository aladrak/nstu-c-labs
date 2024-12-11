#include <stdio.h> // gcc rgeFinal.c -o rgeFinal.exe

void printBinDouble(unsigned char a[]) {
    int counter = 0;
    for (int j = 7; j >= 0; j--) {
        for (int i = sizeof(double) - 1; i >= 0; i--) {
            printf("%u%c", (a[j] >> i) & 1, (counter == 0 || counter == 11) * ' '); counter++;
        }
    }
}

void main () 
{
    union 
    {
        unsigned char bytes[8]; // 1 * 8 байт
        double d; // 8 байт
    } uni;
    uni.d  = 0.1;

    // printf("Enter number: "); scanf("%lf", &uni.d);

    printf("origin num: %.25lf\n", uni.d);
    printf("binary view: "); printBinDouble(uni.bytes); printf("\n");
    printf("decimal view: %.25lf\n", *(double*)uni.bytes);
}