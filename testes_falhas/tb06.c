// buffer e token ok

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista_enc.h"

#define AUTO

void token(Lista **l) {
    FILE *arq;
    arq = fopen("tokens.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
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


void buffer(Lista **l){
    FILE *arq;
    arq = fopen("arq.c", "r");

    if (arq == NULL){
        printf("erro ao abrir o arquivo!\n");
        exit(1);
    }

    char buffer[50];
    int i=0;
    int in_word = 0; // indica se estamos dentro de uma palavra ou não
    

    while(1){
        int aux = fgetc(arq);
        if (aux == EOF){ // se chegou ao fim do arquivo, para o loop externo
            break;
        }
        if (aux != ' ' && aux != '\n' && aux != '\t' && aux != '\r'){ // se o caractere não é um espaço em branco, adiciona ao buffer
            in_word = 1;
            buffer[i] = aux;
            i++;
        }
        else if (in_word){ // se o caractere é um espaço em branco e estávamos dentro de uma palavra, imprime a palavra e reseta o buffer
            in_word = 0;
            for(int j=0; j<i; j++){
                //faca a atribuicao do print para a lista
                printf("%c", buffer[j]);
            }
            printf("\n");
            for(int j=0; j<50; j++){ // reseta o buffer manualmente
                buffer[j] = 0;
            }
            i=0;
        }
    }

    fclose(arq);
}


int main(){
    int n = 75;
    Lista **list = (Lista **) malloc(n * sizeof(Lista *));

    if (list == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    token(list);

    /*for(int i=0; i<n; i++){
        print_List(list[i]);
        printf("\n");
    }*/
    buffer(list);

    free(list); 
    return 0;
}
