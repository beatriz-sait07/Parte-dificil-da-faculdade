
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

void valida_token(Lista **l, char *buffer){
    int cont_l=0, cont_b=0;
    Node *aux = l[cont_l]->inicio;
    while(aux != NULL || buffer[cont_b] != '\0'){
        printf("%c -> %c\n", buffer[cont_b], aux->letra);
        if(aux->letra == buffer[cont_b]){
            if(aux->next == NULL && buffer[cont_b + 1]){
                printf("token valido: %s\n", l[cont_l]->token_list);
            } else if (buffer[cont_b] != '\0' && aux == NULL) {
                cont_l++;
                aux= l[cont_l]->inicio;
                cont_b=0;
            } else {
                printf("token invalido!\n");
            }
        } else {
            if(aux->letra != buffer[cont_b]) {
                cont_b=0;
                while(aux->letra != buffer[cont_b]){
                    cont_l++;
                    aux = l[cont_b]->inicio;
                    printf("teste\n"); //erro aqui
                }
            } else {
                printf("inicial nao encontrada! \n");
            }
        }
        cont_b++;
        aux = aux->next;
    } 
}

/*void valida_token(Lista **l, char *buffer){
    int cont_l=0, cont_b=0;
    Node *aux = l[cont_l]->inicio;
    while(aux != NULL || buffer[cont_b] != '\0'){
        printf("%c -> %c\n", buffer[cont_b], aux->letra);
        if(aux->letra == buffer[cont_b]){
            if(aux->next == NULL && buffer[cont_b + 1]){
                printf("token valido: %s\n", l[cont_l]->token_list);
            } else if (buffer[cont_b] != '\0' && aux == NULL) {
                cont_l++;
                aux= l[cont_l]->inicio;
                cont_b=0;
            } else {
                printf("token invalido!\n");
            }
        } else {
            if(aux->letra != buffer[cont_b]) {
                cont_b=0;
                while(1){
                    if(aux->letra != buffer[cont_b]){
                        continue;
                    } else {
                        break;
                    }
                    cont_l++;
                    aux = l[cont_b]->inicio;
                }
            } else {
                printf("inicial nao encontrada! \n");
            }
        }
        cont_b++;
        aux = aux->next;
    } 
}

*/

void buffer(Lista **l){
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
            if(next >= 'a' && next <= 'z' || next >= 'A' && next <= 'Z'){
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
            else{
                buffer[i] = '\0'; //era o print aqui
                valida_token(l, buffer);
                i = 0;
            }
        }
        else {
            if (i > 0) {
                buffer[i] = '\0';
                i = 0;
            }
            atual = fgetc(arq);
            next = atual;
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
    buffer(list);
    free(list); 
    return 0;
}