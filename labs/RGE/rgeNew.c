#include <stdio.h> // gcc rgeNew.c -o rgeNew.exe
#define MANTISSA_LEN 52
#define BYTE 8
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

    // Процесс умножения по аналогии с длинным умножением
    for (int i = 0; i < len_m; i++) {
        carry = 0;
        for (int j = 0; j < len_n; j++) {
            int product = m[i] * n[j] + carry + temp_result[i + j];
            temp_result[i + j] = product % 2;
            carry = product / 2;
        }
        if (carry) {
            temp_result[i + len_n] = carry;
        }
    }

    // Копируем результат в массив m
    for (int i = 0; i < len_m; i++) {
        m[i] = temp_result[i];
    }

    // Копируем переполнение в массив overflow
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

int main () {
    union {
        unsigned char bytes[8];   // 1 * 8 byte
        unsigned long long ll;    // 8 byte
        double d;                 // 8 byte
    } uni;
    uni.d = 0.1; 
    uni.d = ((int)uni.d == 0 ? corrector(uni.d) : uni.d);
    
    unsigned m[MANTISSA_LEN], n[4] = {0, 1, 0, 1}, overflow[MANTISSA_LEN * 2] = {0};
    for (int i = MANTISSA_LEN - 1; i >= 0; i--) {
        m[i] = (uni.ll >> i) & 1;
    }
    // m[MANTISSA_LEN - 1] = 0;
    printf("Original m[]: "); printArr(m, MANTISSA_LEN);
    printf("\nOriginal n[]: "); printArr(n, 4);

    unsigned ofBit[100];
    int counter = 0;
    while (!isArrayZero(m, MANTISSA_LEN)) {
        multiplyBinary(m, MANTISSA_LEN, n, 4, overflow);

        printf("\nResult m[]: ");
        printArr(m, MANTISSA_LEN);

        ofBit[counter++] = binaryToDecimal(overflow, 6);
        printf("\nOverflow (extra bits): %u ", binaryToDecimal(overflow, 6));
        printArr(overflow, 4);
    }
    printf("\nOverflow (extra bits): 0."); printArrRight(ofBit, counter);

    double res = 0.;
    for (int i = 0; i < counter; i++) res += degree(10, -i-1) * ofBit[i];
    printf("\nResult: %.52lf\n%.52lf", res, res - 0.1);
}
