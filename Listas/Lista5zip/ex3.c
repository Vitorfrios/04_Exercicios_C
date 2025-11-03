#include <stdio.h>

int soma(int n){
    if(n==1)return 1;
    else return n+soma(n-1);

}
int main() {
//Faça uma função recursiva que calcula a soma dos números de 1 até n.
    int n;
    scanf("%d",&n);
    printf("%d",soma(n));

    return 0;
}
