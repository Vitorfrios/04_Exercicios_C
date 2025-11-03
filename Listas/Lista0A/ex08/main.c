#include <stdio.h>
#include <stdlib.h>

int main()
{
/*Ler dois números reais e salvá-los nas variáveis A e B. Em seguida, troque dos valores das duas variáveis
de forma que a variável A passe a ter o valor da variável B e vice-versa. No final, mostre os valores finais.
*/
    float A,B,temp;
    scanf("%f%f",&A,&B);
    temp=A;
    A=B;
    B=temp;
    printf("%f %f",A,B);


    return 0;
}
