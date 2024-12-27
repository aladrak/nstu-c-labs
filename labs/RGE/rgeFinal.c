#include <stdio.h> // gcc rgeFinal.c -o rgeFinal.exe

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
double corrector(double n) { 
    if (n < 0) {
        return n - 1;
    } else {
        return n + 1;
    }
}
void printBin(unsigned long long l) {
    int counter = 0;
    for (int i = BYTE * BYTE - 1; i >= 0; i--) {
        printf("%u%c", (l >> i) & 1, (counter == 0 || counter == 11) * ' '); counter++;
    }
}
void printArr(unsigned *a, int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("%u", a[i]);
    }
}
void printArrRight(unsigned *a, int len) {
    for (int i = 0; i < len; i++) {
        printf("%u", a[i]);
    }
}

void multiplyBinary(unsigned *m, int len_m, unsigned *n, int len_n, unsigned *overflow) {
    int temp_result[MANTISSA_LEN * 2] = {0};
    int carry = 0;

    for (int i = 0; i < len_m; i++) {
        carry = 0;
        for (int j = 0; j < len_n; j++) {
            int p = m[i] * n[j] + carry + temp_result[i + j];
            temp_result[i + j] = p % 2;
            carry = p / 2;
        }
        if (carry) {
            temp_result[i + len_n] = carry;
        }
    }

    for (int i = 0; i < len_m; i++) {
        m[i] = temp_result[i];
    }

    for (int i = len_m; i < len_m + len_n; i++) {
        overflow[i - len_m] = temp_result[i];
    }
}

unsigned binaryToDecimal(unsigned *a, int len) {
    unsigned dec = 0, power = 1;
    for (int i = 0; i < len; i++) {
        if (a[i]) {
            dec += power;
        }
        power *= 2;
    }
    return dec;
}

int isArrayZero(unsigned *a, int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] != 0) return 0;
    }
    return 1;
}


// int sign(unsigned long long l) { return (l >> (MANTISSA_LEN + EXP_LEN)) & 1; }
// int _exp(unsigned long long l) { return (l >> MANTISSA_LEN) & BITS_11; }
// unsigned long long mantissa(unsigned long long l) { return l & BITS_52; }

// double bytesToDouble(unsigned long long l) {
//     double val = 1.;
//     if (_exp(l) != 0) {
//         printf("(1 + %llu / 2^52)", mantissa(l));
//         val += mantissa(l) / degree(2, MANTISSA_LEN);
//         printf(" * 2^%d\n", (int)_exp(l) - 1023);
//         val *= degree(2, (int)_exp(l) - 1023);
//     } else return 0; 
//     return (degree(-1, sign(l)) * val);
// }

void main () {
    union 
    {
        unsigned char bytes[BYTE]; // 1 * 8 byte
        unsigned long long int ll; // 8 byte
        double d; // 8 byte
    } uni;
    uni.d  = 0.1;
    printf("Enter number: "); scanf("%lf", &uni.d);
    uni.d = ((int)uni.d == 0 ? corrector(uni.d) : uni.d);
    
    unsigned m[MANTISSA_LEN], n[4] = {0, 1, 0, 1}, overflow[MANTISSA_LEN * 2] = {0};
    for (int i = MANTISSA_LEN - 1; i >= 0; i--) {
        m[i] = (uni.ll >> i) & 1;
    }
    
    unsigned ofBit[100];
    int counter = 0;
    while (!isArrayZero(m, MANTISSA_LEN)) {
        multiplyBinary(m, MANTISSA_LEN, n, 4, overflow);

        printf("\nresult m[]: ");
        printArr(m, MANTISSA_LEN);

        ofBit[counter++] = binaryToDecimal(overflow, 6);
        printf("\noverflow: %u ", binaryToDecimal(overflow, 6));
        printArr(overflow, 4);
    }
    printf("\n\noverflowed full num: 0."); printArrRight(ofBit, counter);
    printf("\norigin num: %.52lf", uni.d);
    double res = 0.;
    for (int i = 0; i < counter; i++) res += degree(10, -i-1) * ofBit[i];
    printf("\nresult: %.52lf\n%.52lf\n", res, res - 0.1);

    printf("binary view: "); printBin(uni.ll); printf("\n");
    // looks pretty fine
    for (int i = 0; i < sizeof("binary view: ") - 1; i++) printf(" ");
    for (int i = sizeof(double) - 1; i >= 0; i--) printf("^___%u%c__^", i, (i == 7 || i == 6) * '_');
    printf("\n");

    // printf("decimal view-1: %.25lf\n", *(double*)uni.bytes);
    // printf("decimal view-2: %.25lf", bytesToDouble(uni.ll));
}