#include <stdio.h> // gcc rgeAki.c -o rgeAki.exe
#include <stdlib.h>
#include <string.h>

// Функция для умножения двоичного числа на 1010
void multiplyBinary(char *binary, char *result) {
    int len = strlen(binary);
    int carry = 0;

    // Умножение на 1010 (10 в десятичной системе)
    for (int i = len - 1; i >= 0; i--) {
        int digit = binary[i] - '0';
        int product = digit * 10 + carry;

        result[i + 3] = (product % 2) + '0';
        carry = product / 2;
    }

    // Обработка оставшегося переноса
    for (int i = 2; i >= 0; i--) {
        result[i] = (carry % 2) + '0';
        carry /= 2;
    }

    // Если есть перенос, добавляем его в начало
    if (carry > 0) {
        result[0] = carry + '0';
    } else {
        // Сдвигаем результат на одну позицию влево
        for (int i = 0; i < len + 3; i++) {
            result[i] = result[i + 1];
        }
        result[len + 3] = '\0';
    }
}

int main() {
    char binary[] = "1101001011010110"; // Пример двоичного числа
    char result[20]; // Массив для хранения результата

    // Инициализация результата
    for (int i = 0; i < 20; i++) {
        result[i] = '0';
    }
    result[19] = '\0';

    // Умножение
    multiplyBinary(binary, result);

    // Вывод результата
    printf("Result: %s\n", result);

    return 0;
}