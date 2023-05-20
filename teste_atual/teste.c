
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

// Node *caracter(Lista **l, char pos, int pos_adj){
//     int pos_caracter_in = 36, valid_caracter=0;
//     Node *aux = l[pos_adj]->inicio;
//     if (l[pos_caracter_in]->inicio->letra == pos){
//         return l[pos_caracter_in]->token_list;
//     } else if (aux->letra != pos) {
//         pos_caracter_in++;
//         caracter(l[pos_caracter_in]->inicio, pos, pos_adj);
//     } else {
//         return printf("nao eh um caracter especial!\n");
//     }
//         // while(pos_caracter_in < 50){
//         //     if (pos == l[pos_adj]->inicio->letra) {
//         //         valid_caracter = 1;
//         //     }
//         //     pos_caracter_in++;
//         // }
// }

// Node* caracter(Lista** l, char pos, int pos_adj) {
//     int pos_caracter_in = 36, valid_caracter = 0;
//     Node* aux = l[pos_adj]->inicio;
    
//     if (l[pos_caracter_in]->inicio->letra == pos) {
//         return l[pos_caracter_in]->token_list;
//     } else if (aux->letra != pos) {
//         pos_caracter_in++;
//         return caracter(&l[pos_caracter_in], pos, pos_adj);
//     } else {
//         printf("Não é um caracter especial!\n");
//         return NULL;
//     }
// }


//token lexema
void buffer(Lista **l){
    FILE *arq_token;
    arq_token = fopen("arq.c", "r");

    if(arq_token == NULL){
        printf("erro ao abrir o arquivo! -> lex\n");
        exit(1);
    }

    int cont_adj_begin = 0, pos_adj = 0, pos_buf = 0, cont_buf=0;
    int *buffer_posic = (int*)malloc(sizeof(int)); //guardar a posicao que tem as mesmas iniciais
    char *buffer = (char*)malloc(sizeof(char));
    char aux_buf = fgetc(arq_token); //percorrer o arquivo de entrada
    char next = aux_buf;
    Node *aux_list = l[cont_adj_begin]->inicio;
    
    while(next != EOF){

        if(next == '\n' || next == ' ' || next == '\t'){
            buffer[pos_buf] = '\0';
            printf("%s\n", buffer);
        } else {
            buffer[cont_buf] = next;
            cont_buf++;
            printf("%s\n", buffer);
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
