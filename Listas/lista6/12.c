#include <stdio.h>
#include <ctype.h>

int main() {
    char string[100];
    int vogais = 0, consoantes = 0;
    
    scanf("%s", string);
    
    char *ptr = string;
    
    while(*ptr != '\0') {
        char c = tolower(*ptr);
        
        if(c >= 'a' && c <= 'z') {
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vogais++;
            } else {
                consoantes++;
            }
        }
        ptr++;
    }
    
    printf("Vogais: %d\n", vogais);
    printf("Consoantes: %d\n", consoantes);
    
    return 0;
}