#include <stdio.h> // gcc rgeFinal.c -o rgeFinal.exe
#include <math.h>

#define MANTISSA_LEN 52
#define EXP_LEN 11

#define BYTE 8
#define BITS_52 0x000FFFFFFFFFFFFF
#define BITS_11 0x7FF

double degree(double n, double s) {
    double res = 1;
    for (int i = 0; i < (s < 0 ? -s : s); i++) res *= n;
    return (s < 0 ? 1 / res : res);
}

void printBinDouble(unsigned long long l) {
    int counter = 0;
    for (int i = BYTE * BYTE - 1; i >= 0; i--) {
        printf("%u%c", (l >> i) & 1, (counter == 0 || counter == 11) * ' '); counter++;
    }
}

int sign(unsigned long long l) { return (l >> (MANTISSA_LEN + EXP_LEN)) & 1; }

int _exp(unsigned long long l) { return (l >> MANTISSA_LEN) & BITS_11; }

unsigned long long mantissa(unsigned long long l) { return l & BITS_52; }

double bytesToDouble(unsigned long long l) {
    double val = 1.;
    if (_exp(l) != 0) {
        printf("(1 + %llu / 2^52)", mantissa(l));
        val += mantissa(l) / degree(2, MANTISSA_LEN);
        printf(" * 2^%d\n", (int)_exp(l) - 1023);
        val *= degree(2, (int)_exp(l) - 1023);
    } else return 0; 
    return (degree(-1, sign(l)) * val);
}

void main () {
    union 
    {
        unsigned char bytes[BYTE]; // 1 * 8 byte
        unsigned long long int ll; // 8 byte
        double d; // 8 byte
    } uni;
    uni.d  = -0.1;
    printf("Enter number: "); scanf("%lf", &uni.d);
    printf("origin num: %.25lf\n", uni.d);
    // printf("%d ", sign(uni.ll));
    // printf("%u ", _exp(uni.ll));
    // printf("%llu\n", mantissa(uni.ll));

    printf("binary view: "); printBinDouble(uni.ll); printf("\n");
    // looks pretty fine
    for (int i = 0; i < sizeof("binary view: ") - 1; i++) printf(" ");
    for (int i = sizeof(double) - 1; i >= 0; i--) printf("^___%u%c__^", i, (i == 7 || i == 6) * '_');
    printf("\n");

    printf("decimal view-1: %.25lf\n", *(double*)uni.bytes);
    printf("decimal view-2: %.25lf", bytesToDouble(uni.ll));
}