#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Faça um algoritmo que leia 2 números inteiros e faça sua adição.
    // Se o resultado for maior ou igual a 10, some 5 a este número.
    // Caso contrário some 7 a ele. Imprima o resultado final.

    int a, b, soma;
    scanf("%d%d", &a, &b);
    soma = a + b;
    
    if (soma >= 10) {
        soma += 5; // Equivalente a: soma = soma + 5
    } else {
        soma += 7; // Equivalente a: soma = soma + 7
    }
    
    printf("%d", soma);
    return 0;
}