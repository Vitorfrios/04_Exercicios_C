#include <stdio.h>

int main() {
    int matriz[4][4];
    int soma_abaixo = 0;
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i > j) {
                soma_abaixo += matriz[i][j];
            }
        }
    }
    
    printf("%d\n", soma_abaixo);
    
    for(int i = 0; i < 4; i++) {
        printf("%d ", matriz[i][i]);
    }
    printf("\n");
    
    return 0;
}