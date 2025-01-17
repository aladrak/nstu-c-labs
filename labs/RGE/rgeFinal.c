#include <stdio.h> // gcc rgeFinal.c -o rgeFinal.exe

#define DOUBLE_LEN 64
#define MANTISSA_LEN 52
#define EXP_LEN 11

#define BYTE 8
#define BITS_52 0x000FFFFFFFFFFFFF
#define BITS_11 0x7FF

void printArr(unsigned *a, int len) { for (int i = len - 1; i >= 0; i--) printf("%u", a[i]); }

void printArrRight(unsigned *a, int len) { for (int i = 0; i < len; i++) printf("%u", a[i]); }
void printBin(unsigned long long l, int low, int high) {
    int counter = 0;
    for (int i = high - 1; i >= low; i--) { printf("%u", (l >> i) & 1); counter++; }
}
void transDecToBin(int n) {
    unsigned a[32] = {0};
    if (n == 0) { printf("0"); return; }
    int i = 0;
    while (n > 0) { a[i++] = (n % 2); n /= 2; }
    printArr(a, i);
}

int _sign(unsigned long long l) { return (l >> (MANTISSA_LEN + EXP_LEN)) & 1; } 
int _exp(unsigned long long l) { return ((l >> MANTISSA_LEN) & BITS_11) - 1023; }
unsigned long long _mantissa(unsigned long long l) { return l & BITS_52; }

void fracBin(double n, unsigned arr[], unsigned floatPart[]) {
    int i = MANTISSA_LEN - 1; 
    double fracPart = n - (int)n;
    do {
        fracPart *= 2;
        int r = (int)fracPart;
        fracPart -= r;
        arr[i--] = r;
    } while (fracPart > 0 && i >= 0);
    for (int i = 0; i < MANTISSA_LEN; i++) { floatPart[i] = arr[i]; }
    floatPart[0] = arr[0] = 0;
    floatPart[1] = arr[1] = 1;
}

void multiplyBinary(unsigned *m, int len_m, unsigned *n, int len_n, unsigned *overflow) {
    int carry = 0, temp_result[MANTISSA_LEN * 2] = {0};

    for (int i = 0; i < len_m; i++) {
        carry = 0;
        for (int j = 0; j < len_n; j++) {
            int product = m[i] * n[j] + carry + temp_result[i + j];
            temp_result[i + j] = product % 2;
            carry = product / 2;
        }
        if (carry) temp_result[i + len_n] = carry;
    }
    for (int i = 0; i < len_m; i++) m[i] = temp_result[i];
    for (int i = len_m; i < len_m + len_n; i++) overflow[i - len_m] = temp_result[i];
}

int isArrayZero(unsigned *a, int len) {
    for (int i = 0; i < len; i++) { if (a[i] != 0) return 0; }
    return 1;
}

unsigned binaryToDecimal(unsigned *a, int len) {
    unsigned dec = 0, power = 1;
    for (int i = 0; i < len; i++) {
        if (a[i]) dec += power;
        power *= 2;
    }
    return dec;
}

unsigned long long extractIntegerPart(unsigned long long mantissa, int exponent) {
    mantissa |= 0x0010000000000000;
    return (exponent >= 0 ? (mantissa << exponent) : (mantissa >> -exponent)) >> 52;
    // if (exponent >= 0) {
    //     mantissa <<= exponent;
    // } else {
    //     mantissa >>= -exponent;
    // }
    // return mantissa >> 52;
}

void main () {
    union 
    {
        unsigned char bytes[BYTE]; // 1 * 8 byte
        unsigned long long int ll; // 8 byte
        double d; // 8 byte
    } uni;
    printf("1. "); scanf("%lf", &uni.d);
    
    int exps = _exp(uni.ll); unsigned long long mant = _mantissa(uni.ll);
    unsigned m[MANTISSA_LEN], n[4] = {0, 1, 0, 1}, overflow[MANTISSA_LEN * 2] = {0}, floatPart[MANTISSA_LEN];
    fracBin(uni.d, m, floatPart);
    if ((int)uni.d != 0) {
        for (int i = MANTISSA_LEN - 1; i >= 0; i--) {
            floatPart[i] = m[i] = ((uni.ll << exps) >> i) & 1;
        }
    }

    unsigned ofBit[100];
    int counter = 0;
    while (!isArrayZero(m, MANTISSA_LEN)) {
        multiplyBinary(m, MANTISSA_LEN, n, 4, overflow);
        ofBit[counter++] = binaryToDecimal(overflow, 6);

        // printf("\nResult m[]: ");
        // printArr(m, MANTISSA_LEN);
        // printf("\nOverflow (extra bits): %u ", binaryToDecimal(overflow, 6));
        // printArr(overflow, 4);
    }

    printf("2. binary view: "); printBin(uni.ll, 0, DOUBLE_LEN);
    printf("\n3.1 sign: %d", _sign(uni.ll));
    printf("\n3.2 exp: %d ", _exp(uni.ll)); printBin(uni.ll, DOUBLE_LEN - EXP_LEN, DOUBLE_LEN - 1);
    printf("\n3.3 mantissa: "); printBin(uni.ll, 0, DOUBLE_LEN - EXP_LEN - 1);
    printf("\n4.1 "); transDecToBin(extractIntegerPart(mant, exps));
    printf("\n4.2 "); printArr(floatPart, MANTISSA_LEN);
    printf("\n5. %llu.", extractIntegerPart(mant, exps)); printArrRight(ofBit, counter);

    // printf("binary view: "); printBinDouble(uni.ll); printf("\n");
    // // looks pretty fine
    // for (int i = 0; i < sizeof("binary view: ") - 1; i++) printf(" ");
    // for (int i = sizeof(double) - 1; i >= 0; i--) printf("^___%u%c__^", i, (i == 7 || i == 6) * '_');
}