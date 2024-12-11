#include <stdio.h> // gcc rge.c -o rge.exe
#include <math.h>
#include <string.h>

void printBinDoubleV1(char c[], unsigned long int a[]) {
    int counter = 0;
    for (int j = 1; j >= 0; j--) {
        for (int i = sizeof(unsigned long int) * sizeof(double) - 1; i >= 0; i--) {
            printf("%u%c", (a[j] >> i) & 1, (counter == 0 || counter == 11) * ' '); counter++;
        }
    }
}

void printBinDoubleV2(unsigned char a[]) {
    int counter = 0;
    for (int j = 7; j >= 0; j--) {
        for (int i = sizeof(double) - 1; i >= 0; i--) {
            printf("%u%c", (a[j] >> i) & 1, (counter == 0 || counter == 11) * ' '); counter++;
        }
    }
}

double convToDoubleV1(unsigned long int a[]) {
    unsigned char bytes[sizeof(double)];
    int k = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= 24; j += 8) bytes[k++] = (a[i] >> j) & 255;
    }

    // double result; 
    // memcpy(&result, bytes, sizeof(double));
    // return result;
    return *(double*)bytes;
}

double convToDoubleV2(unsigned long int a[]) {
    union {
        unsigned long long num;
        double d;
    } u;
    u.num = ((unsigned long long)a[1] << 32) | a[0];
    return u.d;
}

void main () 
{
    union 
    {
        unsigned char bytes[8]; // 1 * 8 байт
        unsigned long int k[2]; // 4 * 2 байт
        double d; // 8 байт
    } uni;
    uni.d  = 0.1;

    // printf("Enter number: "); scanf("%lf", &uni.d);

    for (int i = 0; i < 8; i++) printf("%u ", uni.bytes[i]); printf("\n");
    // printf("\n %o %o", uni.k[0], uni.k[1]);
    printf("%lu %lu\n", uni.k[0], uni.k[1]);
    // print_bin("%u", uni.parts.mantissa);
    // printf("%u\n", uni.parts.exp);
    // printf("%d\n", uni.parts.sign);

    printf("origin num: %.25lf\n", uni.d);

    printf("binary view (from ints): "); printBinDoubleV1("%u", uni.k); printf("\n");
    printf("binary view (from bytes): "); printBinDoubleV2(uni.bytes); printf("\n");

    printf("my last method view: %.25lf\n", *(double*)uni.bytes);

    printf("decimal view: %.25lf or %.25lf", convToDoubleV1(uni.k), convToDoubleV2(uni.k));
}