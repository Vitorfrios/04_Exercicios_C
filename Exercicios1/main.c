#include <stdlib.h>
#include <stdio.h>

void ex1() {
    // Declare uma variável inteira e mostre na tela o endereço de memória que ela ocupa.
    int x;
    int *p=&x;
    printf(" %p\n",p);
    return 0;
}

void ex2() {
    // Crie duas variáveis (int e float) e exiba seus valores e endereços correspondentes.


    return 0;
}

void ex3() {
    // Declare um ponteiro para inteiro, associe-o a uma variável e use-o para alterar o valor original.
    int x=20;
    int *p=&x;
    *p=40;
    if(&x==p)printf("Igual");
    return 0;
}

int dobra(int *p){
   return *p*2;
}
void ex4() {
    // Faça um programa que receba um número e uma função que o dobre usando ponteiro como parâmetro.
    int num;
    scanf("%d",&num);
    printf("%d\n",dobra(&num));

    return 0;
}

void ex5() {
    // Declare um ponteiro e um ponteiro para ponteiro, e mostre o valor, o endereço e o conteúdo de cada um.
    int x=30;
    int *p=&x;
    int **d=&p;
    printf("conteudo: %d %d \n edereco: %p %p \n,",*p,**d,p,d);
    return 0;
}

void ex6() {
    // Mostre como o valor de uma variável muda ao alterar um ponteiro de ponteiro que a referencia.
    int x=0;
    int *p=&x;
    int **d=&p;
    **d=40;
    printf("%d",x);
    return 0;
}

void ex7() {
    // Crie um ponteiro para inteiro e use malloc para alocar espaço na memória; depois atribua e mostre o valor.
    int x=2;
    int *p=malloc(x*sizeof(int));
    *(p+1)=40;
    *(p+2)=30;
    printf("%d",*(p+2));
    return 0;
}

void ex8() {
    // Use malloc e free para criar e liberar dinamicamente uma variável float.
    float *p=malloc(sizeof(float));
    *p=39;
    printf("%.2f",*p);
    free(p);
    return 0;
}

void ex9() {
    // Crie um vetor de 5 inteiros dinamicamente e preencha seus valores por meio de aritmética de ponteiros.
    int *p=malloc(5*sizeof(int));
    for(int i = 0;i<5;i++){
        printf("Digite o %d numero: ",i+1);
        scanf("%d",(p+i));
    }
    for(int i = 0;i<5;i++){
        printf(" %d ,",*(p+i));
    }
    free(p);
    return 0;
}

void ex10() {
    // Altere o tamanho de um vetor dinâmico usando realloc e mostre o novo conteúdo.
    int *p=malloc(2*sizeof(int));

    for(int i = 0;i<2;i++){
        *(p+i)=i*i+10;
    }
    p=realloc(p,3*sizeof(int));
    *(p+2)=22;
    for(int i = 0;i<3;i++){
        printf(" %d ,",*(p+i));
    }
    free(p);
    return 0;
}

int *dobro(int *d, int v){
    int *neww=malloc(v*sizeof(int));
    for(int i =0;i<v;i++){
        *(neww+i)= *(d+i)*2;
    }
    return neww;
}
void ex11() {
    // Crie uma função que receba um ponteiro e devolva outro ponteiro que armazene o dobro do valor original.
    int v=10;
    int *p=malloc(v*sizeof(int));
    for(int i =0;i<v;i++){
        *(p+i)=i+10*i+v;
    }
    int *dobrado = dobro(p,v);
    printf("Original | Dobrado\n");

    for(int i=0;i<v;i++){

        printf("   %3d   |   %3d\n", *(p + i), *(dobrado + i));

    }
    free(p);
    free(dobrado);
    return 0;
}



int *vetor(int *vet,int num){
    for(int i =0;i<num;i++){
        *(vet+i)= i*num+10;
    }
    return vet;
}
void ex12() {
    // Desenvolva uma função que aloque um vetor e retorne o ponteiro para ele.
    int num=9;
    int *p=malloc(num*sizeof(int));
    int *retorno=vetor(p,num);
    return 0;
}




void ex13() {
    // Crie um sistema simples que simule a reserva de blocos de memória (malloc) e mostre o uso de cada um.
    return 0;
}

void ex14() {
    // Simule a liberação de memória com free, mostrando mensagens de alocação e liberação de blocos.
    return 0;
}

void ex15() {
    // Faça um programa que use ponteiros para percorrer um vetor e inverter sua ordem.
    int *p=malloc(3*sizeof(int));
    int *r=malloc(3*sizeof(int));
    for(int i =0;i<3;i++){
        *(p+i)=i*3+10*i;
        *(r+i)=*(p+(2-i));
    }
    for(int i=0;i<3;i++){

        printf("   %3d   |   %3d\n", *(p + i), *(r + i));

    }
    return 0;
}

void ex16() {
    // Utilize ponteiros para trocar os valores de duas variáveis sem usar uma variável auxiliar.
    return 0;
}

void ex17() {
    // Crie uma função que receba o tamanho de um bloco e devolva um ponteiro para uma área de memória alocada, exibindo o endereço inicial.
    return 0;
}

void ex18() {
    // Implemente um mini gerenciador de memória que aloque, realoque e libere blocos conforme comandos do usuário.
    return 0;
}


int main(){
    int num;
    printf("Escolha o numero do exercicio (0 para sair): ");
    scanf("%d", &num);

    int (*exercicios[30])()={ex1,ex2,ex3,ex4,ex5,ex6,ex7,ex8,ex9,ex10,ex11,ex12,ex13,ex14,ex15,ex16,ex17,ex18,NULL};

    while (num!=0) {

        if (num > 0 && num <= 30 && exercicios[num - 1] != NULL) {
            exercicios[num - 1]();
        } else {
            printf("Exercicio %d nao existe.\n", num);
        }
        printf("\nEscolha o numero do exercicio (0 para sair): ");
        scanf("%d", &num);

    }
    return 0;
}
