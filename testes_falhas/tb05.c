//comecou a andar...
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista_enc.h"

#define AUTO

void token(Lista **l){
    
    FILE *arq;
    arq = fopen("tokens.txt", "r");

    if (arq == NULL){
        printf("erro ao abrir o arquivo!\n");
        exit(1);
    }
    int i = 0;
    l[i] = Lista_create();
    char aux = fgetc(arq);

    while(aux  != EOF){
        if(aux == '\n'){
            aux = fgetc(arq);
            i++;
            l[i] = Lista_create();
        }
        add_Last(l[i], aux);
        aux = fgetc(arq);

    }
    fclose(arq);
}


int main (){
    Lista *list[75];
    token(list);
    for(int i=0; i<75; i++){
        print_List(list[i]);
        printf("\n");
    }
    return 0;
}