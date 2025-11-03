#include <stdio.h>
#include <stdlib.h>
void triangulo(int a,int b,int c){
    if(a<b+c&&b<a+c&&c<a+b){
        if(a==b&&b==c&&a==c)printf("TRIANGULO EQUILATERO\n");
        else if(a==b||a==c||b==c)printf("TRIANGULO ISOSCELES\n");
        else printf("TRIANGULO ESCALENO\n");
    } else printf("NAO TRIANGULO\n");


}
int main()
{
/*Escreva um procedimento que recebe 3 valores reais X, Y e Z e que
// verifique se esses valores podem ser os comprimentos dos lados de um triângulo e, neste caso, exibe qual é o tipo de triângulo formado.
//Para que X, Y e Z formem um triângulo é necessário que a seguinte propriedade seja satisfeita:
//o comprimento de cada lado de um triângulo é menor do que a soma do comprimento dos outros dois lados.
//O procedimento deve identificar o tipo de triângulo formado observando as seguintes definições:
    //• Triângulo Equilátero: os comprimentos dos 3 lados são iguais;
    • Triângulo Isósceles: os comprimentos de pelo menos 2 lados são iguais.
    • Triângulo Escaleno: os comprimentos dos 3 lados são diferentes.
Faça um programa que leia um número indeterminado (até lado negativo) de triângulos (valores dos 3 lados) e para cada triângulo, acione o procedimento.*/

    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    while(a>=0&&b>=0&&c>=0){
        triangulo(a,b,c);
        scanf("%d%d%d",&a,&b,&c);
    }
    return 0;
}

