#include <stdio.h>
#include <stdlib.h>


float conta(int num){
    float n,media=0,soma=0;
    for(int i =0;i<num;i++){
        scanf("%f",&n);
        if(n>=6){soma+=n;media++;}
    }
    return soma/media;


}


int main()
{
/*Faça uma função que lê um número determinado de notas de alunos, calcula e retorna a média das notas dos alunos aprovados (nota maior ou igual a 6). Faça um programa que lê o número de alunos e imprime a média retornada pela função.

*/
    int num;
    scanf("%d",&num);
    printf("%.1f",conta(num));
    return 0;
}
