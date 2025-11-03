#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* Sabendo que 100 kilowatt de energia custa um sétimo do salário mínimo,
       leia o valor do salário mínimo e a quantidade de kilowatt gasta por uma residência,
       e calcule:
       - valor de cada kilowatt
       - valor total a ser pago
       - valor com desconto de 10% */

    int klw;
    float sal, valorklw, valor_total, valor_desconto;

    scanf("%f %d", &sal, &klw);

    valorklw = (sal / 7) / 100;

    valor_total = klw * valorklw;
    valor_desconto = valor_total * 0.90;

    printf("Valor do kW: %.2f\n", valorklw);
    printf("Valor a pagar: %.2f\n", valor_total);
    printf("Valor com desconto: %.2f\n", valor_desconto);

    return 0;
}
