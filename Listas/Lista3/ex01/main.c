#include <stdio.h>
#include <stdlib.h>

void conta(float a1[],char esco ){
    float soma=0,media=0;

    switch(esco){
        case 'A':
            for(int i =0;i<3;i++){
                soma+= a1[i];
            }
            printf("%.2f\n",soma/3);
            break;
        case 'P':
            media = ((a1[0]*5) + (a1[1]*3) + (a1[2]*2)) / 10.0;

            printf("%.2f\n",media);
            break;
        default: break;
    }



}


int main()
{
    //Faça um procedimento que recebe as 3 notas de um aluno por parâmetro e uma letra. Se a letra for ‘A’, o procedimento calcula e escreve a média aritmética das notas do aluno, se for ‘P’, calcula e escreve a sua média ponderada (pesos: 5, 3 e 2). Faça um programa que leia 3 notas de N alunos e acione o procedimento para cada aluno. (N deve ser lido do teclado)

    int qnt;
    scanf("%d",&qnt);
    for(int j=0;j<qnt;j++){
        float n1[3];
        char op;
        for(int i =0;i<3;i++){
            scanf("%f",&n1[i]);
        }
        scanf(" %c",&op);
        conta(n1,op);

    }

    return 0;
}
