#include <stdio.h>

void preencher_vetores(int X[], int Y[]) {
    for(int i = 0; i < 10; i++) {
        scanf("%d", &X[i]);
    }
    for(int i = 0; i < 10; i++) {
        scanf("%d", &Y[i]);
    }
}

void intercalar_vetores(int X[], int Y[], int Z[]) {
    int pos_X = 0, pos_Y = 0;
    
    for(int i = 0; i < 20; i++) {
        if(i % 2 == 0) {     // posições pares: X
            Z[i] = X[pos_X];
            pos_X++;
        } else {              // posições ímpares: Y
            Z[i] = Y[pos_Y];
            pos_Y++;
        }
    }
}


void exibir_vetor(int vetor[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int X[10], Y[10], Z[20];
    
    preencher_vetores(X, Y);
    intercalar_vetores(X, Y, Z);
    exibir_vetor(Z, 20);
    
    return 0;
}