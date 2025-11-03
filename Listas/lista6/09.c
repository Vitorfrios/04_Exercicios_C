#include <stdio.h>
#include <stdlib.h>

int main() {
    int tamanho, soma = 0;
    
    scanf("%d", &tamanho);
    
    int *vetor = (int*)malloc(tamanho * sizeof(int));
    
    for(int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }
    
    int *ptr = vetor;
    for(int i = 0; i < tamanho; i++) {
        soma += *ptr;
        ptr++;
    }
    
    printf("%d\n", soma);
    
    free(vetor);
    return 0;
}