#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valores(int a){
    if(a<=0)return 1;
    else return 0;


}


int main(){
//Faça uma função que recebe um valor inteiro e verifica se o valor é positivo ou negativo. A função deve retornar um valor lógico (true ou false). Faça um programa que lê N números e para cada um deles exibe uma mensagem informando se ele é positivo ou não, dependendo se foi retornado verdadeiro ou falso pela função. Lembre-se de que zero não é positivo.

    int n,num;
    scanf("%d",&n);
    for(int i =0;i<n;i++){
        scanf("%d",&num);
        if (valores(num)==1)printf("NAO\n");
        else printf("SIM\n");
    }
    return 0;
}
