#include <stdio.h>
#include <stdlib.h>

int main()
{
//Faça um programa que imprima todos os elementos da série de Fibonacci menores que L.
    int L,p1=0,p2=1;
    int s;
    scanf("%d",&L);
    while(s<L){
        printf("%d ",p1);
        s = p1+p2;
        p2=p1;
        p1=s;
    }


    return 0;
}
