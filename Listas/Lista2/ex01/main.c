#include <stdio.h>
#include <stdlib.h>

int main()
{
//Fazer um programa leia uma sequência de N valores inteiros fornecida pelo usuário em uma linha de entrada e conte o número de valores positivos, negativos e zeros. Considere N fornecido pelo teclado e os números podem ser maiores do que o limite estabelecido pelo tipo ’int’, sendo sugerido o uso de ’long int’ e especificador ’ld’.

    int N,zero=0,posi=0,neg=0;
    long int num;
    //printf("Digite a quantidade de nuemrso: ");
    scanf("%d",&N);

    for (int i =0;i<N;i++){
        //printf("Digite o %d numro",i+1);
        scanf("%ld",&num);
        if(num==0){zero++;}
        else if(num>0){posi++;}
        else{neg++;}
    }

    printf("%d POSITIVOS\n",posi);
    printf("%d NEGATIVOS\n",neg);
    printf("%d ZEROS\n",zero);
    return 0;
}
