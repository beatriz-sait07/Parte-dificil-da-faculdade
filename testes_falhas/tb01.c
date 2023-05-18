#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ESTADO_INICIAL 0 // estado inicial
#define ESTADO_COMENTARIO 1 // comentario
#define ESTADO_LITERAL 2 // string
#define ESTADO_IDENTIFICADOR 3 // variavel
#define ESTADO_NUMERO 4 // numero
#define ESTADO_OPERADOR_ARITMETICO 5 // operador aritmetico
#define ESTADO_OPERADOR_RELACIONAL 6 // operador relacional
#define ESTADO_OPERADOR_ATRIBUICAO 7 // operador de atribuicao
#define ESTADO_OPERADOR_LOGICO 8 // operador logico
#define ESTADO_DELIMITADOR 9 // delimitador
#define ESTADO_ERRO 10 // erro
#define NUM_ESTADOS 11 // numero de estados

//ideia principal

typedef struct node_dados Node;
typedef struct list List;
bool isNull(const List *l);
Node *create_node (char caracter);
List *create_list();
void insere_dados(List *l, char letra);
void print(const List *list);
//void exluir_lista(List **ref_l);
int main (){
    FILE *arq;
    arq = fopen("arq.c", "r");
    
    List *lista[50]; // lista de palavras
    int i; // contador da lista, cada i vai ser uma palavra
    
    if (arq == NULL){
        printf("erro ao abrir o arquivo!\n");
        exit(1);
    }
    

    lista[0] = create_list();
    List *list_caracter = create_list();
    List *list_num = create_list();
    List *frase = create_list();
    char aux = fgetc(arq);

    //percorrendo o arquivo e jogando os caracteres em uma lista
    while(aux != EOF){ 
        if(aux != ' ' && aux != '\n' && aux != '\t'){
            if(aux == '"'){
                insere_dados(frase, aux);
                aux = fgetc(arq);
                while(aux != '"'){
                    insere_dados(frase, aux);
                    aux = fgetc(arq);
                }
                insere_dados(frase, aux);
                aux = fgetc(arq);
            }
            if (!(aux >= 'a' && aux <= 'z' || aux >= 'A' && aux <= 'Z')) { // se nao for letra
                if (aux < '0' || aux > '9') { // se nao for numero

                    insere_dados(list_caracter, aux);
                    aux = fgetc(arq);
                }
                else {
                    insere_dados(list_num, aux);
                    aux = fgetc(arq);
                }
            }
            else {
                insere_dados(lista[i], aux);
                aux = fgetc(arq);
            }
        }
        else {
            if (aux == '\n') {
                aux = fgetc(arq);
                aux = fgetc(arq);
                aux = fgetc(arq);
                aux = fgetc(arq);
            }
            if (aux == ' ') {
                i++;
                lista[i] = create_list();
            }
            
            aux = fgetc(arq);
        }
    }

    printf("lista de palavras: \n");
    i=0;
    while(lista[i] != NULL){
        print(lista[i]);
        i++;
    }
    printf("\n\nlista de caracteres: \n");
    print(list_caracter);
    printf("\n\nlista de numeros: \n");
    print(list_num);
    printf("\n\nlista de frases: \n");
    print(frase);

    fclose(arq);
    printf("\n\n");

    return 0;
}

// criar uma funcao para definir os token do arquivo de saida

typedef struct  node_dados {
    char letras;
    struct node_dados *next;
}Node;

typedef struct list {
    Node *inicio, *fim;
    long int size;
} List;

bool isNull(const List *l){
    return l->inicio == NULL;
}

Node *create_node (char caracter){
    Node *aux = (Node*)calloc(1, sizeof(Node));
    aux->letras = caracter;
    aux->next = NULL;

    return aux;
}

List *create_list() {
    List *l = (List*)calloc(1, sizeof(List));
    l->inicio = NULL;
    l->fim = NULL;
    l->size = 0;

    return l;
}

void insere_dados(List *l, char letra){ // adicionando apenas no final, pq ? pq eh uma palavra!
    Node *alpha = create_node(letra);
    if (isNull(l)) l->inicio = alpha;
    else {
        Node *aux = l->inicio;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = alpha;
    }
    //printf("%c", letra);
    l->size ++;
}

void print(const List *list){
    Node *p = list->inicio;

    if(list != NULL){
        printf("INICIO -> ");
        while(p != NULL){
            printf(" %c ->", p->letras);
            p = p->next;
        }
        printf("NULL\n");
    }else{
        printf("a lista foi totalmete desalocada!\n");
    }
}

    /*while != null
    se lista.palvra == a
        if lista.palavra == u
        if palavra == t
        se palavra == o
        l.token = "auto"

    se palavra == i*/
        
    

void exluir_lista(List **ref_l){
    List *l = *ref_l;
    Node *pont = l->inicio;
    Node *aux = NULL;

    while(pont != NULL){
        aux = pont;
        pont = pont->next;
        free(aux);
    }
    free(l);
    *ref_l = NULL;
    printf("\nlista totalmente desalocada!\n");
}