#include <stdio.h>
#include <stdlib.h>

int main() {
    int tamanho;
    
    scanf("%d", &tamanho);
    
    int *vetor = (int*)malloc(tamanho * sizeof(int));
    
    for(int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }
    
    int *ptr_i, *ptr_j;
    for(ptr_i = vetor; ptr_i < vetor + tamanho - 1; ptr_i++) {
        for(ptr_j = ptr_i + 1; ptr_j < vetor + tamanho; ptr_j++) {
            if(*ptr_i > *ptr_j) {
                int temp = *ptr_i;
                *ptr_i = *ptr_j;
                *ptr_j = temp;
            }
        }
    }
    
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    free(vetor);
    return 0;
}