#include <stdio.h>

void preencher_matrizes(int A[4][6], int B[4][6]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            scanf("%d", &B[i][j]);
        }
    }
}

void soma_matrizes(int A[4][6], int B[4][6], int S[4][6]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            S[i][j] = A[i][j] + B[i][j];
        }
    }
}

void diferenca_matrizes(int A[4][6], int B[4][6], int D[4][6]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            D[i][j] = A[i][j] - B[i][j];
        }
    }
}

void exibir_matriz(int matriz[4][6]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            printf("%d ", matriz[i][j]);
        }
    }
    printf("\n");
}

int main() {
    int A[4][6], B[4][6], S[4][6], D[4][6];
    
    preencher_matrizes(A, B);
    
    soma_matrizes(A, B, S);
    diferenca_matrizes(A, B, D);
    
    exibir_matriz(S);
    exibir_matriz(D);
    
    return 0;
}