#include <stdio.h>
#include <stdlib.h>


int main() {
    char opcao;
    double salario;

    scanf(" %c", &opcao);

    scanf("%lf", &salario);

    switch(opcao) {
        case 'A':
            salario = salario * 1.08;
            break;
        case 'B':
            salario = salario * 1.11;
            break;
        case 'C':
            if (salario <= 1000)
                salario += 350;
            else
                salario += 200;
            break;
        default:
            return 0;
    }

    printf("%.2f\n", salario);

    return 0;
}

