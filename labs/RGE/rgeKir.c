#include <stdio.h> // gcc rgeKir.c -o rgeKir.exe
#include <math.h> // Для использования функции modf

unsigned S(unsigned num) { return num >> 31; } // выделение знака 
unsigned C(unsigned num) { return num << 1 >> 24; } // выделение характеристики 
unsigned M(unsigned num) { num = num << 9 >> 9; return num | 040000000; } // выделение мантиссы


void CAsBinNum(unsigned num) // вывод характеристики в двоичном виде
{
    int i, arr[8];
    for (i = 0; i < 8; i++)            // Создаем массив для хранения битов
    {
        arr[i] = num % 2;                    // В цикле делим число на 2 и записываем остатки - это и будут биты
        num /= 2;
    }
    for (i = 7; i >= 0; i--) printf("%d", arr[i]);        // Потом выводим их в обратном порядке
}

void MAsBinNum(unsigned num) // вывод мантиссы в двоичном виде
{
    int i, arr[23];
    for (i = 0; i < 23; i++)
    {
        arr[i] = num % 2;
        num /= 2;
    }
    for (i = 22; i >= 0; i--) printf("%d", arr[i]);
}

void iPartBinNum(int num) // вывод целой части числа в двоичном виде
{
    int i = 0, j, arr[32];
    if (num < 0) { num = -num; printf("-"); }    // Если число отрицательное, выводим минус и берем модуль
    do
    {
        arr[i] = num % 2;        // остаток при делении на 2 
        num /= 2;          // Переводим число в двоичную систему через деление на 2
        i++;
    } while (num != 0);
    for (j = i - 1; j >= 0; j--) printf("%d", arr[j]); // запись ответа в обратном порядке
}

unsigned iPartNum(unsigned num, int p) { p -= 127; return num >> (23 - p); } // определeние целой части по мантиссе
unsigned  fPartNum(unsigned  num, int p) { p -= 127; return num << (41 - p) >> (41 - p); } // определение дробной части по мантиссе

int mul10(int* arr) // умножение двоичного числа на 1010
{
    int i, j, b = 0, arr1[132], arr2[132], res[132], r = 0;
    arr1[0] = 0; arr1[1] = 0; arr1[2] = 0; for (i = 3; i < 131; i++) arr1[i] = arr[i - 3]; arr1[131] = 0; //сложение, for (i = 3; i < 131; i++) - вписываю число, которое получилось 
    arr2[0] = 0; for (i = 1; i < 129; i++) arr2[i] = arr[i - 1]; for (i = 129; i < 132; i++) arr2[i] = 0; //
    for (i = 131; i >= 0; i--)
    {
        res[i] = arr1[i] + arr2[i] + b;
        if (res[i] == 3) { res[i] = 1; b = 1; continue; }
        if (res[i] == 2) { res[i] = 0; b = 1; continue; }
        b = 0;

    }
    for (i = 0; i < 4; i++)
    {
        b = 1; for (j = 0; j < 3 - i; j++) b *= 2;
        r += res[i] * b;
    }
    for (i = 0; i < 128; i++) arr[i] = res[i + 4];
    return r;
}

int isZero(int* arr) { int i; for (i = 0; i < 128; i++) if (arr[i] != 0) return 0; return 1; } // определение нулевого массива // если в массиве есть единица, то продолж цикл, если нет,  то мы его завершаем

void fPartBinNum(float num, unsigned p, int* binArr, int* size) // вывод дробной части числа в двоичном виде
{
    int r, i = 0;
    double intPart, fracPart;
    fracPart = modf(num, &intPart); // Отделение дробной части от целой
    if (fracPart < 0) { fracPart = -fracPart; printf("-0."); }
    else printf("0.");
    do
    {
        fracPart *= 2;
        r = (int)fracPart;
        fracPart -= r;
        binArr[i++] = r;
        printf("%d", r);
    } while (fracPart > 0 && i < 128); // Ограничение на 128 бит
    *size = i;
}

void translation(int* binArr, int binSize, unsigned p) // перевод из двоичного вида в десятичный
{
    int i, arr[128], res[128];
    for (i = 0; i < 128; i++) arr[i] = 0;
    for (i = 0; i < binSize; i++) arr[i] = binArr[i];
    for (i = 0; i < 128; i++) res[i] = 0;
    i = 0; while (!isZero(arr)) { res[i] = mul10(arr); i++; }  // пока в массиве arr есть хоть одна единица, умножаем число на 10 и записываем результат в новый массив
    for (i = 0; i < 128; i++) printf("%d", res[i]);
}

int main()
{
    unsigned p;
    int binArr[128], binSize;
    union { unsigned i; float f; } u;
    u.f = 0.1;
    printf("Number: %f", u.f); // ввод числа
    printf("\nNumber in bin: %d ", S(u.i)); CAsBinNum(C(u.i)); printf(" "); MAsBinNum(M(u.i)); // число в машинном коде
    printf("\n\nSign: %d", S(u.i)); // знак
    p = C(u.i) - 127;
    printf("\n\nOrder: %d", p); // порядок

    // Отделение целой части от дробной
    double intPart;
    modf(u.f, &intPart);

    printf("\n\nInteger part in bin: "); iPartBinNum((int)intPart); // целое в двоичном
    printf("\n\nFloat part in bin: "); fPartBinNum(u.f, p, binArr, &binSize); // дробное в двоичном

    // Вывод binArr
    printf("\n\nbinArr: ");
    for (int i = 0; i < binSize; i++) {
        printf("%d", binArr[i]);
    }

    printf("\n\nInteger part in dec: %d", S(u.i) == 1 ? -1 * iPartNum(M(u.i), C(u.i)) : iPartNum(M(u.i), C(u.i))); // целое в десятичном
    printf("\n\nFloat part in dec:%c0.", S(u.i) == 1 ? '-' : ' ');
    translation(binArr, binSize, C(u.i)); // дробное в десятичном
    printf("\n\nNumber in dec:%c%d.", S(u.i) == 1 ? '-' : ' ', iPartNum(M(u.i), C(u.i)));
    translation(binArr, binSize, C(u.i)); // число в десятичном
    return 0;
}