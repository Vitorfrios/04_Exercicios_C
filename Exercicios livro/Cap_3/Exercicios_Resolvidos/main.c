#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float Pnumero(char mensagem[]){
    float valor;
    printf("%s",mensagem);
    scanf("%f",&valor);
    return valor;

}


int ex1(){
    //1. Receba quatro números inteiros, calcule e mostre a soma.
    int qnt = Pnumero("Digite quantos valores deseja: ");
    int soma = 0;
    int valores[qnt];
    char mensagem[50];

    for (int i=0; i < qnt; i++){
        sprintf(mensagem,"Digite o %d numero: ",i+1);
        valores[i]=Pnumero(mensagem);
        soma += valores[i];

    }
    printf("A soma dos valores é %d",soma);
    return 0;
}

int ex2(){
//2. Receba três notas, calcule e mostre a média aritmética.
    int qnt = Pnumero("Digite quantos valores deseja: ");
    float soma = 0;
    float valores[qnt];
    char mensagem[50];

    for (int i = 0; i <qnt; i++){
        sprintf(mensagem,"Digite o %d numero: ",i+1);
        valores[i]=Pnumero(mensagem);
        soma += valores[i];
    }
    float media = soma/qnt;
    printf("A media aritimetica eh  %.2f ",media);
    return 0;
}

int ex3(){
//3. Receba três notas e seus pesos, calcule e mostre a média ponderada.
    int qnt = Pnumero("Digite a quantidade de notas: ");
    int peso [qnt];
    float nota[qnt],somaP = 0,somaN=0;
    char mensagem[50];

    for (int i = 0; i<qnt; i++){
        sprintf(mensagem,"Digite o %d peso: ",i+1);
        peso[i]=Pnumero(mensagem);
        sprintf(mensagem,"Digite a %d nota: ",i+1);
        nota[i]=Pnumero(mensagem);

        somaP += peso[i];
        somaN += (nota[i]*peso[i]);

    }
    float media = somaN/somaP;
    printf("A media ponderada dos valores eh %.2f",media);
    return 0;
}

int ex4(){
//4. Receba o salário de um funcionário, calcule e mostre o novo salário com aumento de 25%.

    float sal = Pnumero("Digite seu salário: "), nsal,Vaument;
    float aumento = Pnumero("Digite o valor do aumento em decimais: ");
    nsal = sal*(1+aumento/100);
    Vaument = sal*(aumento/100);
    printf("O aumento foi de %.2f e o salario novo eh %.2f\n",Vaument,nsal);
    return 0;
}

/*Exercício 05,06,07 – Análise de salário com operações compostas
Escreva um programa que receba o salário base de um funcionário e permita aplicar múltiplas operações sobre ele. O usuário deverá escolher, entre as opções a seguir, quais operações deseja aplicar:
    Aumento fixo de 25%;
    Aumento com percentual informado pelo usuário;
    Gratificação de 5%;
    Desconto de 7%.
O programa deve permitir aplicar mais de uma operação na mesma execução, conforme a escolha do usuário.
Ao final, apresente:
    O valor total de acréscimos;
    O valor total de descontos;
    O salário final;
E uma mensagem informando se houve ou não perda salarial (isto é, se o salário final ficou menor que o salário base).
*/
float aumenEx5(float n){
    float aumento = Pnumero("Digite o valor do aumento: ")/100.0f;
    if (aumento > 0){
        return n*(1+aumento);
    } else{ printf("Digite um valor acima de zero\n");return aumenEx5(n);}
}
float descEx5(float dsc){
    float desconto = Pnumero("Digite o valor do desconto: ")/100.0f;
    if (dsc>0){
        return dsc*(1-desconto);
    } else{printf("Digite um valor acima de zero\n"); return descEx5(dsc);}
}
int ex5(){
    float sal = Pnumero("DIgite seu salario: ");
    float nsal= sal;
    int pergunta,qnta = 0,qntd = 0;
    int qnt = (int)Pnumero("Digite quantos salarios quer ver: ");

    for (int i = 0; i<qnt; i++){
        printf("Voce deseja verificar o que? \n 1-Acrescimos \n 2-Descontos\n");
        scanf("%d",&pergunta);

        switch (pergunta){
            case 1:
                nsal = aumenEx5(nsal);
                qnta ++;
                break;
            case 2:
                nsal = descEx5(nsal);
                qntd ++;
                break;
            default:
                printf("Opcao invalida");
                i--;
                break;
        }

    }
    if (nsal==sal){
        printf("não teve alteracao no salario\n");
    } else {printf("O salario foi alterado, o antigo era %.2f e o novo eh %.2f \n A diferenca foi de %.2f\n", sal, nsal, nsal - sal);;}
    printf("teve %d de descontos e %d de aumento\n",qntd,qnta);
    return 0;

}

int conta(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return conta(n-1) + conta(n-2);
}
int ex6() {
    int n = Pnumero("Digite o termo que quer ver: ");
    printf("O termo %d da sequencia de Fibonacci eh %d\n", n, conta(n));
    int val = Pnumero("Digite quantos valores quer ver: ");
    for (int i = 0; i<val+1; i++){
        printf("%d, ",conta(i));
    }
    return 0;
}

float calculo(float v, float j, int Mes){
    if (v > 0 || j > 0 || Mes > 0){
        return v*pow(1+j,Mes);
    }  else {return calculo(v,j,Mes);}
}
int ex8(){
//8. Receba o valor de um depósito e a taxa de juros, calcule e mostre o rendimento e o valor total.
        float valor = Pnumero("Digite o valor do deposito: ");
        float juros = (Pnumero("Digite a taxa de juros anual: ")/100)/12;
        int mes = Pnumero("Digite a quantidade de meses que deseja ver: ");
        float montante = calculo(valor,juros,mes);
        printf("O valor final eh %.2f ",montante);
}


float area(float b, float h){
        return (b*h)/2;
}
int ex9(){
//9. Calcule e mostre a área de um triângulo (Área = (base * altura)/2).
    float base = Pnumero("Digite a base do triangulo: ");
    float altura = Pnumero("Digite a altura do triangulo: ");
    float Area = area(base,altura);
    printf("A area do triangulo eh %.2f",Area);
    return 0;

}

float circulo(float r){
    return 3.14*r*r;
}
int ex10(){
//10. Calcule e mostre a área de um círculo (Área = π * raio²).
    float raio = Pnumero("Digite o valor do raio: ");
    float area = circulo(raio);
    printf("a area do criculo eh %.2f",area);
    return 0;
}

float cubo(float n, int cont){
    if (cont==0)return 1;
    return  n*cubo(n,cont-1);
}
float raiz(float n, float cont){

    return pow(n,1/cont);
}
int ex11(){
/*11. Receba um número positivo, calcule e mostre:
    a) Número ao quadrado
    b) Número ao cubo
    c) Raiz quadrada
    d) Raiz cúbica */
    float numero = Pnumero("Digite um numero: ");
    char escolha ;
    printf("voce deseja fazer oq a b c: ");
    scanf(" %c",&escolha);
    switch(escolha){
        case 'a':{
            int count = Pnumero("Digite a potencia: ");
            printf("O numero %f com a potencia %d eh %f\n ",numero,count,cubo(numero,count));
            break;
        }
        case 'b' :{
            int count2 = Pnumero("Digite a raiz: ");
            printf("O numero %f com a raiz %d eh %f\n ",numero,count2,raiz(numero,count2));
            break;
        }
        case 'c':{
            int count = Pnumero("Digite a potencia: ");
            int count2 = Pnumero("Digite a raiz: ");
            printf("O numero %.2f com a potencia %d eh %.2f e o mesmo com a raiz %d eh %.2f\n ",numero,count,cubo(numero,count),count2,raiz(numero,count2));
            break;
        }
    }
}

float pol(float n){return n/5280; }
float jar(float n ){return n/3; }
float mil(float n){return n*12; }
int ex13(){
/*13. Receba uma medida em pés, converta e mostre em:
    a) Polegadas
    b) Jardas
    c) Milhas*/
    float pes = Pnumero("Digite a media em pes: ");
    printf(" pes %.2f\n polegadas %.2f\n jardas %.2f\n milhas %.2f\n",pes,pol(pes),jar(pes),mil(pes));
    return 0;
}

int contar_idade(int N, int A){
    if(N>A){
         return printf("Ano inválido");
    }
    return A-N;
}
int ex14(){
/*14. Receba o ano de nascimento e o ano atual, calcule e mostre:
    a) Idade atual
    b) Idade em 2050*/
    int anoN = Pnumero("Digite seu ano de nascimento: ");
    int anoA = Pnumero("Digite o ano atual ou o ano desejado: ");
    printf("%d\n",contar_idade(anoN,anoA));
    return 0;

}

int ex15(){
/*15. Receba o preço de fábrica de um veículo, percentual de lucro e impostos, calcule e mostre:
    a) Valor do lucro
    b) Valor dos impostos
    c) Preço final*/
    float valor = Pnumero("digite o valor do carro: ");
    float parc = Pnumero("Digite o percentual; ")/100;
    float impo = Pnumero("Digite os impostos; ")/100;
    printf("O valor final foi %.2f\n",valor+(valor*parc)+(valor*impo));
    printf("O lucro foi de %.2f\n",valor*parc);
    printf("O valr dos impostos foi de %.2f\n",valor*impo);
    return 0;
}

float conta_sal(float horas, float sal){return horas*sal;}
int ex16(){
//16. Receba horas trabalhadas e valor do salário mínimo, calcule e mostre o salário a receber (com regras específicas).
    float sala = Pnumero("Digite o valor do salario minimo: ")/160;
    float hr = Pnumero("Digite as horas trabalhadas: ");
    printf("O salario a receber eh %.2f\n",conta_sal(hr,sala));
}

float calculo_cheque(float salario,float cheq[],int qnt,int posi){
    if (posi == qnt ){
        return salario;
    }else{
        float Nsal = salario - cheq[posi];
        return calculo_cheque(Nsal,cheq,qnt,posi+1);
    }

}
int ex17(){
//17. Receba salário e valores de dois cheques, calcule e mostre o saldo atual (considerando CPMF).
    float sal = Pnumero("Digite o valor do salario: ");
    int qnt = Pnumero("Quantos cheques quer tirar/pagar: ");
    float cheques[qnt];
    for(int i = 0; i<qnt; i++){
        float p = Pnumero("Digite o valor do cheque: ");
        p = cheques[i];
    }
    printf("O salario atual apos os cheques eh %.2f: ",calculo_cheque(sal,cheques,qnt,0));
    return 0;
}

int ex18(){
//18. Receba o peso do saco de ração e a quantidade diária para dois gatos, calcule o restante após 5 dias.*/
    int saco = Pnumero("Digite o peso do saco de racao: ");
    int gatos = Pnumero("Digite a quantidade de gatos: ");
    int dias = Pnumero("Digite o tanto de dias: ");
    float qnt = (Pnumero("Digite a dose diaria: ")/1000)*gatos*dias;
    printf("Sobrou %.2f kg no saco", saco-qnt);
}

int ex19(){
/*19. Degraus (mais difícil):
 Um alpinista deseja subir até uma altura total determinada, mas a escada que ele usa tem degraus de alturas variáveis: os primeiros 3 degraus têm altura fixa, e os demais diminuem em 2 cm a cada degrau.
  Receba a altura desejada e a altura dos primeiros 3 degraus.
  Calcule quantos degraus ele deve subir para atingir ou ultrapassar a altura.*/
    int altura = Pnumero("Digite a altura desejada: ");
    float degrau = Pnumero("Digite a altura dos 3 primeiros degraus: ")/100;
    printf("Ele precisa de %.2f degraus para chegar a %d",altura /degrau,altura);
    return 0;
}

int ex20(){
/*20. Escada (mais difícil):

Original: Receba o ângulo formado por uma escada e a altura da parede, calcule o tamanho da escada.
Versão mais exigente:

 Uma escada está apoiada contra uma parede e forma um ângulo com o chão. Porém, por segurança, é necessário que esse ângulo esteja entre 60° e 75°.
  Receba a altura da parede e um intervalo de ângulos possíveis.
  Para cada ângulo inteiro dentro desse intervalo, calcule o comprimento da escada necessário.
  Mostre o menor comprimento possível e o maior.*/

    float altura = Pnumero("Digite a altura da parede em Metros : ");
    float angulo = Pnumero("digite o angulo da escada entre 60 e 75 graus: ");
    float comprimento;
    comprimento = sin(angulo)*altura;
    printf("%.2f\n",comprimento);
    return 0;
}

int ex22(){
/*22. Energia (mais difícil):

Original: Receba salário mínimo e kWh consumidos, calcule valor do kWh, total, e com desconto.
Versão mais exigente:

 Uma residência consome energia em 3 horários diferentes: ponta, intermediário e fora de ponta.
  Cada um tem um fator multiplicador diferente no valor do kWh (ponta = 2x, intermediário = 1.5x, fora de ponta = 1x).
  O valor base do kWh corresponde a 1/5 do salário mínimo.
  Receba o consumo em kWh para cada horário e o salário mínimo.
  Calcule:

 Valor do kWh em R\$
 Valor total da conta
 Valor com desconto de 10% para quem consumir menos de 150 kWh.*/
  float sal = Pnumero("Digite o valor do salario minimo: ");
  int qnt = Pnumero("Digite a quantidade de kwh: ");
  int horas[qnt];
  float valores[qnt],soma = 0;


  for(int i = 0; i < qnt; i++){
        horas[i] = Pnumero("Digite as horas inteiras: ");
        valores[i]=Pnumero("Digite os %d kwh: ");
        if (5>valores<12){valores[i]*2*sal/5;}
        else if (13>valores<18){valores[i]*1.5*sal/5;}
        else {valores[i]*sal/5;}
  }
  for(int i = 0; i<qnt; i++){
    soma+=valores[i];
    printf("Cada valor em kwh ja com os valores sao:");
    printf("(%.2f as %d\n)",valores[i],horas[i]);
  }
    if (soma<= 150){printf("O valor final foi de %.2f\n",soma*0.9);}
    else{printf("O valor final foi de %.2f\n ", soma);}



}

int ex23(){
/*Faça um programa que receba um número real, encontre e mostre:
a) a parte inteira desse número;
b) a parte fracionária desse número;
c) o arredondamento desse número.*/
    float real = Pnumero("Digite um numero real: ");
    int arredondado;
    if (real-(int)real >= 0.5){
        arredondado = (int)real+1;
    }
    else if (real<0){
        if (real-(int)real <= -0.5){
            arredondado = (int)real-1;
        } else {arredondado = (int)real;}
    }
    else {arredondado=(int)real;}



    printf("Real: %.2f\n",real);
    printf("Fracionada: %.2f\n",real-(int)real);
    printf("arredondado: %d\n",arredondado);
    printf("Inteiro: %d\n",(int)real);
    return 0;

}

int ex24(){
/*Faça um programa que receba uma hora formada por hora e minutos (um número real), calcule e
mostre a hora digitada apenas em minutos. Lembre-se de que:
■■ para quatro e meia, deve-se digitar 4.30;
■■ os minutos vão de 0 a 59*/
    float hora=Pnumero("Digite a hora'4.30': ");
    int minutos = (int)hora;
    float seg = hora-minutos;
    printf("Ahora digitada em mintuos eh %d\n",(int)((minutos*60)+(seg*100)));
}

int ex25(){
/*Faça um programa que receba o custo de um espetáculo teatral e o preço do convite desse espetáculo.
Esse programa deverá calcular e mostrar a quantidade de convites que devem ser vendidos para que,
pelo menos, o custo do espetáculo seja alcançado*/
    float custo = Pnumero("Digite o valor do teatro: ");
    float convite = Pnumero("Digite o valor do convite: ");

    printf("A quantidade de convits necessária eh de %d\n",(int)(custo/convite));

}







int main() {
    int num;
    int (*exercicios[30])() = {
         ex1, ex2, ex3, ex4, ex5, ex6,7, ex8, ex9, ex10, ex11,12, ex13,ex14,ex15,ex16,ex17,
         ex18,ex19, ex20, 21, ex22,ex23,ex24,ex25 NULL
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
