#include <stdio.h>

int main() {
    float temperaturas[31];
    float soma = 0, menor, maior;
    int dias_abaixo_media = 0;
    
    for(int i = 0; i < 31; i++) {
        scanf("%f", &temperaturas[i]);
        soma += temperaturas[i];
        
        if(i == 0) {
            menor = temperaturas[i];
            maior = temperaturas[i];
        } else {
            if(temperaturas[i] < menor) menor = temperaturas[i];
            if(temperaturas[i] > maior) maior = temperaturas[i];
        }
    }
    
    float media = soma / 31;
    
    for(int i = 0; i < 31; i++) {
        if(temperaturas[i] < media) {
            dias_abaixo_media++;
        }
    }
    
    printf("Menor e maior temperatura: %.0f e %.0f\n", menor, maior);
    printf("Media de temperatura: %.2f\n", media);
    printf("Numero de dias nos quais a temperatura foi inferior a temperatura media: %d\n", dias_abaixo_media);
    
    return 0;
}