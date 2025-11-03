#include <stdio.h>
#include <stdlib.h>

int main()
{
//Adaptar o programa anterior para que ele calcule o percentual dos valores positivos, negativos e zeros em relação ao total de valores fornecidos. Considere o uso do tipo ’long int’ e especificador ’ld’.

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

    printf("%d%% POSITIVOS\n", (posi * 100) / N);
    printf("%d%% NEGATIVOS\n", (neg * 100) / N);
    printf("%d%% ZEROS\n", (zero * 100) / N);

    return 0;
}
