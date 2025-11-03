#include <stdio.h>
#include <stdlib.h>

void media(){
    float sal,media=0,pessoas=0;
    int filho;
    scanf("%f",&sal);
    while(sal>=0){
        scanf("%d",&filho);
        media+=sal;
        scanf("%f",&sal);
        pessoas++;
    }
    printf("%.2f",media/pessoas);
}

int main()
{
//A prefeitura de uma cidade fez uma pesquisa entre os seus habitantes, coletando dados sobre o salário e número de filhos. Faça um procedimento que leia esses dados para um número não determinado de pessoas, calcule e exiba a média de salário da população (a condição de parada deve ser um flag com salário negativo). Faça um programa que acione o procedimento.

    media();
    return 0;
}
