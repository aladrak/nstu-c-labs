void main () {
    int k = 0;
    int Tcurr[20+1], Tprev[20+1];
    printf("Enter number k: "); scanf("%d", &k);
    for(int i = 0; i <= 20; i++) {
        Tprev[i] = Tcurr[i] = 0;
    }
    Tprev[0] = 1; // T[0] = 1.
    Tcurr[1] = 1; // Т[1] = X.
    for(int i = 2; i <= k; i++) {
        int buffer[20+1];
        for(int j = 0; j <= 20; j++) { buffer[j] = Tcurr[j]; }
        for(int j = 20; j > 0; j--) { Tcurr[j] = Tcurr[j-1]*2; }
    //Вычитание
        Tcurr[0] = 0;
        for(int j = 0; j <= 20; j++) { Tcurr[j] -= Tprev[j]; } 
        for(int j = 0; j <= 20; j++) { Tprev[j] = buffer[j]; }
    }

    int check = 0;
    for(int i = 20; i >= 0; i--) {
        if (Tcurr[i]) {
            if (Tcurr[i] > 0 && check) printf("+");
            printf("%d", Tcurr[i]);
            if (i) printf("x^%d", i);
            check = 1;
        }
    }
}