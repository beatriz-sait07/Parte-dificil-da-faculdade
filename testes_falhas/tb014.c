
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
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
    l[i]->size_adj_list++;
    while(aux != EOF){
        if (aux == ' '){
            char* vet = (char*) malloc(50 * sizeof(char));
            fgets(vet, 50, arq);
            if (vet[strlen(vet)-1] == '\n') {
                vet[strlen(vet)-1] = '\0';
                i++;
                l[i] = Lista_create();
                l[i]->size_adj_list++;
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

void buffer(Lista** l) {
    FILE* arq_token;
    arq_token = fopen("arq.c", "r");

    if (arq_token == NULL) {
        printf("Erro ao abrir o arquivo! -> lex\n");
        exit(1);
    }

    int cont_adj_begin = 0, pos_b = 0, buffer_size = 1;
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    char aux_buf = fgetc(arq_token);
    Node* aux_list = l[cont_adj_begin]->inicio;

    while (aux_buf != EOF) {
        if (aux_buf != ' ' && aux_buf != '\t' && aux_buf != '\n') {
            buffer[pos_b] = aux_buf;
            pos_b++;

            // Verifica se o buffer está cheio e realoca mais memória se necessário
            if (pos_b >= buffer_size) {
                buffer_size *= 2; // Dobrar o tamanho do buffer
                buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
            }

            aux_buf = fgetc(arq_token);
        } else {
            if (pos_b > 0) { // Verifica se há caracteres no buffer antes de finalizá-lo
                buffer[pos_b] = '\0';
                printf("%s\n", buffer);
                //comeca a verificacao aqui!
                

                pos_b = 0;
                aux_buf = fgetc(arq_token);
            } else {
                aux_buf = fgetc(arq_token); // Ignora o caractere de nova linha e continua a leitura
            }
        }
    }

    // Verifica se há caracteres no buffer quando o arquivo termina
    if (pos_b > 0) {
        buffer[pos_b] = '\0';
        printf("%s\n", buffer);
    }

    fclose(arq_token);
    free(buffer);
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
