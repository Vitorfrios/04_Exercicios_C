#include <stdio.h>
#include <stdlib.h>

/*
# PROVA DE AEDS – FUNÇÕES E RECURSÃO (TOTAL: 20 PONTOS)

---

## QUESTÃO 03 — Análise de Função/Recursão (5 PONTOS)

**Tipo escolhido:** A – Função recursiva simples

**Enunciado:**
Analise a função abaixo, que retorna a soma dos números de 1 até `n`:

```c
int somaRecursiva(int n) {
    if (n == 1) return 1;
    return n + somaRecursiva(n - 1);
}
```

**Subitens:**

a) Qual é o **objetivo geral da função**?
b) Qual será o **resultado de `somaRecursiva(5)`**? Mostre passo a passo como a função calcula o resultado.
c) Explique o **caso base** e por que ele é essencial para a recursão.
d) Explique o **passo recursivo** e como os resultados parciais são combinados para formar o resultado final.

---

## QUESTÃO 04 — Implementação Completa em C (7 PONTOS)

**Tipo escolhido:** A – Sistema de processamento de dados sequenciais com validação

**Enunciado:**
Crie um programa que faça o seguinte:

1. Solicite ao usuário a quantidade `n` de números inteiros que deseja informar.
2. Armazene os números em um array.
3. Calcule e exiba a **média apenas dos números positivos**.
4. Caso o usuário informe um valor inválido (número não inteiro ou `n <= 0`), peça a entrada novamente.

**Exemplo de entrada e saída esperada:**

```
Quantos numeros deseja informar? 5
Digite o numero 1: 4
Digite o numero 2: -2
Digite o numero 3: 0
Digite o numero 4: 7
Digite o numero 5: 3
Media dos positivos: 4.6667
```



int q1(){
/*## QUESTÃO 01 — Correção de Código (4 PONTOS)

**Tipo escolhido:** B – Correção de erros de manipulação de estruturas e limites

**Enunciado:**
Analise o seguinte trecho de código que manipula um array de inteiros. O objetivo do programa é somar todos os elementos positivos do array.

```c
int somaPositivos(int arr[], int n) {
    int soma = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i] > 0) {
            soma += arr[i];
        }
    }
    return soma;
}
```

**Tarefas:**

1. Identifique os erros relacionados ao **acesso aos índices do array**.
2. Explique como esses erros podem causar comportamento incorreto ou travamentos.
3. Descreva alterações pontuais necessárias para corrigir o código mantendo a lógica.
4. Explique o resultado esperado após a correção, dado um array de 5 elementos positivos e negativos.

//correção de codigo
int somaPositivos(int arr[], int n) {
    int soma = 0;
    for (int i = 0//aqui eh zero pois se nao pula o primeiro indice do araay[0]/; i<n //aqui retira o = para percorrer todos do array e nao ultrapassar/; i++) {
        if (arr[i] > 0) {
            soma += arr[i];
        }
    }
    return soma;//retorna o valor da soma
}
}


int q2(){
    /*## QUESTÃO 02 — Conceitual (4 PONTOS)

    **Tipo escolhido:** C – Análise de código / problema prático

    **Enunciado:**
    Considere os seguintes trechos de código e responda:


    **Alternativa a)**
    Explique o que o seguinte trecho faz, detalhando cada passo do fluxo de execução:

    ```c
    int fatorial(int n//entra com o valor digitado anteriormente) {
        if (n == 0) return 1//caso base,se n ==0 retorna 1 ;
        return n * fatorial(n - 1);//n*chamada recursiva para n-1
        //o trecho indica o resolução do fatorial de um numero de forma recursiva
    }
    ```
    **Alternativa b)**
    Um aluno escreveu:

    ```c
    int fatorial(int n) {
        //aqui faltou o caso base representado no exercicio acima
        //if(n==0) return 1
        /faltou um else if// else if return n * fatorial(n - 1);
        else return 0// tratamnento para erro
    }
    ```

    Explique por que essa função não funciona corretamente, relacionando com o conceito de caso base em recursão.
    */
}

int q3(){

## QUESTÃO 03 — Análise de Função/Recursão (5 PONTOS)

**Tipo escolhido:** A – Função recursiva simples

**Enunciado:**
Analise a função abaixo, que retorna a soma dos números de 1 até `n`:

```c
int somaRecursiva(int n) {
    if (n == 1) return 1;
    return n + somaRecursiva(n - 1);
}
```

**Subitens:**

a) Qual é o **objetivo geral da função**?
    o objetivo da funçãi eh retornar a soma recursivamente de todos os numeros abaixo de n ate 1, ou seja de 1 ate n;
b) Qual será o **resultado de `somaRecursiva(5)`**? Mostre passo a passo como a função calcula o resultado.
    5+(4)
        4+(3)
            3+(2)
                2+(1)//caso base
                3
            5
        9
    14

c) Explique o **caso base** e por que ele é essencial para a recursão.
    o caso base é esencial para parar o "loop" da recusaão
d) Explique o **passo recursivo** e como os resultados parciais são combinados para formar o resultado final.
    o codigo aciona a recursão enquando nao entrar no caso base

---


}


int q4(){
## QUESTÃO 04 — Implementação Completa em C (7 PONTOS)

**Tipo escolhido:** A – Sistema de processamento de dados sequenciais com validação

**Enunciado:**
Crie um programa que faça o seguinte:

1. Solicite ao usuário a quantidade `n` de números inteiros que deseja informar.
2. Armazene os números em um array.
3. Calcule e exiba a **média apenas dos números positivos**.
4. Caso o usuário informe um valor inválido
(número não inteiro ou `n <= 0`), peça a entrada novamente.

**Exemplo de entrada e saída esperada:**

```
Quantos numeros deseja informar? 5
Digite o numero 1: 4
Digite o numero 2: -2
Digite o numero 3: 0
Digite o numero 4: 7
Digite o numero 5: 3
Media dos positivos: 4.6667
```

}
int main(){
    int qnt;
    printf("Digite a quantidade de numeros que deseja: ");
    scanf("%d",&qnt);

    int arr[qnt],soma=0;
    for(int i =0;i<qnt;i++){
        printf("Digite o %d numero: ",i+1);
        scanf("%d",&arr[i]);
        while(arr[i]>=0&& (int)arr[i]==arr[i]){
            scanf("%d",&arr[i]);
        }
        if(arr[i]>0)soma+=arr[i];
    }
    printf("A soma eh %.2f",(float)soma);
}

