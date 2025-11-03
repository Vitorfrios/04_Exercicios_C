#include <stdio.h>

void preencher_matriz(int M[10][10]) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            scanf("%d", &M[i][j]);
        }
    }
}

void trocar_linha_2_com_8(int M[10][10]) {
    int temp;
    for(int j = 0; j < 10; j++) {
        temp = M[1][j];
        M[1][j] = M[7][j];
        M[7][j] = temp;
    }
}

void trocar_coluna_4_com_10(int M[10][10]) {
    int temp;
    for(int i = 0; i < 10; i++) {
        temp = M[i][3];
        M[i][3] = M[i][9];
        M[i][9] = temp;
    }
}

void trocar_diagonais(int M[10][10]) {
    int temp;
    for(int i = 0; i < 10; i++) {
        temp = M[i][i];
        M[i][i] = M[i][9-i];
        M[i][9-i] = temp;
    }
}

void trocar_linha_5_com_coluna_10(int M[10][10]) {
    int temp;
    for(int i = 0; i < 10; i++) {
        temp = M[4][i];
        M[4][i] = M[i][9];
        M[i][9] = temp;
    }
}

void exibir_matriz(int M[10][10]) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int M[10][10];
    
    preencher_matriz(M);
    
    trocar_linha_2_com_8(M);
    trocar_coluna_4_com_10(M);
    trocar_diagonais(M);
    trocar_linha_5_com_coluna_10(M);
    
    exibir_matriz(M);
    
    return 0;
}