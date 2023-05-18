// erro apenas ao ler um token invalido

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_enc.h"

void token(Lista **l) {
    FILE *arq;
    arq = fopen("tokens.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int i = 0, j = 0;
    char aux = fgetc(arq);
    l[i] = Lista_create();

    while(aux != EOF){
        if (aux == ' '){
            char* vet = (char*) malloc(50 * sizeof(char));
            fgets(vet, 50, arq);
            if (vet[strlen(vet)-1] == '\n') {
                vet[strlen(vet)-1] = '\0';
                i++;
                l[i] = Lista_create();
            }
            l[j]->token_list = (char*) malloc((strlen(vet)+1) * sizeof(char));
            strcpy(l[j]->token_list, vet);
            free(vet);
            j++;
        } else {
            add_Last(l[i], aux);
        }
        aux = fgetc(arq);
    }

    fclose(arq);
}

char *valida_token(Lista **l, char *buffer) {
    int i = 0, j = 0;
    Node *aux = l[i]->inicio;

    if (l[i]->inicio == NULL || buffer == NULL) {
        printf("nao ha dados para prosseguir na funcao!\nErr: valida_token\n");
        exit(1);
    } 
    else {
        while (l[i] != NULL) {
            aux = l[i]->inicio;
            j = 0;
            while (aux != NULL && aux->letra == buffer[j]) {
                aux = aux->next;
                j++;
                if (buffer[j] == '\0' && aux == NULL) {
                    printf("Token valido: %s\n", buffer);
                    return buffer;
                }
            }
            i++;
        }
        printf("Token invalido!\n");
    }
    return buffer;
}




void buffer(Lista **l){ // cria o buffer
    FILE *arq;
    arq = fopen("arq.c", "r");
    char atual = fgetc(arq);
    char next = atual;

    if (arq == NULL){
        printf("erro ao abrir o arquivo!\n");
        exit(1);
    }

    char buffer[50];
    int i = 0;
    
    while (next != EOF){
        if (next != ' ' && next != '\t' && next != '\n') {
            buffer[i] = atual;
            i++;
            atual = fgetc(arq);
            next = atual;
            if(next >= 'a' && next <= 'z' || next >= 'A' && next <= 'Z' || next >= '0' && next <= '9' || next == '_'){ // se for letra ou numero ou _ continua
                continue;
            }
            else if (next == '"'){
                buffer[i] = atual;
                i++;
                atual = fgetc(arq);
                next = atual;
                while(next != '"'){
                    buffer[i] = atual;
                    i++;
                    atual = fgetc(arq);
                    next = atual;
                }
                buffer[i] = atual;
                i++;
                atual = fgetc(arq);
                next = atual;
            }
            else{ // se for outro caractere, imprime o buffer e zera ele
                buffer[i] = '\0';
                valida_token(l, buffer);
                i = 0;
                exit(1);
            }
        }
        else {
            atual = fgetc(arq);
            next = atual;
        }
    }
    fclose(arq);
}


int main(){
    int n = 77;
    Lista **list = (Lista **) malloc(n * sizeof(Lista *));

    if (list == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    token(list);
    buffer(list);
    free(list); 
    return 0;
}