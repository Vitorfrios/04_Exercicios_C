#include <stdio.h>
#include <stdlib.h>

int main() {
    int tamanho, maior;
    
    scanf("%d", &tamanho);
    
    int *vetor = (int*)malloc(tamanho * sizeof(int));
    
    for(int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
        
        if(i == 0) {
            maior = vetor[i];
        } else if(vetor[i] > maior) {
            maior = vetor[i];
        }
    }
    
    printf("%d\n", maior);
    
    free(vetor);
    return 0;
}