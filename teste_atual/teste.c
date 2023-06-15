// LEMBRE-SE DE CORRIGIR O ERRO DA STRING
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
    FILE* arq_token = fopen("arq.c", "r");

    if (arq_token == NULL) {
        printf("Erro ao abrir o arquivo! -> lex\n");
        exit(1);
    }

    int cont_adj_begin = 0, pos_b = 0, buffer_size = 1;
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    char aux_buf = fgetc(arq_token);
    Node* aux_list = l[cont_adj_begin]->inicio;
    int buffer_printed = 0; // Flag para controlar se o buffer já foi impresso

    while (aux_buf != EOF) {
        int j = 35;
        int controle = 0;
        while (j <= 74) {
            if (aux_buf == l[j]->inicio->letra) {
                controle = 1;
                break;
            }
            j++;
        }
        if (controle == 1 && aux_buf == l[42]->inicio->letra) {
            buffer[pos_b] = aux_buf;
            pos_b++;
            aux_buf = fgetc(arq_token);
            while (aux_buf != l[42]->inicio->letra && aux_buf != EOF) { //cria a string
                buffer[pos_b] = aux_buf;
                pos_b++;
                aux_buf = fgetc(arq_token);
                if (pos_b >= buffer_size) {
                    buffer_size *= 2;
                    buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
                }
                if (aux_buf == EOF) { // finaliza o laco pois o arquivo acabou e nao encontrou o fechamento do comentario
                    printf("\n***Erro! Comentario nao fechado!***\n");
                    break;
                }
            }
            buffer[pos_b] = aux_buf; // finaliza a string com a ultima aspas
            pos_b++;
            aux_buf = fgetc(arq_token);
            buffer[pos_b] = '\0';
            printf("%s\n", buffer);
            pos_b = 0; // Redefinir o buffer
            controle = 0; // Redefinir o controle
            continue; // Volta para o início do while
        } else if (controle == 1 && aux_buf != l[42]->inicio->letra) {
            buffer[pos_b] = aux_buf;
            buffer[1] = '\0';
            int cont_caract = 35, caract_valido = 0;
            while (cont_caract < 79) {
                if (buffer[pos_b] == l[cont_caract]->inicio->letra) {
                    caract_valido = 1;
                    // printf("%d\n", cont_caract);
                    break;
                } else {
                    caract_valido++;
                }
                cont_caract++;
            }
            if (caract_valido == 1) {
                printf("%s --> token valido: %s\n", buffer, l[cont_caract]->token_list);
                caract_valido = 0;
            } else {
                printf("%s --> token invalido\n", buffer);
            }
            //printf("%s ********\n", buffer);
            pos_b = 0;
        }

        if (aux_buf != ' ' && aux_buf != '\t' && aux_buf != '\n' && controle != 1) { // verifica se é letra
            buffer[pos_b] = aux_buf;
            pos_b++;
            if (pos_b >= buffer_size) {
                buffer_size *= 2;
                buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
            }
            aux_buf = fgetc(arq_token);
        } else {
            if (pos_b > 0) {
                buffer[pos_b] = '\0';
                printf("%s  ->  ", buffer);
                int cont_bg2 = 0;
                aux_list = l[cont_bg2]->inicio;
                while (cont_bg2 < 35) {
                    if (buffer[0] == aux_list->letra) {
                        cont_adj_begin = cont_bg2;
                        aux_list = l[cont_adj_begin]->inicio;
                        break;
                    }
                    cont_bg2++;
                    aux_list = l[cont_bg2]->inicio;
                }
                int cont_buf = 0, cont_adj = 0;
                aux_list = l[cont_adj_begin]->inicio;
                while (cont_buf < pos_b && aux_list != NULL) {
    if (buffer[cont_buf] == aux_list->letra) {
        cont_adj++;
        cont_buf++;
        if (cont_buf == pos_b) { // Verifica se o buffer acabou e se o adjacente também acabou
            break;
        }
        if (aux_list->next->letra != buffer[cont_buf]) {
            cont_buf = 0;
            cont_adj_begin++;
            if (cont_adj_begin >= 35) {
                break;  // Excedeu o número máximo de listas
            }
            aux_list = l[cont_adj_begin]->inicio;
            continue; // Pular para a próxima posição da lista de adjacência
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
                buffer[pos_b] = '\0'; // Limpar o buffer
            }
            aux_buf = fgetc(arq_token);
        }
    }
    fclose(arq_token);
    free(buffer);
}


int main(){
    int n = 79;
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