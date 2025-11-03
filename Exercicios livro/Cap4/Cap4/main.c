#include <stdio.h>
#include <stdlib.h>

float Pnumero(char mensagem[])
{   float valor;
    printf("%s",mensagem);
    scanf("%f",&valor);
    if (valor >= 0){return valor;}
    else {printf("Digite um valor acima de zero"); return Pnumero(mensagem);}
}


int maior(int numeros[], int qnt) {
    // Caso base: se só tem 1 elemento
    if (qnt == 1) {
        return numeros[0];
    } else {
        // Maior do restante do array
        int maior_restante = maior(numeros, qnt - 1);

        // Comparar último elemento com maior do restante
        if (numeros[qnt - 1] > maior_restante) {
            return numeros[qnt - 1];
        } else {
            return maior_restante;
        }
    }
}
int ex3(){
    int qnt = Pnumero("Digite a quantidade de numeros: ");
    int num[qnt];
    for(int i = 0; i<qnt; i++){
        num[i] = Pnumero("Digite um numero: ");

    }
    printf("%d\n",maior(num,qnt));
    return 0;
}


void ordenar( int array[], int qnt){
    if (qnt<=1)return; //caso base

    for(int i =0;i<qnt;i++){
        if(array[i]>array[i+1]){
            int temp = array[i];
            array[i]=array[i+1];
            array[i+1] = temp;
        }

    }
    ordenar(array,qnt-1);
}
int ex4(){
    int qnt = Pnumero("Digite a quantidade de numeros: ");
    int numeros[qnt];

    for(int i =0; i<qnt; i++){
        numeros[i]= Pnumero("Digite o numero: ");
    }

    ordenar(numeros, qnt);

    printf("Array ordenado: ");
    for (int i = 0; i < qnt; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}


void decrescente(int array[],int qnt){
    if (qnt==1)return;//caso base

    for (int i =0;i<qnt;i++){
        if (array[i]<array[i+1]){
            int temp = array[i];
            array[i]=array[i+1];
            array[i+1] = temp;
        }
    }
    decrescente(array,qnt-1);
}
int ex5(){
    int qnt = Pnumero("Digite o numero adicional: ");
    int lista[qnt];
    for (int i =0;i<qnt;i++){
        lista[i]=Pnumero("Digite o numero: ");
    }
    decrescente(lista,qnt);
    printf("a lisyta decrescente: ");
    for(int i =0;i<qnt;i++){
        printf("%d ",lista[i]);
    }
    printf("\n");
}

void fibo(int lista[], int qnt) {
    if (qnt == 1) {
        lista[0] = 0; // caso base 1
    }
    else if (qnt == 2) {
        lista[0] = 0; // caso base 2
        lista[1] = 1;
    }
    else {
        fibo(lista, qnt - 1); // preenche os qnt-1 primeiros termos
        lista[qnt - 1] = lista[qnt - 2] + lista[qnt - 3]; // calcula o termo atual
    }
}
int fibo2(int n){
    if (n==1)return 0;
    else if(n==2)return 1;
    else {return fibo2(n-1)+fibo2(n-2);}
}
int ex6(){
    int qnt = Pnumero("Digite ate que termo deseja ver: ");
    int lista[qnt];
    fibo(lista, qnt); // preenche a lista recursivamente

    printf("Sequência de Fibonacci: ");
    for (int i = 0; i < qnt; i++) {
        printf("%d ", lista[i]);
    }
    printf("%d",fibo2(qnt));
    printf("\n");
    return 0;

}



void dec(float a, float b, float c) {
    if (a >= b && a >= c) {
        if (b >= c) {
            printf("%.2f %.2f %.2f\n", a, b, c);
        } else {
            printf("%.2f %.2f %.2f\n", a, c, b);
        }
    }
    else if (b >= a && b >= c) {
        if (a >= c) {
            printf("%.2f %.2f %.2f\n", b, a, c);
        } else {
            printf("%.2f %.2f %.2f\n", b, c, a);
        }
    }
    else {
        if (a >= b) {
            printf("%.2f %.2f %.2f\n", c, a, b);
        } else {
            printf("%.2f %.2f %.2f\n", c, b, a);
        }
    }
}
void cre(float a,float b,float c){}
void maiorD(float a,float b,float c){}
int ex7(){
/*Faça um programa que receba quatro valores: I, A, B e C. Desses valores, I é inteiro e positivo, A, B e
C são reais. Escreva os números A, B e C obedecendo à tabela a seguir.
Suponha que o valor digitado para I seja sempre um valor válido, ou seja, 1, 2 ou 3, e que os números
digitados sejam diferentes um do outro.
VALor dE i ForMA A EsCrEVEr
1 A, B e C em ordem crescente.
2 A, B e C em ordem decrescente.
3 O maior fica entre os outros dois números*/
    int I =Pnumero("DIgite um numero: ");
    float A = Pnumero("digite um numero");
    float B = Pnumero("digite um numero");
    float C = Pnumero("digite um numero");

    switch(I){
    case 1:
        dec(A,B,C);
        printf("\n");
    case 2:
        cre(A,B,C);
        printf("\n");
    case 3:
        maiorD(A,B,C);
        printf("\n");
    }
}


int main(){
    int num;
    int (*exercicios[30])() = {
         1,2,ex3,ex4,ex5,ex6,ex7 NULL
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
