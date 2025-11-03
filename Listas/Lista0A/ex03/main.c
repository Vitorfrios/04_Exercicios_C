#include <stdio.h>
#include <stdlib.h>

int main()
{
//Ler a base e a altura de um retângulo e mostrar o seu perímetro, área e diagonal
    float base,altura;
    //printf("Digite a base e a altura:");
    scanf("%f%f",&base,&altura);
    printf("Perimetro: %.2f\n", (base*2)+(altura*2));
    printf("Area: %.2f\n", base*altura);
    printf("Diagonal: %.2f\n", sqrt(base*base+altura*altura));
    return 0;
}
