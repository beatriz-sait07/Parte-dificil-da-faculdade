/* 100% funcional, esta separando as listas de tokens e palavras reservadas
*/

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
                printf("%s\n", buffer);
                i = 0;
            }
        }
        else {
            if (i > 0) {
                buffer[i] = '\0';
                printf("%s\n", buffer);
                i = 0;
            }
            atual = fgetc(arq);
            next = atual;
        }
    }
    fclose(arq);
}


//passar no ddd e ver o que esta acontecendo aqui
void valida_token(Node *node, char *buffer){
    if(node == NULL){
        printf("%s -> Token invalido!\n", buffer);
        exit(1);
    }
    else{
        int i = 0;
        while (node->letra != '\0' && buffer[i] != '\0') {
            if (node->letra != buffer[i]) {
                valida_token(node->next, buffer);
                return;
            }
            i++;
        }
        if (node->letra == '\0' && buffer[i] == '\0') {
            printf(" %s -> Token valido!\n", buffer);
        } else {
            valida_token(node->next, buffer);
        }
    }
}

void print_list_token(Lista **l, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", l[i]->token_list ? l[i]->token_list : "(null)"); // Trata caso de token_list ser NULL
    }
}


int main(){
    int n = 77;
    Lista **list = (Lista **) malloc(n * sizeof(Lista *));

    if (list == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    token(list);

    for(int j=0; j<n; j++){
        printf("|%d|-|%s| = ", j,list[j]->token_list);
        print_List(list[j]);
        printf("\n");
    }

    free(list); 
    return 0;
}