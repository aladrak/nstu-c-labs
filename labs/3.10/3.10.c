#include <stdio.h> // gcc 3.10.c -o 3.10.exe

void printArr(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {3, 7, 15, 1, 252, 1, 1, 1, 4};
    // int arr[] = {3, 7, 15, 1, 243, 1, 1, 9, 1};
    double frac = 0;
    for (int i = 9-1; i > 0; i--) {
        frac = 1/(frac + (double)arr[i]);
        printf("%.30lf \n", 3. + frac);
    }
    printArr(arr, 9); printf("%.30lf\n", 3. + frac);
}