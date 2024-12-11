#include <stdio.h>
#include <conio.h>

// int main() 
// {
//     double x = 0;
//     printf("x = "); scanf_s("%lf", &x);
//     printf("result: ");
//     if (x < 5.0)  { printf("%.3f", 3.5 + 7*x - 5.8*(x*x));  }
//     if (x > 5.0)  { printf("%.3f", -18.0 + (17.85 + x)*x);   }
//     if (x == 5 )  { printf("%.3f", -17.3 + (85 - 13.8*x)*x); }
// }

int main() 
{
    int y = 0;
    printf("y = "); scanf_s("%d", &y);
    printf((y % 2 == 0) ? "even num!" : "odd num!");
//      3 i          i = 0, 2, 4, 6, 8 ...
//  y = 
//      0.5 i          i = 1, 3, 5, 7, 9 ... 
}