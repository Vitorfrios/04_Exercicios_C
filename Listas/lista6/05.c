#include <stdio.h>

void preencher_matriz(int M[5][5]) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            scanf("%d", &M[i][j]);
        }
    }
}

int soma_linha_5(int M[5][5]) {
    int soma = 0;
    for(int j = 0; j < 5; j++) {
        soma += M[4][j];
    }
    return soma;
}

int soma_coluna_2(int M[5][5]) {
    int soma = 0;
    for (int i = 0; i < 5; i++) {
        soma += M[i][2];
    }
    return soma;
}


int soma_diagonal_principal(int M[5][5]) {
    int soma = 0;
    for(int i = 0; i < 5; i++) {
        soma += M[i][i];
    }
    return soma;
}

int soma_diagonal_secundaria(int M[5][5]) {
    int soma = 0;
    for(int i = 0; i < 5; i++) {
        soma += M[i][4-i];
    }
    return soma;
}

int soma_total(int M[5][5]) {
    int soma = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            soma += M[i][j];
        }
    }
    return soma;
}

int main() {
    int M[5][5];
    
    preencher_matriz(M);
    
    printf("%d\n", soma_linha_5(M));
    printf("%d\n", soma_coluna_2(M));
    printf("%d\n", soma_diagonal_principal(M));
    printf("%d\n", soma_diagonal_secundaria(M));
    printf("%d\n", soma_total(M));
    
    return 0;
}