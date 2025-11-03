#include <stdio.h>
#include <stdlib.h>


int main()
{
//Escreva um algoritmo que lê um valor n inteiro e positivo e que calcula a seguinte soma: S = 1 + 1/2 + 1/3 + 1/4 + ... + 1/n O algoritmo deve escrever o valor final de S.

    int n;
    float S=0;
    scanf("%d",&n);
    for(int i =1;i<=n;i++){
        S+=1/(float)i;
    }

    printf("%.2f",S);
    return 0;
}
