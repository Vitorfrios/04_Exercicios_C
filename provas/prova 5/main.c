--- 80%

## QUESTÃO 02 — Correção de Código (4 PONTOS) — Tipo B

O programa abaixo deve calcular a média de três números inteiros, mas contém erros sutis:

```c
int main(){
    int a, b, c;
    scanf("%d %d %d", a, b, c);
    int media = (a + b + c) / 2;
    printf("Media = %d\n", media);
    return 0;
}
```

Com entrada `4 6 8`, a saída correta deve ser `6`.
Identifique e corrija os erros de forma pontual.
Escreva a correção aqui:
int main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);//faltou &
    float media = (a + b + c) / 2;
    printf("Media = %.2f\n", media);
    return 0;
}
---

## QUESTÃO 03 — Conceitual em formato de código (4 PONTOS) — Tipo A

a) Em C, explique a diferença entre **funções que retornam valor** e **funções que não retornam valor**.
	Funções que retornam valor (mais comuns int e float), podem ser utilizadas como variaveis para outras partes do programa,ou seja, podem ser reutilizadas.
	Funções que nao retornam valor(void), são utilizadas apenas para exibir algo, na maioria das vezes terminando somente com printf.
b) Para uma função recursiva que calcula a soma de `n` números inteiros positivos, por que é importante definir corretamente o **caso base**?
	O caso base eh importante para que a recursão nao ocorra infinitamente, tendo um caso base, a recursão para e "volta" retornando o valor do caso base.
---

## QUESTÃO 04 — Análise de Função/Recursão (5 PONTOS) — Tipo B

Considere a função:

```c
int multRec(int a, int b){
    if(b == 0) return 0;
    return a + multRec(a, b-1);
}
```

a) Qual é o objetivo da função?
	O objetivo da função eh em cada recursão somar a + a " queda de b" ate atingir o caso base b==0 retornando 0.
b) Qual é o resultado de `multRec(3,4)`? 16
c) Descreva passo a passo a sequência de chamadas recursivas.
	4+multRec(4,3)
	|	4+multRec(4,2)
	|	|	4+multRec(4,1)
	|	|	|	4+multRec(4,0)//aqui atinge o caso base e retorna 0
	|	|	|	4+0=4
	|	|	4+4=8
	|	8+4=12
	4+12=16
d) Como o resultado seria alterado se `if(b == 0) return 0;` fosse `if(a == 0) return 0;`?
	A recursão iria ocorrer infinitamente, pois o caso base nao se relaciona com a recursão, ja que quem deminui é b e nao a.
---

## QUESTÃO 05 — Correção de Código (4 PONTOS) — Tipo C

O algoritmo abaixo deveria calcular o fatorial de um número, mas apresenta erros:

```c
int fatorial(int n){
    if(n = 0) return 1;
    return n * fatorial(n);
}
```

Para `n = 5`, o resultado esperado é `120`.
Identifique e corrija os erros de forma pontual.
Escreva a correção abaixo:
int fatorial(int n){
    if(n == 0||n==1) return 1;
    return n * fatorial(n-1);
}
---

## QUESTÃO 07 — Análise de Função/Recursão (5 PONTOS) — Tipo C

Analise a função:

```c
int seqFib(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return seqFib(n-1) + seqFib(n-2);
}
```

a) Qual é o objetivo da função?
	A função está representando recursivamente um numero da sequencia de fibonattci.A função retorna uma dupla chamada de função, onde o caso base só ira ser valido quando as duas atingirem o caso base.
b) Qual é o resultado de `seqFib(5)`?5

c) Descreva a sequência de chamadas recursivas para `seqFib(4)`
			seqFib(4)=3
        seqFib(3)=2    +	  seqFib(2)=//retorna 1
   seqFib(2)=1 + seqFib(1)=//retorna 1
seqFib(1)=//retorna 1 + seqFib(0)=//retorna 0

d) O que aconteceria se removêssemos o caso `if(n == 0) return 0;`?
	A recursão iria ocorrer infinitamente, pois o n chegaria a 0 em uma das chamadas mas nao retornaria nada.
---

QUESTÃO 08 — Conceitual em formato de código (4 PONTOS) — Tipo C (SEM PONTEIROS)

Analise o código abaixo:

void troca(int x, int y){
    int temp = x;
    x = y;
    y = temp;
}


a) Explique por que os valores das variáveis externas não são alterados ao chamar esta função.
	Não são alterados, pois a função nao retorna nada.
b) Como seria possível alterar os valores de duas variáveis externas sem usar ponteiros?
	Trocando de void para int ou float, inserindo as duas em um array[] e retornando ele.
---

## QUESTÃO 06 — Implementação Completa em C (7 PONTOS) — Tipo A

Desenvolva um programa que leia **5 números inteiros positivos** e determine:

* O maior e o menor número da lista.
* A média aritmética dos 5 números.

Regras:

* Caso algum número negativo seja digitado, deve ser solicitado novamente.
* Ao final, exibir os três resultados de forma clara.

Exemplo:

```
Entrada: 3 8 7 -2 5 10
Saída: Maior: 10, Menor: 3, Média: 6.6
```
void maior(int lists[]){
	int maior = lists[0];
	for(int i =1;i<5;i++){
		if(maior<lists[i])maior=lists[i];
	} prinf("O maior termo eh %d\n",maior);
}
void menor(int lista[]){
	int menor=lista[0];
	for(int i =1;i<5;i++){
		if(menor>lista[i])menor=lista[i];
	} prinf("O menor termo eh %d\n",menor);
}
int main(){
	int num[5];
	float soma=0;
	for(int i =0;i<5;i++){
		printf("Digite um numero: ");
		scanf("%d",&num[i]);
		while(num<0){
			printf("Digite um numero positivo: );
			scanf("%d",&num[i]);}
		soma+=num[i];
	}
	maior(num);
	menor(num);
	printf("A media aritimetica dos 5 termos eh %.2f",soma/5);
	return 0;
}
---

## QUESTÃO 01 — Implementação Completa em C (7 PONTOS) — Tipo B

Crie um programa que receba números inteiros positivos do usuário até que ele digite `0`.

Requisitos:

* Para cada número digitado, indique se ele é múltiplo de 3 ou não.
* Ao final, mostre a soma de todos os números múltiplos de 3 digitados.
* Caso nenhum número múltiplo de 3 tenha sido digitado, informe “Nenhum múltiplo de 3 fornecido”.

Exemplo:

```
Entrada: 4 9 12 5 0
Saída: 4 não é múltiplo de 3
       9 é múltiplo de 3
       12 é múltiplo de 3
       5 não é múltiplo de 3
       Soma dos múltiplos de 3: 21
```

---
int main(){
	int num,soma=0;
	printf("Digite um numero");
	scanf("%d",&num);
	while(num!=0){
		if(num%3==0){
			printf("%d eh multiplo de 3",num);
			soma+=num;}
		else printf("%d nao eh multiplo de 3",num);
		printf("Digite o proximo numero: ");
		scanf("%d",&num);
	}
	if(soma<0)printf("Nao teve nehum numero multiplo de 3");
	else printf("Soma dos multiplos de 3: %d",soma);
	return 0;
}
