/*ta separando as palavras dos tokens, mas nao esta puxando a ultima linha do arquivo corretamente

necessario fazer a funcao de comparacao de palavras e tokens
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_enc.h"

void token(Lista **l) {
    FILE *arq;
    char buffer[256];

    arq = fopen("tokens.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int i = 0;
    l[i] = Lista_create();

    while (fgets(buffer, sizeof(buffer), arq) != NULL) {
        int buffer_len = strlen(buffer);
        int word_start = 0;
        for (int j = 0; j < buffer_len; j++) {
            if (buffer[j] == ' ' || buffer[j] == '\n') {
                // Adiciona as letras na lista atual
                for (int k = word_start; k < j; k++) {
                    add_Last(l[i], buffer[k]);
                }
                if (word_start < j) {
                    l[i]->token_list = (char*) malloc((j - word_start + 1) * sizeof(char));
                    strncpy(l[i]->token_list, buffer + word_start, j - word_start);
                    l[i]->token_list[j - word_start] = '\0';
                    add_Last(l[i], ' '); // Adiciona espaço entre as palavras
                }
                word_start = j + 1;
            }
            if (buffer[j] == '\n') {
                i++;
                l[i] = Lista_create();
                word_start = 0;
            }
        }
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


int main(){
    int n = 77;
    Lista **list = (Lista **) malloc(n * sizeof(Lista *));

    if (list == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    token(list);

    printf("tokens: \n");

    for(int i=0; i<n; i++){
        print_List(list[i]);
        printf("\n");
    }

    printf("\n\nLista token: \n");
    for(int i=0; i<n; i++){
        printf("%s\n", list[i]->token_list);

    }
    free(list); 
    return 0;
}