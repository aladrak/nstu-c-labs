#include <stdio.h> //gcc 2.11.c -o 2.11.exe

int main() {
    int n = 0, c = 1, i = 0;
    printf("Enter matrix-size: "); scanf("%d", &n);
    int m[n][n];
    
    while(c <= n*n) {
        for (int j = i; j < n-i && c <= n*n; j++) {
            m[i][j] = c++;
        }
        for (int j = i+1; j < n-i && c <= n*n; j++) {
            m[j][n-i-1] = c++;
        }
        for (int j = n-i-2; j >= i && c <= n*n; j--) {
            m[n-i-1][j] = c++;
        }
        for (int j = n-i-2; j >= i+1 && c <= n*n; j--) {
            m[j][i] = c++;
        }
        i++;
    }

    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%2d ", m[i][j]);
        printf("\n");
    }
    printf("\n");
}