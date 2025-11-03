#include <stdio.h>

// ------------------------------
// EXERCÍCIO 1 (somaDois)
// Enunciado: Crie uma função que receba dois inteiros e retorne a soma.
// Objetivo: treinar funções simples e retorno.
// Função: int somaDois(int a, int b);
// ------------------------------
int somaDois() {
    int n;

    printf("digite a quantidade de termos que deseja somar: ");
    scanf("%d",&n);

    int numeros[n],soma=0;
    for(int i =0;i<n;i++){
        printf("Digite o %d numero: ",i+1);
        scanf("%d",&numeros[i]);
        soma += numeros[i];
    }
    printf("A soma final eh %d",soma);
    return 0;
}

// ------------------------------
// EXERCÍCIO 2 (ehPar)
// Enunciado: Crie uma função que receba um inteiro e retorne 1 se for par e 0 se for ímpar.
// Objetivo: treinar condicionais.
// Função: int ehPar(int n);
// ------------------------------
int ehPar(int n) {
    int a;
    printf("DIgite o numero: ");
    scanf("%d",&a);
    if(a%2==0)printf("1");
    else printf("0");
    return 0;
}

// ------------------------------
// EXERCÍCIO 3 (tabuada)
// Enunciado: Escreva uma função que mostre a tabuada de um número de 1 a 10.
// Objetivo: usar laço FOR (contagem conhecida).
// Função: void tabuada(int n);
// ------------------------------
void tabuada(int n) {
    int tabu;
    printf("Digite o numero da tabuada: ");
    scanf("%d",&tabu);
    for(int i =1; i<=10;i++){
        printf("%d * %d = %d\n",tabu,i,tabu*i);

    }

}

// ------------------------------
// EXERCÍCIO 4 (somaAteN)
// Enunciado: Calcule a soma de todos os números de 1 até n.
// Objetivo: usar laço WHILE (contagem até condição).
// Função: int somaAteN(int n);
// ------------------------------
int somaAteN() {
    int n=0,i=1,soma=0;
    printf("Soma de termos");
    scanf("%d",&n);
    while(){
        soma += n;
        i++;
    }
    printf("A soma final eh %d ",soma);
    return 0;
}

// ------------------------------
// EXERCÍCIO 5 (menuSimples)
// Enunciado: Crie uma função que mostre um menu repetidamente até o usuário digitar 0.
// Objetivo: usar DO WHILE (executa pelo menos uma vez).
// Função: void menuSimples();
// ------------------------------
void menuSimples() {
    int n;
    do{
        printf("Menu");
        scanf("%d",&n);

    }while(n!=0);

}

// ------------------------------
// EXERCÍCIO 6 (fatorialIterativo)
// Enunciado: Calcule o fatorial de um número usando laço.
// Objetivo: treinar laço FOR ou WHILE.
// Função: int fatorialIterativo(int n);
// ------------------------------
int fatorialIterativo() {
    int n, fat=1;
    printf("Digite o numero fat: ");
    scanf("%d",&n);
    for(int i = n;i<=2;i--){
        fat*=n;

    }
    printf("O fatorial de %d eh %d ",n,fat);
    return 0;
}

// ------------------------------
// EXERCÍCIO 7 (fatorialRecursivo)
// Enunciado: Calcule o fatorial de um número usando recursão.
// Objetivo: treinar chamada recursiva e caso base.
// Função: int fatorialRecursivo(int n);
// ------------------------------
int fato(int f){
    if(f==1)return 2;
    else return f*fato(f-1);

}
int fatorialRecursivo(int n) {
    int num,fat=0;
    printf("Digite o num para o fat: ");
    scanf("%d",&num);
    fat = fato(num);
    printf("Fatorial de %d eh %d",num,fat);
    return 0;
}

// ------------------------------
// EXERCÍCIO 8 (contagemRegressiva)
// Enunciado: Faça uma função recursiva que receba um número e imprima uma contagem regressiva até 0.
// Objetivo: visualizar a pilha de chamadas.
// Função: void contagemRegressiva(int n);
// ------------------------------
int regressao(int num){
    if(num==0)return printf("0\n");
    else return printf("%d\n",regressao(num-1));
}
int contagemRegressiva() {
    int n;
    scanf("%d",&n);
    regressao(n);
}

// ------------------------------
// EXERCÍCIO 9 (maiorDeTres)
// Enunciado: Crie uma função que receba três inteiros e retorne o maior deles.
// Objetivo: treinar condicionais aninhadas.
// Função: int maiorDeTres(int a, int b, int c);
// ------------------------------
int maiorDeTres(int a) {
    int qnt;
    printf("Digite a quantidade de termos que deseja comparar: ");
    scanf("%d",&qnt);

    int num[qnt],maior=0;
    for(int i =0;i<qnt;i++){
        printf("Digite o %d termo: ",i+1);
        scanf("%d",&num[i]);
        maior=num[i];
        if(maior<num[i+1])maior=num[i+1];
    }
    return maior;
}
int maiorCWhile(int a){
    printf("Digite quantos numeros quiser e se quiser encerrar o ciclo digite -1");
    int num,i=1,maior=0;
        printf("Digite o %d termo: ",i);
        scanf("%d",&num);
    while(num==-1){
        if(maior<num)maior=num;
        i++;
        scanf("%d",&num);
    }
    return maior;
}
int menu(){
    printf("As duas opçoes serão executadas");
    int A = maiorDeTres(0);
    int B = maiorCWhile(0);
    printf("O maior de tremo do A eh %d",A);
    printf("O maniro termo de B eh %d",B);
}

// ------------------------------
// EXERCÍCIO 10 (somaRecursiva)
// Enunciado: Faça uma função recursiva que calcule a soma de 1 até n.
// Objetivo: recursão simples com retorno acumulado.
// Função: int somaRecursiva(int n);
// ------------------------------
int calculo(int num){
    if(num==1)return 1;
    else return num+calculo(num-1);
}
int somaRecursiva() {
    int num;
    scanf("%d",&num);
    printf("Caldulo da soma progressiva: %d",calculo(num));
    return 0;
}

// ------------------------------
// MAIN DE CONTROLE
// ------------------------------
int main() {
    int opcao;
    do {
        printf("\n=== MENU DE EXERCICIOS ===\n");
        printf("1 - Soma de dois numeros (somaDois)\n");
        printf("2 - Numero par ou impar (ehPar)\n");
        printf("3 - Tabuada (tabuada - for)\n");
        printf("4 - Soma de 1 ate n (somaAteN - while)\n");
        printf("5 - Menu simples (menuSimples - do while)\n");
        printf("6 - Fatorial iterativo (fatorialIterativo)\n");
        printf("7 - Fatorial recursivo (fatorialRecursivo)\n");
        printf("8 - Contagem regressiva recursiva (contagemRegressiva)\n");
        printf("9 - Maior de tres numeros (maiorDeTres)\n");
        printf("10 - Soma recursiva de 1 ate n (somaRecursiva)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: somaDois(0); break;
            case 2: ehPar(0); break;
            case 3: tabuada(0); break;
            case 4: somaAteN(0); break;
            case 5: menuSimples(); break;
            case 6: fatorialIterativo(0); break;
            case 7: fatorialRecursivo(0); break;
            case 8: contagemRegressiva(0); break;
            case 9: menu(); break;
            case 10: somaRecursiva(); break;
        }
    } while(opcao != 0);

    return 0;
}
