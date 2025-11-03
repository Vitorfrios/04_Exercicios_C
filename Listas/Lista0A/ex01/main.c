#include <stdio.h>
#include <stdlib.h>

int main()
{
//Ler do teclado um número inteiro com três dígitos
//(no formato CDU - centena, dezena e unidade) e mostrar o número invertido (no formato UDC).
//O número invertido deve ser armazenado em outra variável antes de ser mostrado.

    int num, cent, dez, un;
    scanf("%d", &num);

    cent = num / 100;
    dez  = (num / 10) % 10;
    un   = num % 10;

    printf("%d\n", un*100 + dez*10 + cent);

    return 0;
}
