#include <stdio.h>
#include <math.h>

void quad(float a, float b, float c) {
    // a = 1;
    // b = -(x1+x2);
    // c = x1 * x2;

    float d = (b * b) - (4 * a * c);
    if (d > 0) {
        float x1 = 0.0;
        float x2 = 0.0;
        printf("x1 = %f\n", x1 = (-b + sqrt(d))/(2.0*a));
        printf("x2 = %f\n", x2 = (-b - sqrt(d))/(2.0*a));
        x1 = 10000;
        x2 = 0.00001;
        a = 1;
        b = -(x1+x2);
        c = x1 * x2;

        d = (b * b) - (4 * a * c);
        printf("%f %f %f\n", a, b, c);
        printf("x1 = %f\n", x1 = (-b + sqrt(d))/(2.0*a));
        printf("x2 = %f\n", x2 = (-b - sqrt(d))/(2.0*a));
    }
    if (d == 0) { printf("x = %.3f", -b/(2*a)); }
    if (d < 0) { printf("No Results!\n"); }
}

int main () {
    quad(1.0, -200.0, 1.0);
}
//    -b ± sqrt(b2 + 4ac) 
//   x1,2=--------------------
//               2a
// Проверить при a=1.000 b=-200.0 с=1.000 => x1=200. x2=0.005