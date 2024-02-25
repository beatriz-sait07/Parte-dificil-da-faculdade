#include <stdio.h>
#include <string.h>

int main(){

    char entrada[20];
    int desloc;
    printf("Entrada: ");
    scanf("%s", entrada);
    printf("qual o deslocamento que deseja: ");
    scanf("%d", &desloc);

    char cryp[20], aux; // vetor para encryptografar e nao sobrescrever o original.
    
    
    for(int i=0; i < strlen(entrada); i++){
        aux = entrada[i];
        cryp[i] = aux + desloc;

    }

    printf("Frase original: %s\n", entrada);
    printf("Frase cryptografada: %s\n\n", cryp);
    return 0;
}