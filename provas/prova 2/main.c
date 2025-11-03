#include <stdio.h>
#include <stdlib.h>

int Q1()
{
/* PROVA DE AEDS (TOTAL: 25 PONTOS)

QUESTÃO 01 (4 PONTOS) — Correção de Código
Enunciado:
O código abaixo deveria calcular a soma de todos os números pares de 1 até N, mas contém erros. Corrija o código para que funcione corretamente.

int N, i, soma;
soma = 1;
printf("Digite o valor de N: ");
scanf("%d", N);
for(i = 1; i <= N; i--){
    if(i % 2 = 0){
        soma + i;
    }
}
printf("A soma dos pares é: %d", soma);

Objetivo:
- Corrigir erros de inicialização, incremento/decremento, operadores e entrada/saída.
- Garantir que o programa some corretamente todos os números pares de 1 até N.
*/
    int N, i, soma = 0;//valor alterado para soma =0
    printf("Digite o valor de N: ");
    scanf("%d", &N);//faltou  colocar o & para indicar qual variavel
    for(i = 1; i <= N; i++){ // aumento e nao diminuição
        if(i % 2 == 0){ //adicionar o == para comparador e nao definição de variavel
            soma +=i; //retirade de somente soma +i  para soma+= i
        }
    }
    printf("A soma dos pares é: %d", soma);
}


int Q2(){
/*
QUESTÃO 02 (4 PONTOS) — Conceitual
a) Explique a diferença entre passagem de parâmetros por valor e por referência em funções.
    Passagens de parametros por valor sempre retorna alguma coisa para a main,podendo ser usada para outros fatores no programa, ja a referencia nem sempre retorna algo, usada apenas para mostrar o resultado da função.
b) O que é modularização e por que ela é importante no desenvolvimento de programas grandes?
    A modularização é fundamental para programas grandes, pois além de ela poder ser reutilizada em qualquer parte do programa, ela consegue deixar a identação do codigo mais limpa "clean code".
*/

}

int Q3(){
 /*QUESTÃO 03 (5 PONTOS) — Análise de Função/Recursão
Função fornecida:
int fatorial(int n){
    if(n == 0){
        return 1;
    } else {
        return n * fatorial(n - 1);
    }
}

Perguntas:
a) Qual é o objetivo da função fatorial?
    O objetivo da ufnção é retornar a multiplicação dos numeros anteriores a ele ex 5! = 5*4*3*2 = 120. Quando o numero n for zero ele retoan 1 que se refere ao caso base, a partir disso a recursão "volta" calculando o fatorial correto.
b) Calcule fatorial(3) passo a passo, mostrando as chamadas recursivas.
    return 3 * fatorial(2)
        return 2 * fatorial(1)
            return 1 *fatorial(0)//caso base q é igual a 1
            1*1
        2*1
    3*2 = 6
c) Calcule fatorial(5) e explique como a pilha de chamadas se comporta.
    return 5 * fatorial(4)//chama o n =5 e subtrai para o proximo termo ==4
        return 4 * fatorial(3) // chama n = 4 e subtrai para o proximo termo == 3
            return 3 * fatorial(2) // chama n = 3 e subtrei o proximo == 2
                return 2 * fatorial(1)//chama n =2 e sbtrai == 1
                    return 1 * fatorial(0)// chega no caso base == 1
                    1*1
                2*1
            3*2
        4*6
    5*24
    120
*/
}

int media(int n; float val[]){
    if(n==0) return val[0];
    else return (val[n-1] + media(n-1,val))/n;
}
void maior(int n; float valor[n]){
    float mais =0;
    for(int i = 0;i<n;i++){
        if (mais<valor[i])mais=valor[i];
    }

}
void menor(int n; float valores[n]){
    float menos = 0;
    for(int i = 0;i<n;i++){
        menos = valores[i]
        if(menos>valores[i+1]) menos=valores[i];
        else menos = menos;
    }
}
void menu(){
    printf("Menu:");
    printf("1. Mostrar o maior número");
    printf("2. Mostrar o menor número");
    printf("3. Calcular a média");
    printf("4. Sair");
}
int Q4(){
/*QUESTÃO 04 (7 PONTOS) — Implementação Completa em C
Enunciado:
Crie um programa que:
1. Leia N números inteiros.
2. Apresente um menu com as opções:
   1. Mostrar o maior número
   2. Mostrar o menor número
   3. Calcular a média
   4. Sair

Regras:
- Cada opção deve ser implementada em uma função/procedimento separado.
- Se o usuário digitar uma opção inválida, o programa deve mostrar uma mensagem de erro e voltar ao menu.
- O programa só termina quando o usuário escolher a opção “Sair”.

Exemplo de fluxo:
Digite a quantidade de números: 5
Digite os números: 10 20 5 7 15

Menu:
1. Maior número
2. Menor número
3. Média
4. Sair
Escolha a opção: 1
O maior número é 20

Menu:
...
*/
    int n, escolha, flag=false;
    printf("Digite a quantidade de termos: ");
    scanf("%d",&n);
    float array[n];
    for (int i =0;i<n;i++){
        printf("Digite o %d termo: ",i+1);
        scanf("%f",&array[i]);
    }
    while(flag){
        menu();
        printf("Escolha a opção: ");
        scanf("%d",&escolha);
        if(escolha>=1 && escolha<=3){
            switch(escolha){
                case 1:
                    printf("O maior numero eh %d ",maior(n,array));
                    break;
                case 2:
                    printf("O menor termo eh %d ",menor(n,array));
                    break;
                case 3:
                    printf("A media dos termos são %d ",media(n,array));
                    break;
            }
        }
        else if (escolha==4)flag=true;
        else flag = false;
    }
}



int Q5(){/*
QUESTÃO 05 (5 PONTOS) — Recursão Avançada
Enunciado:
Analise a função abaixo que calcula a soma de todos os elementos de um array de tamanho N de forma recursiva:

int somaArray(int arr[], int N){
    if(N == 0){
        return 0;
    } else {
        return arr[N-1] + somaArray(arr, N-1);
    }
}

Perguntas:
a) Explique como a recursão funciona neste caso (ida e volta).
    Arecursão irá percorrer todos os numeros do array ate encontrar o caso base que é n == 0 e retornará 0, o que fará o caminho de volta somando todos os numeros que ela percorreu ate o n == 0.
b) Calcule somaArray([2, 4, 6], 3) passo a passo, mostrando cada chamada e retorno.
    return arr[2] (6) + somaArray(arr,2)
        return arr[1] (4) + somaArray(arr,1)
            return arr[0] (2) + somaArray(arr,0//casobase retorna 0)
            return 2 +0
        return 4+2
    return 6+6
    return 12
c) Quais cuidados devem ser tomados para evitar erros em funções recursivas que processam arrays?
    os cuidados são, sempre deve existir o caso base para a recusão poder "voltar" calculando, a posição do primeiro numero do array é "0" e nao "1".
*/
}

