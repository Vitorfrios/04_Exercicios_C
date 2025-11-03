#include <stdio.h>

int num(int N) {
    if (N < 0) N = -N;          // transforma negativo em positivo
    if (N == 0) return 1;       // caso especial: 0 tem 1 dígito
    if (N / 10 == 0) return 1;  // último dígito
    return 1 + num(N / 10);
}

int main() {
    int N;
    while (scanf("%d", &N) == 1) {  // lê todos os números até EOF
        printf("%d\n", num(N));     // imprime com quebra de linha
    }
    return 0;
}
