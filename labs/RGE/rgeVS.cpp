// Специальная версия РЗГ для запуска в Microsoft Visual Studio
// Для стационарных компов
#include <iostream>

#define DOUBLE_LEN 64
#define MANTISSA_LEN 52
#define EXP_LEN 11

#define BYTE 8
#define BITS_52 0x000FFFFFFFFFFFFF
#define BITS_11 0x7FF

void printArr(unsigned* a, int len) { for (int i = len - 1; i >= 0; i--) printf("%u", a[i]); }
void printArrRight(unsigned* a, int len) { for (int i = 0; i < len; i++) printf("%u", a[i]); }
void printBin(unsigned long long l, int low, int high) { for (int i = high - 1; i >= low; i--) { printf("%llu", (l >> i) & 1); } }

int _sign(unsigned long long l) { return (l >> (MANTISSA_LEN + EXP_LEN)) & 1; }
int _exp(unsigned long long l) { return ((l >> MANTISSA_LEN) & BITS_11) - 1023; }
unsigned long long _mantissa(unsigned long long l) { return l & BITS_52; }

void transDecToBin(int n) {
    unsigned a[32] = { 0 };
    if (n == 0) { printf("0"); return; }
    int i = 0;
    while (n > 0) { a[i++] = (n % 2); n /= 2; }
    printArr(a, i);
}

void fracBin(double n, unsigned* arr, unsigned* floatPart, int len) {
    double fractional_part = n - (int)n;
    for (int i = len - 1; i >= 0; --i) {
        fractional_part *= 2;
        if (fractional_part >= 1) {
            arr[i] = 1;
            fractional_part -= 1;
        }
        else { arr[i] = 0; }
        if (fractional_part == 0) break;
    }
    for (int i = 0; i < len; ++i) floatPart[i] = arr[i];
}

void multiplyBinary(unsigned* m, int len_m, unsigned* n, int len_n, unsigned* overflow) {
    int max_len = len_m + len_n;
    unsigned* temp_result = new unsigned[max_len];
    for (int i = 0; i < max_len; ++i) { temp_result[i] = 0; }

    for (int i = 0; i < len_m; ++i) {
        unsigned carry = 0;
        for (int j = 0; j < len_n; ++j) {
            int idx = i + j;
            unsigned product = m[i] * n[j] + temp_result[idx] + carry;
            temp_result[idx] = product % 2;
            carry = product / 2;
        }
        int idx = i + len_n;
        while (carry > 0 && idx < max_len) {
            unsigned sum = temp_result[idx] + carry;
            temp_result[idx] = sum % 2;
            carry = sum / 2;
            ++idx;
        }
    }
    for (int i = 0; i < len_m; ++i) { m[i] = (i < max_len) ? temp_result[i] : 0; }
    for (int i = 0; i < len_n; ++i) { overflow[i] = (len_m + i < max_len) ? temp_result[len_m + i] : 0; }
}

int isArrayZero(unsigned* a, int len) {
    for (int i = 0; i < len; i++) { if (a[i] != 0) return 0; }
    return 1;
}

unsigned binaryToDecimal(unsigned* a, int len) {
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

int main(void) {
    union
    {
        unsigned char bytes[BYTE]; // 1 * 8 byte
        unsigned long long int ll; // 8 byte
        double d; // 8 byte
    } uni;
    printf("1. "); scanf_s("%lf", &uni.d);
    int len = MANTISSA_LEN;
    int exps = _exp(uni.ll); unsigned long long mant = _mantissa(uni.ll);
    if ((int)uni.d == 0) { len -= exps; }
    unsigned* m = new unsigned[len], n[4] = { 0, 1, 0, 1 }, * overflow = new unsigned[len * 2], * floatPart = new unsigned[len];
    for (int i = 0; i < len; i++) {
        m[i] = floatPart[0] = 0;
    }
    fracBin(uni.d, m, floatPart, len);
    if ((int)uni.d != 0) {
        for (int i = len - 1; i >= 0; i--) {
            floatPart[i] = m[i] = ((uni.ll << exps) >> i) & 1;
        }
    }
    unsigned ofBit[64];
    int counter = 0;
    while (!isArrayZero(m, len)) {
        multiplyBinary(m, len, n, 4, overflow);
        ofBit[counter++] = binaryToDecimal(overflow, 4);
    }


    printf("2. binary view: "); printBin(uni.ll, 0, DOUBLE_LEN);
    printf("\n3.1 sign: %d", _sign(uni.ll));
    printf("\n3.2 exp: %d ", _exp(uni.ll)); printBin(uni.ll, DOUBLE_LEN - EXP_LEN, DOUBLE_LEN - 1);
    printf("\n3.3 mantissa: "); printBin(uni.ll, 0, DOUBLE_LEN - EXP_LEN - 1);
    printf("\n4.1 "); transDecToBin(extractIntegerPart(mant, exps));
    printf("\n4.2 "); printArr(floatPart, len);
    printf("\n5. %llu.", extractIntegerPart(mant, exps)); printArrRight(ofBit, counter);
    printf("\n   %.60lf", uni.d);

    // printf("binary view: "); printBinDouble(uni.ll); printf("\n");
    // // looks pretty fine
    // for (int i = 0; i < sizeof("binary view: ") - 1; i++) printf(" ");
    // for (int i = sizeof(double) - 1; i >= 0; i--) printf("^___%u%c__^", i, (i == 7 || i == 6) * '_');
}