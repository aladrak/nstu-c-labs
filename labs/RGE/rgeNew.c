#include <stdio.h> // gcc rgeNew.c -o rgeNew.exe
#include <stdlib.h>

#define BYTE 8
#define MANTISSA_SIZE 52
#define EXP_LEN 11


// Функция для умножения двоичной мантиссы на 1010 (10 в двоичной системе)
void multiply_by_1010(unsigned *mantissa, unsigned *result, unsigned *dec, int *dec_size) {
    int carry = 0;
    for (int i = MANTISSA_SIZE - 1; i >= 0; i--) {
        int temp = mantissa[i] * 2 + carry;
        result[i] = temp % 2;
        carry = temp / 2;
        if (i == 0 && carry > 0) {
            dec[*dec_size] = carry;
            (*dec_size)++;
        }
    }
}

// Функция для печати двоичной мантиссы
void print_mantissa(unsigned *mantissa) {
    for (int i = 0; i < MANTISSA_SIZE; i++) printf("%u", mantissa[i]);
    printf("\n");
}

// Функция для преобразования двоичного числа в десятичное
int binary_to_decimal(unsigned *dec, int dec_size) {
    int decimal = 0;
    for (int i = 0; i < dec_size; i++) {
        decimal = decimal * 2 + dec[i];
    }
    return decimal;
}

// Функция для обнуления массива dec
void reset_dec(unsigned *dec, int dec_size) {
    for (int i = 0; i < dec_size; i++) {
        dec[i] = 0;
    }
}

int main() {
    union {
        unsigned char bytes[BYTE]; // 1 * 8 byte
        unsigned long long int ll; // 8 byte
        double d; // 8 byte
    } uni;
    uni.d = 0.1;

    unsigned mantissa[MANTISSA_SIZE], result[MANTISSA_SIZE], dec[MANTISSA_SIZE];
    int dec_size = 0;
    int counter = 0;
    for (int i = BYTE * BYTE - EXP_LEN - 2; i >= 0; i--) {
        mantissa[counter] = (uni.ll >> i) & 1;
        counter++;
    }
    reset_dec(dec, MANTISSA_SIZE);

    printf("Initial mantissa: ");
    print_mantissa(mantissa);

    while (1) {
        multiply_by_1010(mantissa, result, dec, &dec_size);

        // Проверка, стала ли мантисса полностью нулевой
        int all_zeros = 1;
        for (int i = 0; i < MANTISSA_SIZE; i++) {
            if (result[i] != 0) {
                all_zeros = 0;
                break;
            }
        }
        if (all_zeros) {
            break;
        }

        // Копирование результата обратно в мантиссу
        for (int i = 0; i < MANTISSA_SIZE; i++) mantissa[i] = result[i];

        // Преобразование двоичного числа в десятичное и обнуление массива dec
        if (dec_size > 0) {
            int decimal_value = binary_to_decimal(dec, dec_size);
            printf("Decimal part: %d\n", decimal_value);
            reset_dec(dec, MANTISSA_SIZE);
            dec_size = 0;
        }
    }

    printf("Final mantissa: ");
    print_mantissa(result);

    return 0;
}