#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valores(int a){
    if(a==0)return 0;
    else return a%10+valores(a/10);


}


int main(){
//Faça uma função para encontrar a soma dos dígitos de um número usando recursão. Faça um programa principal que leia um número, acione a função e exiba o resultado gerado.



    int n;
    scanf("%d",&n);
    printf("%d",valores(n));
    return 0;
}
