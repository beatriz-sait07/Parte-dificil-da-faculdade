//corregi os erros de encadeamento porem terei que refazer a validacao no tb04
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define AUTO AUTO
#define BREAK BREAK
#define CASE CASE
#define CHAR CHAR
#define CONST CONST
#define CONTINUE 6
#define DEFAULT 7
#define DO 8
#define DOUBLE 9
#define ELSE 10
#define ENUM 11
#define EXTERN 12
#define FLOAT 13
#define FOR 14
#define GOTO 15
#define IF 16
#define INT 17
#define LONG 18
#define REGISTER 19
#define RETURN 20
#define SHORT 21
#define SIGNED 22
#define SIZEOF 23
#define STATIC 24
#define STRUCT 25
#define SWITCH 26
#define TYPEDEF 27
#define UNION 28
#define UNSIGNED 29
#define VOID 30
#define VOLATILE 31
#define WHILE 32

#define IDENTIFICADOR 99
#define NUMERO 98
#define STRING 97
#define CARACTER 96
#define OPERADOR 95
#define DELIMITADOR 94 
#define COMENTARIO 93
#define ERRO 92

//ideia principal

typedef struct node_dados Node;
typedef struct list List;
bool isNull(const List *l);
Node *create_node (char caracter);
List *create_list();
void insere_dados(List *l, char letra);
void print(const List *list);
//void print_token(const List *list);
//void exluir_lista(List **ref_l);
void validar_token(List *l);

int main (){
    FILE *arq;
    arq = fopen("arq.c", "r");
    
    List *lista[50]; // lista de palavras
    int i; // contador da lista, cada i vai ser uma palavra
    
    if (arq == NULL){
        printf("erro ao abrir o arquivo!\n");
        exit(1);
    }

    lista[i] = create_list();
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
            while(aux == ' ' || aux == '\n' || aux == '\t'){
                if(aux == ' ') {
                    i++;
                    lista[i] = create_list();
                    aux = fgetc(arq);
                    insere_dados(lista[i], aux);
                }
                aux = fgetc(arq);
            }
            aux = fgetc(arq);
        }
    }

    printf("lista de palavras: \n");
    i=0;
    while(lista[i] != NULL){
        print(lista[i]);
        i++;
        printf("\n");
    }
    printf("\n\nlista de caracteres: \n");
    print(list_caracter);
    printf("\n\nlista de numeros: \n");
    print(list_num);
    printf("\n\nlista de frases: \n");
    print(frase);
    printf("\n------------------------------------------------------------------------------------------------\n");/*

    /*for(int j=0; j<3; j++){
        print(lista[j]);
        validar_token(lista[j]);
    }*/

    //validar_token(lista[0]);

    fclose(arq);
    printf("\n\n");

    return 0;
}

// criar uma funcao para definir os token do arquivo de saida

typedef struct  node_dados {
    char letras;
    struct node_dados *next;
    struct node_dados *prev;
}Node;

typedef struct list {
    Node *inicio, *fim;
    long int size;
    char token;
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
    l->token = 0;
    l->size = 0;

    return l;
}

void insere_dados(List *l, char letra){
    Node *aux = create_node(letra);

    if(isNull(l))l->inicio = l->fim = aux;
    else{
        l->fim->next = aux; 
        aux->prev = l->fim; 
        l->fim = aux;
    }
}

void print(const List *list){
    Node *p = list->inicio;
    if(p != NULL){
        while(p != NULL){
            printf("| %c |", p->letras);
            p = p->next;
        }
        printf("->");
    }
}


void validar_token(List *l){
    Node *p = l->inicio;

    while (p != NULL){
        if (p->letras == 'a'){ // token -> auto
            p = p->next;
            if (p != NULL && p->letras == 'u'){
                p = p->next;
                if (p != NULL && p->letras == 't'){
                    p = p->next;
                    if(p != NULL && p->letras == 'o' && p->next == NULL){
                        printf("token -> auto\n");
                    }
                    else {
                        printf("token -> identificador\n");
                    }
                }
            }
        }

        if (p->letras == 'b'){ // token -> break
            p = p->next;
            if (p != NULL && p->letras == 'r'){
                p = p->next;
                if (p != NULL && p->letras == 'e'){
                    p = p->next;
                    if(p != NULL && p->letras == 'a'){
                        p = p->next;
                        if(p != NULL && p->letras == 'k' && p->next == NULL){
                            printf("token -> break\n");
                        }
                        else {
                            printf("token -> identificador\n");
                        }
                    }
                }
            }
        }

        if (p->letras == 'c'){ // token -> case
            p = p->next;
            if (p != NULL && p->letras == 'a'){
                p = p->next;
                if (p != NULL && p->letras == 's'){
                    p = p->next;
                    if(p != NULL && p->letras == 'e' && p->next == NULL){
                        printf("token -> case\n");
                    }
                    else {
                        printf("token -> identificador case\n");
                    }
                }
            }
            else if (p != NULL && p->letras == 'h'){ // token -> char
                p = p->next;
                if (p != NULL && p->letras == 'a'){
                    p = p->next;
                    if (p != NULL && p->letras == 'r' && p->next == NULL){
                        printf("token -> char\n");
                    }
                    else {
                        printf("token -> identificador char\n");
                    }
                }
            }
            else if(p != NULL && p->letras == 'o'){ // token -> const
                p = p->next;
                if (p != NULL && p->letras == 'n'){
                    p = p->next;
                    if (p != NULL && p->letras == 's'){
                        p = p->next;
                        if (p != NULL && p->letras == 't' && p->next == NULL){
                            printf("token -> const\n");
                        }
                        else {
                            printf("token -> identificador const\n");
                        }
                    }
                    else if (p != NULL && p->letras == 't'){ // token -> continue
                        p = p->next;
                        if (p != NULL && p->letras == 'i'){
                            p = p->next;
                            if (p != NULL && p->letras == 'n'){
                                p = p->next;
                                if (p != NULL && p->letras == 'u'){
                                    p = p->next;
                                    if (p != NULL && p->letras == 'e' && p->next == NULL){
                                        printf("token -> continue\n");
                                    }
                                    else {
                                        printf("token -> identificador continue\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if(p->letras == 'd'){ //token -> default
            p = p->next;
            if(p != NULL && p->letras == 'e'){
                p = p->next;
                if(p != NULL && p->letras == 'f'){
                    p = p->next;
                    if(p != NULL && p->letras == 'a'){
                        p = p->next;
                        if(p != NULL && p->letras == 'u'){
                            p = p->next;
                            if(p != NULL && p->letras == 'l'){
                                p = p->next;
                                if(p != NULL && p->letras == 't' && p->next == NULL){
                                    printf("token -> default\n");
                                }
                                else {
                                    printf("token -> identificador default\n");
                                }
                            }
                        }
                    }
                }
            }
            else if(p != NULL && p->letras == 'o' && p->next == NULL){ // token ->do
                printf("token -> do\n"); //fazer um identificador para o do
            }
            else if(p != NULL && p->letras == 'o'){ // token -> double
                p = p->next;
                if(p->next != NULL && p->letras == 'u'){
                    p = p->next;
                    if(p != NULL && p->letras == 'b'){
                        p = p->next;
                        if(p != NULL && p->letras == 'l'){
                            p = p->next;
                            if(p != NULL && p->letras == 'e' && p->next == NULL){
                                printf("token -> double\n");
                            }
                            else {
                                printf("token -> identificador double\n");
                            }
                        }
                    }
                }   
            }
        }

        if(p->letras == 'e'){ 
            p = p->next;
            if(p != NULL && p->letras == 'l'){ //token else
                p = p->next;
                if(p != NULL && p->letras == 's'){
                    p = p->next;
                    if(p != NULL && p->letras == 'e' && p->next == NULL){
                        printf("token -> else\n");
                    }
                    else{
                        printf("token -> identificador else\n");
                    }
                }
            } 
            else if(p != NULL && p->letras == 'n'){
                p = p->next;
                if(p != NULL && p->letras == 'u'){
                    p = p->next;
                    if(p != NULL && p->letras == 'm' && p->next == NULL){
                        printf("token -> enum\n");
                    }
                    else{
                        printf("token -> identificador enum\n");
                    }
                }
            }
            else if(p != NULL && p->letras == 'x'){ //token -> extern
                p = p->next;
                if(p != NULL && p->letras == 't'){
                    p = p->next;
                    if(p != NULL && p->letras == 'e'){
                        p = p->next;
                        if(p != NULL && p->letras == 'r'){
                            p = p->next;
                            if(p != NULL && p->letras == 'n' && p->next == NULL){
                                printf("token -> extern\n");
                            }
                            else {
                                printf("token -> identificador extern\n");
                            }
                        }
                    }
                }
            }
        }

        if(p->letras == 'f'){
            p = p->next;
            if(p != NULL && p->letras == 'l'){
                p = p->next;
                if(p != NULL && p->letras == 'o'){
                    p = p->next;
                    if(p != NULL && p->letras == 'a'){
                        p = p->next;
                        if(p != NULL && p->letras == 't' && p->next == NULL){
                            printf("token -> float\n");
                        }
                        else {
                            printf("token -> identificador float\n");
                        }
                    }
                }
            }
        }

        p = p->next;
    }
}

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