#include <stdio.h>

void ordenarTres(int numeros[]) {
    int temp;

    // Passo 1
    if (numeros[0] > numeros[1]) {
        temp = numeros[0];
        numeros[0] = numeros[1];
        numeros[1] = temp;
    }

    // Passo 2
    if (numeros[1] > numeros[2]) {
        temp = numeros[1];
        numeros[1] = numeros[2];
        numeros[2] = temp;
    }

    // Passo 3
    if (numeros[0] > numeros[1]) {
        temp = numeros[0];
        numeros[0] = numeros[1];
        numeros[1] = temp;
    }
}

int main() {
    int numeros[3];
    int qnt;
    scanf("%d", &qnt);

    for (int i = 0; i < qnt; i++) {
        // Lê 3 números por vez
        scanf("%d %d %d", &numeros[0], &numeros[1], &numeros[2]);

        ordenarTres(numeros);

        printf("%d %d %d\n", numeros[0], numeros[1], numeros[2]);
    }

    return 0;
}
