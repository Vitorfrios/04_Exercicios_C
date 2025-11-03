#include <stdio.h>

// Funções de exercícios já declaradas aqui
// ==========================
// 1. O cofre secreto (nota 3)
// Verifique se a senha é múltiplo de 3 e menor que 100.
// Pergunta extra: o que acontece se a senha for 105 ou 9?
// ==========================
void cofreSecreto() {
    float senha=0;
    printf("Exercicio da senha\n");
    while(senha != -1){
        scanf("%f",&senha);
        if((int)senha % 3 == 0 && senha<100) {printf("Parabens vc acertou\n"); senha=-1;}
        else printf("Tente novamente\n");
    }
}

// ==========================
// 2. Corrida dos carros (nota 4)
// Some o tempo total de 5 voltas.
// Pergunta extra: como saber se alguma volta foi mais rápida que 50 segundos?
// ==========================
void corridaDosCarros() {
    float tempo,total=0,menor=0;

    for(int i = 0;i<5;i++){
        printf("Digite o tempo da %d volta\n",i+1);
        scanf("%f",&tempo);
        total += tempo;
        if(i==0)menor=tempo;
        if(tempo<50){
            if(menor>tempo)menor=tempo;
        }
    }
    printf("O tempo total as voltads foi %.2f ",total);
    printf("O menor tempo foi de %.2f ",menor);
}

// ==========================
// 3. Caixa de surpresas (nota 5)
// Imprima apenas números pares e maiores que 10.
// Pergunta extra: e se a quantidade de números for indefinida?
// ==========================
void caixaDeSurpresas() {
    // Seu código aqui
}

// ==========================
// 4. Ranking do campeonato (nota 4)
// Calcule a média de pontos de 3 jogadores e descubra o campeão.
// Pergunta extra: como decidir o vencedor se houver empate?
// ==========================
void rankingDoCampeonato() {
    // Seu código aqui
}

// ==========================
// 5. Menu do restaurante (nota 3)
// Menu com 4 opções (1-Pizza, 2-Hamburguer, 3-Salada, 4-Sair).
// Pergunta extra: como tratar caso de usuário digitar 5 ou 0?
// ==========================
void menuDoRestaurante() {
    // Seu código aqui
}

// ==========================
// 6. Mini calculadora (nota 5)
// Receba dois números e uma operação (+, -, *, /) e mostre o resultado.
// Pergunta extra: operação inválida ou divisão por zero.
// ==========================
void miniCalculadora() {
    // Seu código aqui
}

// ==========================
// 7. A festa das idades (nota 4)
// Separe pessoas em grupos: crianças (<12), adolescentes (12–17), adultos (18–59), idosos (60+).
// Pergunta extra: se receber 10 idades, conte quantas pessoas em cada grupo.
// ==========================
void festaDasIdades() {
    // Seu código aqui
}


int main() {
    int opcao = -1; // inicializa com valor diferente de 0

    while(opcao != 0) { // repete enquanto não for 0

        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cofreSecreto(); break;
            case 2: corridaDosCarros(); break;
            case 3: caixaDeSurpresas(); break;
            case 4: rankingDoCampeonato(); break;
            case 5: menuDoRestaurante(); break;
            case 6: miniCalculadora(); break;
            case 7: festaDasIdades(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    }

    return 0;
}
