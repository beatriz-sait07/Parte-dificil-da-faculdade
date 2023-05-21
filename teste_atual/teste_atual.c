
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
            if (pos_b > 0) {
                buffer[pos_b] = '\0';
                printf ("%s  ->  ", buffer);
                int cont_bg2 = 1, cont = 0;
                aux_list = l[cont_bg2]->inicio;
                while (cont_bg2 < 35) {
                    if (buffer[0] == aux_list->letra) {
                        cont_adj_begin = cont_bg2;
                        aux_list = l[cont_adj_begin]->inicio;
                        break;
                    } else if (buffer[0] != aux_list->letra) {
                        cont_bg2++;
                        aux_list = l[cont_bg2]->inicio;
                    }
                }
                int cont_buf = 0, cont_adj = 0;
                aux_list = l[cont_adj_begin]->inicio;
                while (cont_buf < pos_b && aux_list != NULL) {
                    if (buffer[cont_buf] == aux_list->letra) {
                        cont_adj++;
                        cont_buf++;
                        if (cont_buf == pos_b) {
                            break;  // Verificou todos os caracteres do buffer
                        }
                    } else {
                        cont_buf = 0;
                        cont_adj_begin++;
                        if (cont_adj_begin >= 35) {
                            break;  // Excedeu o número máximo de listas
                        }
                        aux_list = l[cont_adj_begin]->inicio;
                    }
                    aux_list = aux_list->next;
                }

                if (cont_adj != cont_buf) {
                    printf("token nao identificado!\n");
                } else {
                    printf("token valido: %s\n", l[cont_adj_begin]->token_list);
                }
                pos_b = 0;
                buffer_size = 1;
                aux_buf = fgetc(arq_token);
            } else {
                aux_buf = fgetc(arq_token);
            }
        }
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