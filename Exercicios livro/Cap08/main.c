#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Exercicios propostos
int Nint(int n){
    if(n==0||n==1)return 1;
    else if(n>1) return n+Nint(n-1);
    else return -1;
}
int ex1(){
    //Faça uma sub-rotina que receba um número inteiro e positivo N como parâmetro e retorne a soma dos números inteiros existentes entre o número 1 e N (inclusive)
    int n;
    printf("Digite o valor de N: ");
    scanf("%d",&n);
    printf("A soma dos valores de 1 ate N eh %d\n",Nint(n));
}

float divrecurs(float n){
    if(n==1)return 1;
    else if(n>1) return 1/n+divrecurs(n-1);
}
int ex2(){
    //S=1+1/2+1/3+1/4+1/5+1/n recursivo
    int x;
    printf("Digite o numero X: ");
    scanf("%d",&x);
    printf("A soma eh %.2f\n",divrecurs(x));
}

float Sd(int n) {
    if (n == 1)return 1.0 / 2.0;
    else if (n > 1)return((pow(n, 2) + 1.0) / (n + 3.0)) + Sd(n - 1);
    else return 0;
}

int ex3(){
//S=(n²+1)/(n+3) recursivo
    int x;
    printf("Digite o valor de X: ");
    scanf("%d",&x);
    printf("O valor de S eh %.2f\n",Sd(x));
}

int pote(int x,int z){
    if(z==0 )return 1;
    else if(z>=1) return x*pote(x,z-1);
    else return -1;

}
int ex4(){
    int x,z;
    printf("Digite X e Z: ");
    scanf("%d%d",&x,&z);
    printf("O valor de X elevado a Z eh %d\n",pote(x,z));

}




int main() {
    int num;
    int (*exercicios[30])() = {
         ex1,ex2,ex3,ex4 NULL
    };

    while (1) {
        printf("Escolha o numero do exercicio (0 para sair): ");
        scanf("%d", &num);

        if (num == 0) {
            printf("Saindo dos exercicios!\n");
            break;
        } else if (num > 0 && num <= 30 && exercicios[num - 1] != NULL) {
            exercicios[num - 1]();
        } else {
            printf("Exercicio %d nao existe.\n", num);
        }

    }

    return 0;
}
