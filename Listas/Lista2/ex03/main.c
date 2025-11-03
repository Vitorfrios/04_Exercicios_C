#include <stdio.h>

int main() {
    double num;          // lê números reais
    int inteiro;         // parte inteira do número
    int count = 0;       // contador de números lidos
    int a = 0, b = 0, c = 0,d=0; // contadores: 3&9, 2, 5

    while (count != 10) {
        scanf("%lf", &num);       // lê decimal ou inteiro
        inteiro = (int)num;

        int divisivel = 0;

        if (inteiro % 3 == 0 && inteiro % 9 == 0) { a++; divisivel = 1; }
        if (inteiro % 2 == 0) { b++; divisivel = 1; }
        if (inteiro % 5 == 0) { c++; divisivel = 1; }

        if (!divisivel) { d++; }

        count++;
    }
    for(int i =0; i<d;i++){
        printf("Numero nao eh divisivel pelos valores\n");
    }
    printf("%d Numeros sao divisiveis por 3 e por 9\n", a);
    printf("%d Numeros sao divisiveis por 2\n", b);
    printf("%d Numeros sao divisiveis por 5\n", c);

    return 0;
}
