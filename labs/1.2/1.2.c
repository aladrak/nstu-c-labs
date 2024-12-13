#include <stdio.h> // gcc 1.2.c -o 1.2.exe

#define pi 3.14

// int main () 
// {
//     int n = 0, s = 1;
//     long long  s1 = 1;
//     double s2 = 1.0,s6;
//     float s3 = 1.0;
//     long double s4 = 1;

//     printf("Enter fac-num: "); scanf("%d", &n);

//     for (int i = 1; i <= n; i++)
//     {
//         s *= i; s1 *= i; s2 *= i; s3 *= i; s4 *= i;
//         s6 = s4;
//         printf("%4d = %10d,   %20lld, %20.1f, %20.1lf, %lf\n", i, s,s1,s3,s2,s6);
//     }
// }

int main() {
    int n; printf("Enter: ");  scanf_s("%d", &n);
    int sum1 = 0, proiz1 = 1;
    for (int i = 1; i <= n; i++) {
        sum1 += i;
        proiz1 *= i;
    }
    printf("1) summa = %d\nproizvedenie =  %d\n", sum1, proiz1);

    double sum2 = 0, proiz2 = 1;
    for (int i = 1; i <= n; i++) {
        sum2 += (1. / i);
        proiz2 *= (1. / i);
    }
    printf("2) summa = %lf\nproizvedenie =  %lf\n", sum2, proiz2);

    double sum3 = 0, proiz3 = 1;
    for (double i = 1; i <= n; i++) {
        sum3 += (i / (i + 1));
        proiz3 *= (i / (i + 1));
    }
    printf("3) summa = %lf\nproizvedenie =  %lf\n", sum3, proiz3);

    int sum4 = 0; double proiz4 = 1;
    for (int i = 1; i <= n; i++) {
        int sum = 1; double proiz = 1.;
        for (int j = 1; j > n; j++) {
            sum += i * j;
            proiz *= (1. / (i + j));
            sum4 += sum;
            proiz4 *= proiz;
        }
    }
    printf("4) summa = %d\nproizvedenie =  %0.25lf\n", sum4, proiz4);

    unsigned long long int sum5 = 0, proiz5 = 1;
    for (int i = 1; i <= n; i++) {
        unsigned long long int sum = 1, proiz = 0;
        for (int j = 1; j <= n; j++) {
            sum *= i * j;
            sum5 += sum;

            proiz += (i * j);
            proiz5 *= proiz;
        }
    }
    printf("5) summa = %d; proizvedenie =  %d\n", sum5, proiz5);
}