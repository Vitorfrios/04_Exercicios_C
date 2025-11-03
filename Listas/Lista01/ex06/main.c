#include <stdio.h>
#include <stdlib.h>

int main()
{
/*Faça um programa para ler os coeficientes de uma equação do primeiro grau (ax + b = 0), calcular e escrever a raiz da equação.*/
    int a,b,x;
    scanf("%d%d",&a,&b);
    if(b>0){
        x=-b/a;
    }else{x=b/a;}
    printf("%.2f",(float)x);
    return 0;
}
