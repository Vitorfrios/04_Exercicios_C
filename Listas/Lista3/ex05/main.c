#include <stdio.h>
#include <stdlib.h>
void media(int nota){
    if (nota <= 39) {
        printf("F\n");
    } else if (nota <= 59) {
        printf("E\n");
    } else if (nota <= 69) {
        printf("D\n");
    } else if (nota <= 79) {
        printf("C\n");
    } else if (nota <= 89) {
        printf("B\n");
    } else {
        printf("A\n");
    }

}
int main()
{/*
Faça um procedimento que recebe a média final de um aluno, identifica e exibe o seu conceito, conforme a tabela abaixo. Faça um programa que leia a média de N alunos, acionando o procedimento para cada um deles. (N deve ser lido do teclado)

Nota Conceito Até 39 F 40 a 59 E 60 a 69 D 70 a 79 C 80 a 89 B A partir de 90 A
*/
    int n,nota;
    scanf("%d",&n);
    for(int i =0;i<n;i++){
        scanf("%d",&nota);
        media(nota);
    }
    return 0;
}
