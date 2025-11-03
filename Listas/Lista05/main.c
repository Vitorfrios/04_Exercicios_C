#include <stdio.h>
#include <stdlib.h>
//Faça um programa que leia 3 números inteiros (a, b, c). Para cada valor lido, mostre o nome da variável, o endereço e o seu valor.
int ex1(){
    int x , *p , **q ;
    *p = &x ;
    **q = &p ;
    x = 10;
    printf ( "\n%d\n " , **q ) ;
    return (0) ;

}




int main()
{
    int num;
    printf("Digite o numero do exercicio: ");
    scanf("%d", &num);
    int (*exercicios[30])()={ex1,NULL};
    while(num!=0){
        if(num > 0 && num <= 30 && exercicios[num - 1] != NULL)exercicios[num-1]();
        else printf("Exercicio %d nao existe ", num);
        scanf("%d", &num);
    }


    return 0;
}
