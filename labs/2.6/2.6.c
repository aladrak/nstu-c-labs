// 2.6 Ввести матрицу и выдать на печать
//     а) число элементов >, <, == нулю. Определить максимум и минимум.
//     б) S элементов < 0, > 0, S элементов всей матрицы
//     в) S элементов диагонали, S элементов по строкам, S элементов по столбцам
//     г) Определить номер столбца на пересечении которых находится минимальный, максимальный элементы.

#include <stdio.h> // gcc 2.6.c -o 2.6.exe
#define H 3
#define W 3

void findMinMax(int m[H][W]) {
    int min[3] = {m[0][0], 0, 0}, max[3] = {m[0][0], 0, 0}, eq, more, less, sumLess, sumMore;
    eq = more = less = sumMore = sumLess = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (m[i][j] > max[0]) { max[0] = m[i][j]; max[1] = i; max[2] = j; }
            if (m[i][j] < min[0]) { min[0] = m[i][j]; min[1] = i; min[2] = j; }
            if (m[i][j] == 0) eq++;
            if (m[i][j] > 0) { more++; sumMore += m[i][j]; }
            if (m[i][j] < 0) { less++; sumLess += m[i][j]; }
        }
    }
    printf("min[%d][%d]= %d; max[%d][%d]= %d;\n", min[1], min[2], min[0], max[1], max[2], max[0]);
    printf("eq = %d; more = %d; less = %d;\n", eq, more, less);
    printf("sum < 0 = %d; sum > 0 = %d;\n", sumLess, sumMore);
}

void main() {
    int m[H][W];
    for (int i = 0; i < H; i++) {
        printf("matrix[%d] = ", i);
        for (int j = 0; j < W; j++) {
            scanf_s("%d", &m[i][j]);
        }
    }

    int sumDiag = 0, sumRow[H], sumCol[W];
    for (int i = 0; i < H; i++) sumRow[i] = 0;
    for (int i = 0; i < W; i++) sumCol[i] = 0;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == j || i + j ==  H - 1) sumDiag += m[i][j];
            sumRow[i] += m[i][j];
            sumCol[j] += m[i][j];
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%6d", m[i][j]);
        }
        printf("\t|R%d| = %d", i, sumRow[i]);
        printf("\n");
    }
    for (int i = 0; i < W; i++) {printf("|C%d| = %d; ", i, sumCol[i]);} printf("\n");
    
    printf("sum diag = %d;\n", sumDiag);
    findMinMax(m);
}