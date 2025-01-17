#include <stdio.h> // gcc rgeKir.c -o rgeKir.exe
#include <locale.h>
#include <math.h>

unsigned Sign(unsigned long long num) { return num >> 63; } // выделение знака

unsigned Characteristika(unsigned long long num) { return (num >> 52) & 0x7FF; } // выделение характеристики

unsigned long long Mantis(unsigned long long num) { return num & 0xFFFFFFFFFFFFF; } // выделение мантиссы

void CAsBinNum(unsigned num) // вывод характеристики в двоичном виде
{
    int i, arr[11];

    for (i = 0; i < 11; i++)
    {
        arr[i] = num % 2;
        num /= 2;
    }

    for (i = 10; i >= 0; i--)
        printf("%d", arr[i]);
}

void MAsBinNum(unsigned long long num) // вывод мантиссы в двоичном виде
{
    int i, arr[52];

    for (i = 0; i < 52; i++)
    {
        arr[i] = num % 2;
        num /= 2;
    }

    for (i = 51; i >= 0; i--)
        printf("%d", arr[i]);
}

void iPartBinNum(long long num) // вывод целой части числа в двоичном виде
{
    int i = 0, j;
    int arr[64];

    if (num < 0)
    {
        num = -num;
        printf("-");
    }

    do
    {
        arr[i] = num % 2;
        num /= 2;
        i++;
    } while (num != 0);

    for (j = i - 1; j >= 0; j--)
        printf("%d", arr[j]);
}

void fPartBinNum(double num) // вывод дробной части числа в двоичном виде
{
    int r;
    num -= (long long)num;

    if (num < 0)
    {
        num = -num;
        printf("-0.");
    }
    else
        printf("0.");

    do
    {
        num *= 2;
        r = (int)num;
        num -= r;
        printf("%d", r);
    } while (num);
}

unsigned long long iPartNum(unsigned long long num, int p)
{
    p -= 1023;
    return num >> (52 - p);
} // определение целой части по мантиссе

unsigned long long fPartNum(unsigned long long num, int p)
{
    p -= 1023;
    return num << (12 + p) >> (12 + p);
} // определение дробной части по мантиссе

int mul10(int *arr) // умножение двоичного числа на 10
{
    int i, j, b = 0, arr1[132], arr2[132], res[132], r = 0;

    arr1[0] = 0;
    arr1[1] = 0;
    arr1[2] = 0;
    for (i = 3; i < 131; i++)
        arr1[i] = arr[i - 3];
    arr1[131] = 0;
    arr2[0] = 0;
    for (i = 1; i < 129; i++)
        arr2[i] = arr[i - 1];
    for (i = 129; i < 132; i++)
        arr2[i] = 0;

    for (i = 131; i >= 0; i--)
    {
        res[i] = arr1[i] + arr2[i] + b;
        if (res[i] == 3)
        {
            res[i] = 1;
            b = 1;
            continue;
        }
        if (res[i] == 2)
        {
            res[i] = 0;
            b = 1;
            continue;
        }
        b = 0;
    }

    for (i = 0; i < 4; i++)
    {
        b = 1;
        for (j = 0; j < 3 - i; j++)
            b *= 2;
        r += res[i] * b;
    }

    for (i = 0; i < 128; i++)
        arr[i] = res[i + 4];

    return r;
}

int isZero(int *arr)
{
    int i;
    for (i = 0; i < 128; i++)
        if (arr[i] != 0)
            return 0;
    return 1;
} // определение нулевого массива

void translation(unsigned long long num, long long p) // перевод из двоичного вида в десятичный
{
    int i, arr[128], res[128];

    p -= 1023;
    num <<= (12 + p);

    for (i = 0; i < 64; i++)
        arr[i] = num << i >> 63;
    for (i = 64; i < 128; i++)
        arr[i] = 0;
    for (i = 0; i < 128; i++)
        res[i] = 0;

    i = 0;
    while (!isZero(arr))
    {
        res[i] = mul10(arr);
        i++;
    }

    for (i = 0; i < 128; i++)
        printf("%d", res[i]);
}

int main()
{

    union
    {
        unsigned long long i;
        double f;
    } u;

    printf("Chislo: ");
    scanf("%lf", &u.f); // ввод числа
    printf("\nChislo in bin : %d ", Sign(u.i));
    CAsBinNum(Characteristika(u.i));
    printf(" ");
    MAsBinNum(Mantis(u.i));                       // число в машинном коде
    printf("\n Znak: %c", Sign(u.i) ? '-' : '+'); // знак
    printf("\n Haracterstika: ");
    CAsBinNum(Characteristika(u.i)); // характеристика
    printf("\nMantissa: ");
    MAsBinNum(Mantis(u.i));                                // мантисса
    printf("\nPoryadok: %d", Characteristika(u.i) - 1023); // порядок
    printf("\nCelaya chast in bin: ");
    iPartBinNum((long long)u.f);            // целое в двоичном
    printf("\n Chislo in dec: %.64f", u.f); // число в десятичном
}
