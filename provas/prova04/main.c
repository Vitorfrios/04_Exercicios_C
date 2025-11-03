## QUESTÃO 01 — Análise de Função/Recursão (5 PONTOS) — Tipo C

Analise a função abaixo e responda às questões:

```c
int calcula(int a, int b){
    if(a == 0) return b;
    if(b == 0) return a;
    return calcula(a-1, b) + calcula(a, b-1);
}
```

a) Explique a lógica geral da função.
	A função recursiva está retornando a soma de a-1,b +a,b-1, a cada chamada ele calcula esse programa, e como tem "duas" recursões o codigo so para quando as duas atingirem o caso base
b) Qual é o resultado retornado para a chamada `calcula(2,1)`? 4
c) Descreva a sequência de chamadas recursivas realizadas para `calcula(2,1)`.
	(2,1)+(2,1)
		(1,1)+(1,1)+(2,0)//base
			(0,1)//base+(1,0)//base+2
			1+1+2=4
d) Como o resultado final seria alterado se o primeiro caso base fosse `if(a == 0) return 0;`?
	O resultado seria 3 e no caso base retornaria 0 e nao b
	(2,1)+(2,1)
		(1,1)+(1,1)+(2,0)//base
			(0,1)//base+(1,0)//base+2
			0+1+2=3

---

## QUESTÃO 02 — Correção de Código (4 PONTOS) — Tipo A

O algoritmo abaixo deveria calcular a soma dos dígitos de um número inteiro positivo. No entanto, contém erros sutis de fluxo e estado.

```c
int somaDigitos(int n){
    int soma = 0;
    while(n > 0){
        soma = soma + n % 10;
        n = n / 9;
    }
    return soma;
}
```

O comportamento esperado é:

* Para a entrada `n = 572`, o resultado deve ser `14`.

Identifique e corrija os erros para que o programa funcione conforme esperado.
Escreva a correção abaixo:

int somaDigitos(int n){
    int soma = 0;
    while(n > 0){
        soma += n % 10;
        n /= 10;
    }
    return soma;
}
---
## QUESTÃO 04 — Conceitual em formato de código (4 PONTOS) — Tipo B

a) Explique conceitualmente a diferença entre **parâmetros por valor** e **parâmetros por referência** em C, e em que situações cada um é mais adequado.
	Parametros por valor eh o formato em que se é utilizado em outras funções, parametro spor referencia eh usado apenas na função em questão.
b) Em funções recursivas, qual é a importância do **caso base** e o que pode ocorrer se ele for definido de forma incorreta?
	O caso base é fundamental para identificar ate onde a recursão vai, se ele nao existisse a recursão iria percorrer infinitamente, ocupando muita memoria.
---

## QUESTÃO 05 — Análise de Função/Recursão (5 PONTOS) — Tipo A

Considere a função:

```c
int funcao(int n){
    if(n == 0) return 0;
    return n + funcao(n-1);
}
```

a) Qual é o objetivo geral da função?
	O objetivo da função recursiva eh somar n + funcao(n-1), ou seja a cada chamada ele diminui o n em 1 e para quando n for 0.
b) Qual o resultado da chamada `funcao(5)`? 15
c) Explique detalhadamente o papel do caso base.
	O caso base é fundamental para identificar ate onde a recursão vai, se ele nao existisse a recursão iria percorrer infinitamente, ocupando muita memoria.Ao atingir n ==0 ele retorna 0 como valor base encerrando a recursão e voltando somando.
d) Mostre a sequência de chamadas recursivas para a entrada `n = 3`.
	3+(2)
		2+(1)
			1+(0)//caso base retorna 0
			1+0
		2+1
	3+3
	6
---
## QUESTÃO 06 — Correção de Código (4 PONTOS) — Tipo C

O algoritmo abaixo deveria inverter o sinal de todos os números digitados até que o valor `0` fosse inserido, mas contém erros lógicos de transformação.

```c
int main(){
    int x;
    do{
        scanf("%d", &x);
        if(x != 0);
            printf("%d\n", x * -1);
    }while(x > 0);
    return 0;
}
```

Para a sequência de entrada `5 7 -2 0`, a saída correta esperada é `-5 -7 2`.
Identifique e corrija os erros necessários.
Escreva a correção abaixo:
int main(){
    int x;
    do{
        scanf("%d", &x);
        printf("%d\n", x * -1);
    }while(x != 0);
    return 0;
}
---
## QUESTÃO 07 — Conceitual em formato de código (4 PONTOS) — Tipo C

Analise os trechos abaixo:

a)

```c
int f1(int n){
    if(n <= 1) return 1;
    return f1(n-1) + f1(n-1);
}
```

Qual é o resultado de `f1(3)`? Explique o motivo.
	  (2)  +  (2)
	(1)+(1)+(1)+(1)
	       4
b)

```c
int f2(int n){
    if(n == 0) return 1;
    return n * f2(n-1);
}
```

Qual é a função matemática representada por `f2`?
	A função eh o fatorial.
---
/*

## QUESTÃO 03 — Implementação Completa em C (7 PONTOS) — Tipo B

Implemente um programa que receba repetidamente números inteiros positivos fornecidos pelo usuário até que seja digitado `-1`.

Requisitos:

* O programa deve contar quantos números pares e quantos números ímpares foram digitados.
* Após o término da entrada, o programa deve imprimir:

  * Quantidade de pares.
  * Quantidade de ímpares.
  * A porcentagem de números pares em relação ao total.
* Deve ser considerado o caso especial de nenhum número ter sido digitado (exceto o `-1`).

Exemplo:

```
Entrada: 4 7 10 13 -1
Saída: Pares: 2, Ímpares: 2, Porcentagem de pares: 50%
```
*/
int main(){
    int num,pares=0,impar=0;
    printf("Digite um numero: ");
    scanf("%d",num);
    while(num!=-1){
        if(num%2==0)pares++;
        else impar++;
        PRINTF("Digite o proximo numero: ");
        scanf("%d",num);
    }
    if(pares>0&&impar>0){
        if(pares>0)printf("A quantidade de pares eh %d\n",pares);
        if(impar>0)printf("A quantidade de impares eh %d\n",impar);
        printf("A porcentagem dos numeros pares eh %d%%\n",((float)(pares/(pares+impar)))*100.0);

    } else printf("Nenhum numero alem de -1 foi digitado");



}
/*
---

## QUESTÃO 08 — Implementação Completa em C (7 PONTOS) — Tipo A

Desenvolva um programa que leia uma quantidade fixa de 5 números inteiros positivos e calcule a média aritmética deles.

Requisitos:

* Caso algum número negativo seja digitado, deve ser solicitado novamente até que seja fornecido um valor válido.
* Ao final, o programa deve exibir a média calculada.

Exemplo:

```
Entrada: 5 8 -2 7 10 4
Saída: Média = 6.8
```

*/
int main(){

    int n,soma=0,nmrs=0;
    for(int i =1;i<=5;i++){
        printf("Digite um valor inteiro nao negativo: ");
        scanf("%d",&n);
        while(n<0){
            printf("Digite um valor positivo: ");
            scanf("%d",&n);
        }
        soma+=n;
        nmrs++;

    }
    printf("%d",soma);
    return 0;
}
