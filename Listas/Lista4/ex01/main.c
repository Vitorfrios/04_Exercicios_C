#include <stdio.h>
#include <stdlib.h>

int fat(int n){
    if(n<=1)return 1;
    else return n*fat(n-1);
}

int main()
{
//Faça uma função recursiva que calcula o fatorial de um número inteiro positivo.
    int N;
    scanf("%d",&N);
    printf("%d",fat(N));
    return 0;
}
