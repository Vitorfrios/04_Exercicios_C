#include <stdio.h>

// Função para calcular fatorial
double fatorial(int n) {
    if (n == 0)
        return 1;          // 0! = 1
    else
        return n * fatorial(n - 1);
}

// Função para calcular a série
double serie(int n) {
    if (n == 1)
        return 1.0;        // caso base: 1/1! = 1
    else
        return 1.0 / fatorial(n) + serie(n - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%.2f", serie(n));

    return 0;
}
