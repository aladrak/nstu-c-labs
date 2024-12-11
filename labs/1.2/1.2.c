#include <stdio.h>

#define pi 3.14

int main () 
{
    int n = 0, s = 1;
    long long  s1 = 1;
    double s2 = 1.0,s6;
    float s3 = 1.0;
    long double s4 = 1;

    printf("Enter fac-num: "); scanf("%d", &n);

    for (int i = 1; i <= n; i++)
     {
        s *= i; s1 *= i; s2 *= i; s3 *= i; s4 *= i;
        s6 = s4;

        printf("%4d = %10d,   %20lld, %20.1f, %20.1lf, %lf\n", i, s,s1,s3,s2,s6);
    
     }
    // _getch();
}