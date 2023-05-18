
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

void prints(Lista *l){
    printf("tam adj lista = %d\n", l->size_adj_list);
    printf("tam token: %d\n", l->tam_l_token);
    printf("tam size_l: %d\n", l->size_l);
}


//token lexema
void buffer(Lista **l){
    FILE *arq_token;
    arq_token = fopen("arq.c", "r");

    if(arq_token == NULL){
        printf("erro ao abrir o arquivo! -> lex\n");
        exit(1);
    }
    
    // buffer que armazena a palvra token tem a posicao POS_BUF
    //BUFFER_POSICAO armazena a posicao que a inicial apareceu igual a posicao inicial que o buffer leu -> cont_buf
    int cont_adj_begin = 0, pos_adj = 0, pos_buf = 0, cont_buf=0;
    int *buffer_posic = (int*)malloc(sizeof(int)); //guardar a posicao que tem as mesmas iniciais
    int pos_caracter_in = 36, valid_caracter=0;
    char *buffer = (char*)malloc(sizeof(char));
    char aux_buf = fgetc(arq_token); //percorrer o arquivo de entrada
    char next = aux_buf;
    Node *aux_list = l[cont_adj_begin]->inicio;
    
    while(next != EOF){
        //printf("%c -> %c || %d -- %d\n", aux_list->letra, next, cont_adj_begin, pos_buf);
        // if (aux_list->letra == next){
        //     printf("%d\n", cont_adj_begin);
        //     buffer_posic[cont_buf] = cont_adj_begin;
        //     cont_buf++;
        //     cont_adj_begin++;
        //     //aux_list = aux_list[cont_adj_begin].next;
        // }
        while(pos_caracter_in < 77){
            if (next == l[pos_adj]->inicio->letra) {
                valid_caracter = 1;
            }
            pos_caracter_in++;
            
        }
        if(next != '\n' && next != ' ' && next != '\t'){
            buffer[cont_buf] = aux_buf;
            pos_buf++;
            if()
        } else {
            //printf("%d", pos_buf);
            buffer[pos_buf] = '\0';
            printf("%s\n", buffer);
            pos_buf = 0;
        }
        aux_buf = fgetc(arq_token);
        next = aux_buf;
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

    //     for(int j=0; j<n; j++){
    //     printf("|%d|-|%s| = ", j,list[j]->token_list);
    //     print_List(list[j]);
    //     printf("\n");
    // }

    free(list); 
    return 0;
}
