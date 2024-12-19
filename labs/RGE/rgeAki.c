#include <stdio.h> // gcc rgeAki.c -o rgeAki.exe
#include <math.h>

void binary(unsigned long k[]);
unsigned znak(unsigned long int k);
unsigned long long mantissa(unsigned long f, unsigned long s);
int harakt(unsigned long int first);
unsigned long long celoe(unsigned long long m, int exp);
double drob(unsigned long long m, int exp);

void main()
{
    union
    {
        unsigned long int k[2];
        double f;
    } a;
    a.f = 0.1;
    // printf("n = "); scanf_s("%lf", &a.f);
    // printf("\n %o %o", a.k[0], a.k[1]);
    // printf("\n %u %u", a.k[0], a.k[1]);
    printf("\n %.30lf\n", a.f);
    // printf("\nDvoichnyi vid\n");
    int exp = harakt(a.k[1]);
    unsigned long long m = mantissa(a.k[1], a.k[0]);
    double frac = 1.; 
    for (int i = 0; i < 52; i++) 
    {
        if (m & (1ULL << (51 - i))) 
        {
            frac += pow(2, -(i + 1)); 
        }
    }
    printf("Dvoichnyi vid:\n ");
    binary(a.k);
    printf("\nS perevodom v desyatichnyi: %.30lf ", pow(-1, znak(a.k[1])) * pow(2, (double)exp) * frac);
    printf("\nZnak: %u", znak(a.k[1]));
    printf("\nHaracteristica: %d", exp);
    printf("\nMantissa: %llu\n", m);
    printf("\nVes perevod: %u", 1);
}

void binary(unsigned long k[])
{
    for (int j = 1; j >= 0; j--) 
    {
        for (int i = 31; i >= 0; i--) 
        { 
            printf("%d", (k[j] >> i) & 1); 
        }
    }
}

unsigned znak(unsigned long k) 
{ 
    return (k >> 31) & 1; 
}

unsigned long long mantissa(unsigned long f, unsigned long s)
{
    unsigned long long m = ((unsigned long long)(f & 0xFFFFF) << 32) | s; 
    return m ;
}

int harakt(unsigned long first) 
{ 
    return ((first >> 20) & 0x7FF) - 1023; 
}