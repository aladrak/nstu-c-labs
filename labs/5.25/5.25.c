#include <stdio.h> // gcc 5.25.c -o 5.25.exe
#include <stdlib.h>
#include <ctype.h>

#define BUF_SIZE 256
#define CHO '0'

// typedef struct {
    
// } Nums;

char* transDecToBin(int n, int* len); // Целая часть сс10 -> cc2
char* transFracDecToBin(double n, int* len); // Дробная часть сс10 -> cc2

int transBinToDec(char* n, int* len); // Целая часть сс2 -> сс10
double transFracBinToDec(char* n, int* len); // Дробная часть сс2 -> сс10

char* transHex(int n, int* len);

void printReverse(char* buf, int* len) {
    if (*len == 0) {
        printf("0");
    }
    for (int i = *len - 1; i >= 0; i--) {
        printf("%c", buf[i]); 
    }
    printf("\n");
}

void printRight(char* buf, int* len) {
    for (int i = 0; i < *len; i++) {
        printf("%c", buf[i]); 
    }
    printf("\n");
}

void fillArr(char* buf, int len) {
    for (int i = 0; i < len; i++) {
        buf[i] = '0';
    }
}

void copyArr(char* oldbuf, int len, char* newbuf, int start, int end) {
    int j = start;
    for (int i = 0; i < len; i++) {
        oldbuf[i] = newbuf[j++];
    }
}

int main() {
    double number = 0.0;
    char* intbuff = NULL, *fracbuff = NULL;
    int system = 0, *intlen = (int*)malloc(sizeof(int)), *fraclen = (int*)malloc(sizeof(int));

    while (1) {
        printf("Enter number: "); scanf("%lf", &number); 
        printf("Enter system: "); scanf("%d", &system); 
        // number = s;

        switch (system) {
        case 2:
            free(intbuff); intbuff = NULL;
            intbuff = transDecToBin((int)number, intlen);
            printReverse(intbuff, intlen);
            if (number - (int)number > 0.) {
                free(fracbuff); fracbuff = NULL;
                fracbuff = transFracDecToBin(number - (int)number, fraclen);
                printRight(fracbuff, fraclen);
            }
            break;
		case 10:
            printf("%d\n", transBinToDec(intbuff, intlen));
            printf(".");
            printf("%lf\n", transFracBinToDec(fracbuff, fraclen));
			break;
        case 16:
            free(intbuff); intbuff = NULL;
            intbuff = transHex((int)number, intlen);
            printReverse(intbuff, intlen);
            break;
        default:
            printf("Error");
            return 0;
            break;
        }
    }
}

char* transDecToBin(int n, int* len) {
    char* buf = (char*)malloc(BUF_SIZE * sizeof(char));
    int i = 0;
    while (n > 0) {
        buf[i] = (n % 2) + '0';
        n /= 2;
        i++;
    }
    *len = i;
    buf[i] = '\0';
    return buf;
}

char* transHex(int n, int* len) {
    char* buf = (char*)malloc(BUF_SIZE * sizeof(char));
    int i = 0, rest;
    while (n > 0) {
        rest = n % 16;
        if (rest >= 10) {
            buf[i] = rest - 10 + 'A'; 
        } else {
            buf[i] = rest + '0';
        }
        i++;
        n /= 16;
    }
    *len = i;
    buf[i] = '\0';
    return buf;
}

char* transFracDecToBin(double n, int* len) {
    char* buf = (char*)malloc(BUF_SIZE * sizeof(char));
    int bit, i = 0;
    while (n > 0) {
        n *= 2;
        bit = (int)n;  
        buf[i++] = bit + '0';
        n -= bit;
    }
    *len = i;
    buf[i] = '\0';
    return buf;
}

int transBinToDec(char* buf, int* len) {
    int dec = 0, power = 1;
    for (int i = 0; i < *len; i++) {
        if (buf[i] == '1') {
            dec += power;
        }
        power *= 2;
    }
    return dec;
}

double transFracBinToDec(char* buf, int* len) { // x 1010
    char *resbuf = (char*)malloc(BUF_SIZE * sizeof(char)); 
    int *reslen = (int*)malloc(1 * sizeof(int)); *reslen = *len + 6; 
    fillArr(resbuf, *reslen);
    int binTen[4] = {1, 0, 1, 0};
    for (int c = 0; c < 10; c++) {
        int offset = 0;
        for (int i = 3; i >= 0; i--) {
            if (binTen[i] == 0) {
                offset += 1;
                continue;
            }
            int b = 0;
            for (int j = *reslen - 1, k = *len - 1; j >= 0; j--, k--) {
                if (k >= 0) {
                    resbuf[j-offset] = (resbuf[j-offset] - CHO) + (buf[k] - CHO) + CHO;
                }
                // resbuf[j-offset] = b + CHO;
                // if (resbuf[j-offset] == '2') {
                //     b++;
                // }
                int v = j;
                while (resbuf[v] > '1' && v > 5) {
                    resbuf[v] = '1';
                    resbuf[v-1] = ((resbuf[v-1] - CHO) + 1) + CHO;
                    v--;
                }
                printRight(resbuf, reslen);
            }
            offset += 1;
        }
    }
    printRight(resbuf, reslen);
    return 22.1;
}