#include <stdio.h>
#include <stdlib.h>
/*EX 1 – Vetor (int*)
Ler n.
Alocar vetor dinâmico com malloc.
Ler n valores pelo ponteiro.
Função deve retornar o MAIOR valor.
Na main imprimir o maior e liberar a memória.
Protótipo: int maior(int *v, int n)
*/
int mV(int vet[],int n){
    int m= vet[0];
    for(int i =0; i<n;i++){
        if(vet[i]>m){m=vet[i];}
    }
    return m;
}
int ex1(){
    int qnt;
    scanf("%d", &qnt);
    int *n = malloc(qnt*sizeof(int));
    for(int i=0; i<qnt;i++)scanf("%d",&n[i]);
    printf("%d", mV(n,qnt));

}

/*
EX 2 – Vetor (int*)
Ler n.
Vetor dinâmico.
Função deve contar quantos números pares existem e retornar.
Protótipo: int contaPares(int *v, int n)
*/
int contagem(int val[],int qnt){
    int n=0;
    for(int i=0; i<qnt;i++){
        if(val[i]%2==0)n++;
    }
    return n;
}
int ex2(){
    int *num = malloc(5*sizeof(int));
    for(int i =0;i<5;i++){
        scanf("%d",&num[i]);
    }
    printf("%d",contagem(num,5));

}


/*
EX 3 – Vetor (int*)
Função recebe int *v e int n.
Calcular soma e média (somente com ponteiros, sem v[i]).
Main imprime soma e média.
Memória liberada no final.
*/
void somamedia(int v[],int n){
    int soma=0;

    for(int i =0;i<n;i++){
        soma += *(v+i);
    }
    printf("%d\n",soma);
    printf("%.2f\n",(float)soma/n);
}
int ex3(){
    int *v=malloc(4*sizeof(int));
    for(int i=0;i<4;i++){
        scanf("%d",(v+i));
    }
    somamedia(v,4);
    free(v);
    return 0;
}


/*
EX 4 – Matriz Forma 1 (int*)
Ler lin e col.
Alocar matriz com int m usando malloc(lincolsizeof(int)).
Preencher com fórmula (icol+j).
Imprimir como tabela.
Liberar memória.
Protótipo: void imprime(int *m, int lin, int col)
*/
void table(int *m,int lin,int col){
    for(int i =0;i<lin;i++){
        for(int j=0;j<col;j++){
            printf("%3d | ",*(m+i*col+j));
        }
        printf("\n");
    }

}
int ex4(){
    int lin,col;
    scanf("%d%d",&lin,&col);
    int *m = malloc(lin*col*sizeof(int));
    for(int i = 0;i<lin;i++){
        for(int j = 0;j<col;j++){
            *(m+i*col+j)=i*col+j+1;
        }
    }
    table(m,lin,col);
    free(m);
    return 0;
}


/*EX 5 – Matriz Forma 1 (int*)
Ler n (matriz quadrada).
Alocar com int* (bloco único).
Ler todos os valores do teclado.
Calcular e retornar soma da diagonal principal.
Protótipo: int diagonal(int *m, int n)*/
void table2(int *matriz, int n){
    for(int i =0;i<n;i++){
        for(int j=0; j<n;j++){
            printf("%3d | ",matriz[i*n+j]);
        }
        printf("\n");
    }

}
int diagonal(int *m, int n){
    int soma=0;
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(i==j)soma+=m[i*n+j];
        }
    }
    return soma;
}
int ex5(){
    int tam;
    scanf("%d",&tam);
    int *mat=malloc(tam*tam*sizeof(int));
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            *(mat+i*tam+j)=i*tam+j+1;
        }
    }
    printf("%d",diagonal(mat,tam));
    table2(mat,tam);
    free(mat);
    return 0;
}


int main(){
    int select;
    printf("Selecione o exercicio ");
    scanf("%d",&select);
    switch(select){
    case 1:
        ex1();
        break;
    case 2:
        ex2();
        break;
    case 3:
        ex3();
        break;
    case 4:
        ex4();
        break;
    case 5:
        ex5();
        break;
    }
}

/*

EX 6 – Matriz Forma 2 (int**)
Ler lin e col.
Alocar com ponteiro duplo:
int m = malloc(linsizeof(int));
e malloc para cada linha.
Preencher valores do usuário .
Imprimir em formato de tabela.
Liberar linha por linha e depois m.
Protótipo: int criaMatriz(int lin, int col)

EX 7 – Matriz Forma 2 (int**)
Função recebe int **m, int lin, int col e um valor x.
Procurar x na matriz.
Se encontrar, retornar 1.
Se não, retornar 0.
Protótipo: int busca(int **m, int lin, int col, int x)

EX 8 – String (char*)
Ler tamanho da string.
Alocar com malloc.
Ler string com scanf.
Função deve contar e retornar número de vogais.
Protótipo: int vogais(char *s)

EX 9 – String (char*)
Ler duas strings dinâmicas.
Criar terceira com malloc do tamanho necessário.
Concatenar manualmente (sem strcat).
Imprimir no final e liberar as 3.
Protótipo: void concat(char *dest, char *src)

EX 10 – Arquivo + Vetor dinâmico
Ler n.
Vetor dinâmico com n inteiros digitados pelo usuário.
Salvar todos em arquivo “dados.txt” com fprintf.
Protótipo: void grava(int *v, int n)

EX 11 – Arquivo + malloc
Abrir “dados.txt”.
Descobrir quantos valores tem.
Alocar um vetor do tamanho certo com malloc.
Ler todos com fscanf até EOF.
Imprimir e liberar.
Protótipo: int* carrega(int *n) // n passado por ponteiro deve receber a quantidade lida*/
