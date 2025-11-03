#include <stdio.h>

int divisao(int numerador, int denominador) {
    if (numerador < denominador)
        return 0;                  // caso base
    else
        return 1 + divisao(numerador - denominador, denominador); // recursão
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (b == 0)
        return 1;  // tratamento simples para divisão por zero
    printf("%d",divisao(a, b));  // exibe o resultado
    return 0;
}
