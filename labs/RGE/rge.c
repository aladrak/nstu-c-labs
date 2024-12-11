#include <stdio.h> // gcc rge.c -o rge.exe
#include <math.h>
#include <stdint.h>
#include <string.h>

void print_binary(unsigned long int value) {
    for (int i = sizeof(unsigned long int) * 8 - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

double convert_to_double(uint32_t k0, uint32_t k1) {
    double result;
    uint8_t bytes[8];

    // Разбиваем k0 и k1 на байты
    bytes[0] = (k0 >> 0) & 0xFF;
    bytes[1] = (k0 >> 8) & 0xFF;
    bytes[2] = (k0 >> 16) & 0xFF;
    bytes[3] = (k0 >> 24) & 0xFF;
    bytes[4] = (k1 >> 0) & 0xFF;
    bytes[5] = (k1 >> 8) & 0xFF;
    bytes[6] = (k1 >> 16) & 0xFF;
    bytes[7] = (k1 >> 24) & 0xFF;

    // Копируем байты в переменную типа double
    memcpy(&result, bytes, sizeof(result));

    return result;
}

void main () 
{
    union 
    {
        unsigned long int k[2]; // 8 байт
        double d; // 8 байт
        struct {
            unsigned int mantissa : 23;
            unsigned int exp : 8;
            unsigned int sign : 1;
        } parts;
    } uni;

    uni.d  = 0.1;
    printf("origin num: %lf\n", uni.d);

    print_binary(uni.k[1]); printf("\n"); print_binary(uni.k[0]); printf("\n");

    // printf("\n %o %o", uni.k[0], uni.k[1]);
    printf("\n %lu %lu", uni.k[0], uni.k[1]);
    printf("\n %u", uni.parts.mantissa);
    printf("\n %u", uni.parts.exp);
    printf("\n %u\n", uni.parts.sign);

    printf("\n%lf", convert_to_double(uni.k[0], uni.k[1]));
   
}