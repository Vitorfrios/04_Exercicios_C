#include <stdio.h>
#include <math.h>

double soma(int n){
    double s = 0;
    for(int i = 1; i <= n; i++){
        s += ((i*i + 1.0)/(i + 3.0));
    }
    return s;
}

int main(){
    int n;
    scanf("%d", &n);
    printf("%.6f\n", soma(n));
    return 0;
}
