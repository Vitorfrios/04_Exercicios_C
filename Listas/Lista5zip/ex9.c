#include <stdio.h>

int resto(int numerador, int denominador) {
    if (numerador < denominador)      // caso base: não dá para subtrair mais
        return numerador;             // o que sobra é o resto
    else
        return resto(numerador - denominador, denominador); // subtração + recursão
}

int main() {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    printf("%d", resto(a, b));


    return 0;
}
