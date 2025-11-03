#include <stdio.h>

double calcularS(int N) {
    double S = 1.0;
    double fatorial = 1.0;

    for (int i = 1; i <= N; i++) {
        fatorial *= i;
        S += 1.0 / fatorial;
    }

    return S;
}

int main() {
    int N;

    scanf("%d", &N);

    if (N < 0) {
        return 1;
    }

    double resultado = calcularS(N);
    printf("%.6lf\n",resultado);

    return 0;
}
