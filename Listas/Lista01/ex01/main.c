#include <stdio.h>
#include <stdlib.h>

int main(){
    //Fa�a um programa que receba tr�s n�meros e mostre o maior

    int a,b;
    //printf("Digite o numero: ");
    scanf("%d%d%d",&a,&b);

    if (a>b){printf("%d",a);}
    else{printf("%d",b);}
    return 0;
}
