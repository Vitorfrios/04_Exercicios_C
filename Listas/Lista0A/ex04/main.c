#include <stdio.h>
#include <stdlib.h>

int main()
{
//Ler o raio de um c�rculo e mostrar o seu per�metro e �rea. Considere o valor de PI como 3.14159
    float raio;
    float pi=3.14159;
    scanf("%f", &raio);
    printf("Perimetro: %.2f\n", 2*pi*raio);
    printf("Area: %.2f\n", pi*raio*raio);
    return 0;
}
