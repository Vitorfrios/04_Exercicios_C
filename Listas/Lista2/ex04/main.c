#include <stdio.h>
#include <stdlib.h>

int main()
{
//Escrever um algoritmo que lê um valor N inteiro e positivo e que calcula e escreve o valor de E: E = 1 + 1/1! + 1/2! + 1/3! + .... + 1/N!
//(1/fatorial de N)+.....
//fatorial de 7 = 1*2*3*4*5*6*7
/*
Escrever o fatorial em fração 1/1*1/2..
*/
    int n;
    double conta=1,E=1.0;
    scanf("%d",&n);

    for(int i = 0;i<n;i++){
        conta*=i+1;
        E+=1/conta;
    }
    printf("%.2lf\n",E);
    return 0;
}

