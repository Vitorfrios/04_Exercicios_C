#include <stdio.h>
#include <stdlib.h>

Perfeito, Vitor! Vamos montar uma **Prova C** com nível **mais difícil**, mantendo a matéria até **recursão**, e seguindo exatamente os critérios que você falou:

* **Implementação Completa em C**: mais desafiadora, exigindo pensar em estruturas específicas (while, for, do-while) ou passagem de funções como parâmetro.
* **Correção de Código**: sem revelar o objetivo da função ou o resultado esperado, deixando os alunos pensarem e analisarem o código.
* **Questões Conceituais e Recursão**: também com nível elevado, pedindo raciocínio aprofundado.
* **8 questões no total**, 2 de cada tipo.

---

# PROVA DE AEDS – FUNÇÕES E RECURSÃO (TOTAL: 20 PONTOS) – PROVA C

---

## QUESTÃO 01 — Correção de Código (4 PONTOS) — Tipo B

```c
int computa(int n){
    int resultado = 1;
    for(int i = 0; i < n; i++){
        resultado = resultado + i;
    }
    if(n = 0){
        resultado = 0;
    }
    return resultado;
}
```

* Identifique os erros presentes no código e explique como corrigi-los.
* Não há informação sobre o objetivo ou resultado esperado.

---

## QUESTÃO 02 — Implementação Completa em C (7 PONTOS) — Tipo C

Desenvolva um programa que leia **uma sequência indefinida de números inteiros** até que o usuário digite `-1`.

Requisitos:

* Calcular e imprimir o **maior número par** e o **menor número ímpar** digitados.
* Utilize obrigatoriamente um **loop do-while** para entrada de dados.
* Crie **funções auxiliares** que recebam os números como parâmetro para atualizar os valores do maior par e menor ímpar.
* Caso não existam números pares ou ímpares, informe adequadamente.

---

## QUESTÃO 03 — Análise de Função/Recursão (5 PONTOS) — Tipo B

Analise a função:

```c
int potRec(int base, int expo){
    if(expo == 0) return 1;
    return base * potRec(base, expo-1);
}
```

a) Qual é o resultado de `potRec(2,4)`?
b) Explique detalhadamente o **caso base** e o **passo recursivo**.
c) Descreva a sequência completa de chamadas para `potRec(3,2)`.
d) Como o resultado seria alterado se o caso base fosse `if(expo == 1) return base;`?

---

## QUESTÃO 04 — Conceitual em formato de código (4 PONTOS) — Tipo A

a) Explique o que significa **modularização** em C e quais são as vantagens de dividir um programa em funções menores.

b) Em recursão, qual é a diferença entre **recursão direta** e **recursão múltipla**? Dê exemplos conceituais.

---

## QUESTÃO 05 — Implementação Completa em C (7 PONTOS) — Tipo A

Crie um programa que:

* Receba **5 números inteiros positivos** e imprima a soma dos **números primos** digitados.
* Utilize obrigatoriamente um **loop for** para percorrer os números e uma **função para verificar se cada número é primo**, recebendo o número como parâmetro.
* Não use vetores; trabalhe apenas com variáveis individuais e parâmetros de função.
* Se nenhum número primo for digitado, informe “Nenhum primo encontrado”.

---

## QUESTÃO 06 — Correção de Código (4 PONTOS) — Tipo C

```c
int sequencia(int n){
    if(n < 1) return n;
    int total = 0;
    for(int i = 0; i <= n; i++);
        total = total + i;
    return total;
}
```

* O código possui problemas de lógica e sintaxe.
* Identifique os erros e explique como corrigi-los.

---

## QUESTÃO 07 — Conceitual em formato de código (4 PONTOS) — Tipo B

a) O que é **passagem de parâmetros por valor** e como ela afeta o comportamento de uma função?

b) Em que situação **passagem de parâmetros por referência** (ou equivalente em C, usando ponteiros) seria indispensável?

---

## QUESTÃO 08 — Análise de Função/Recursão (5 PONTOS) — Tipo C

Analise a função:

```c
int seq(int n){
    if(n <= 1) return 1;
    return seq(n-1) + seq(n-2);
}
```

a) Qual é a sequência gerada para `n = 5`?
b) Explique detalhadamente a **sequência de chamadas recursivas**.
c) O que aconteceria se o primeiro caso base fosse `if(n < 1) return 0;`?
d) Por que essa função pode se tornar muito lenta para valores maiores de `n`?

---

✅ Total: 20 pontos

---

Se você quiser, Vitor, posso já **gerar a Prova D** com **nível ainda mais pesado**, deixando as implementações completas exigirem **combinações de loops e recursão**, e questões de correção **com mais de 1 erro sutil interligado**.

Quer que eu faça isso agora?

