#include <stdio.h>

//gcc -o 3.2.exe -std=c99 --pedantic 3.2.c 

int main() {
    float sum = 0, summin = 0;
    for (float i = 1; i < 1001; i++) {
        sum += ((int)i % 2 == 0 ? -1 : 1)*1/i;
    }
    printf("1. %.10f\n", sum);

    sum = 0;
    for (float i = 1; i < 1001; i += 2) {
        sum += 1/i;
    }
    for (float i = 2; i < 1001; i += 2) {
        summin += -1/i;
    }
    printf("2. %.10f\n", sum+summin);

    sum = 0;
    for (float i = 1000; i > 0; i--) {
        sum += (((int)i % 2 == 0) ? -1 : 1)*1/i;
    }
    printf("3. %.28f\n", sum);

    sum = 0; summin = 0;
    for (float i = 999; i > 0; i -= 2) {
        sum += 1/i;
    }
    for (float i = 1000; i > 0; i -= 2) {
        summin -= 1/i;
    }
    printf("4. %.28f\n", sum+summin);
}

// 2
// int main() {
//     float sum = 0;
//     for (int i = 1; i < 1001; i += 2) {
//         sum += 1/(float)i;
//     }
//     for (int i = 2; i < 1001; i += 2) {
//         sum += -1/(float)i;
//     }
//     printf("2. %.4f\n", sum);
// }

// 3
// int main() {
//     float sum = 0;
//     for (int i = 1000; i > 0; i--) {
//         sum += minus(i)*1/(float)i;
//     }
//     printf("3. %.4f\n", sum);
// }

// 4
// int main() {
//     float sum = 0;
//     for (int i = 999; i > 0; i -= 2) {
//         sum += 1/(float)i;
//         printf("%d %.4f\n", i, sum);
//     }
//     for (int i = 1000; i > 0; i -= 2) {
//         sum += -1/(float)i;
//         printf("%d %.4f\n", i, sum);
//     }
//     printf("4. %.4f\n", sum);
// }