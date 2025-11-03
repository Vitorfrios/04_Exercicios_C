#include <stdio.h>

void preencher_notas(float vetor[]) {
    for (int i = 0; i < 10; i++) {
        scanf("%f", &vetor[i]);
    }
}

void calcular_media_e_acima(float vetor[]) {
    float soma = 0;
    int acima_media = 0;
    
    for (int i = 0; i < 10; i++) {
        soma += vetor[i];
    }
    
    float media = soma / 10;
    
    for (int i = 0; i < 10; i++) {
        if (vetor[i] >= 6.0) {
            acima_media++;
        }
    }
    
    printf("Media: %.2f\n", media);
    printf("Alunos acima da media: %d\n", acima_media);
}

int main() {
    float notas[10];
    
    preencher_notas(notas);
    calcular_media_e_acima(notas);
    
    return 0;
}