#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

bool memoria_desalocada = false;
//--------------------------LISTA ENCADEADA----------------------

struct node{
    char letras; //criar o nome/email e afins
    struct node *next;
};

struct lista{
    struct node *inicio, *fim;
};

struct node *criar_no(char letra){
    struct node *no = (struct node*)calloc(1, sizeof(struct node));
    no->letras = letra;
    no->next = NULL;

    return no;
}

struct lista *criar_lista(){
    struct lista *l = (struct lista*)calloc(1, sizeof(struct lista));
    l->inicio = NULL;
    l->fim = NULL;

    return l;
}

bool ta_vazia(const struct lista *l){
    return l->inicio == NULL;
}

void add(struct lista *l, char letra){
    struct node *novo = criar_no(letra);

    if(ta_vazia(l)){
        l->inicio = l->fim = novo;
    } else {
        l->fim->next = novo;
        l->fim = l->fim->next;
    }
}

void imprime(const struct lista *l){
    struct node *aux = l->inicio;

    while(aux != NULL){
        printf("%c", aux->letras);
        aux = aux->next;
    }
}

void exluir_lista(struct lista **l, int i){
    struct node *ponteiro = l[i]->inicio;
    struct node *aux = NULL;
    
    while (ponteiro != NULL){
        aux = ponteiro->next;
        free(ponteiro);
        ponteiro = aux;
    }

    free(l[i]);
    l[i] = NULL;

    bool memoria_desalocada = true; 
}

//---------------------------LEITURA DO ARQUIVO--------------------------
void leitura_arquivo(struct lista **l) {
    FILE *file = fopen("entrada_email_beatriz.csv", "r");

    if (file == NULL) {
        fprintf(stderr, "(FUNCAO)ERRO: arquivo nao encontrado! ");
        exit(1);
    }

    int tam = 2, cont_adj = 0, cont_email = 0;
    char *email = (char *)malloc(tam * sizeof(char));
    char aux_leitura = fgetc(file);
    l[cont_adj] = criar_lista();

    while (aux_leitura != EOF) {
        if (aux_leitura == ',') {
            email[cont_email] = '\0'; // Finaliza o e-mail
            cont_email = 0;
            cont_adj++;
            l[cont_adj] = criar_lista();
        } else {
            if (cont_email >= tam - 1) { 
                tam *= 2;
                email = (char *)realloc(email, tam * sizeof(char));
            }
            email[cont_email] = aux_leitura; 
            add(l[cont_adj], aux_leitura); 
            cont_email++;
        }
        aux_leitura = fgetc(file);
    }

    free(email);
    fclose(file);
}

int main (){
   /* teste de validacao de add da funcao inicial
    struct  lista *main = criar_lista();
    add(main, 'b');
    add(main, 'e');
    add(main, 'a');
    add(main, 't');
    add(main, 'r');
    add(main, 'i');
    add(main, 'z');

    imprime(main);

    // for (int i = 0; i <=8; i++) {
    //     exluir_lista(&main, i);
    // }

    exluir_lista(&main, 0);

    printf("\n");
    -----------------------------------------------------------------------------------------*/

    FILE *file = fopen("entrada_email_beatriz.csv", "r");

    //------so pra deixar dinamico com o tamanho do arquivo-------
    if(file == NULL){
        fprintf(stderr, "(MAIN)ERRO: arquivo nao encontrado! ");
        exit(1);
    }
    int cont_linha = 0, cont_virg=0;
    char aux = fgetc(file);

    while(aux != EOF){
        if(aux == '\n'){
            cont_linha+=1;
        }
        if (aux == ','){
            cont_virg++;
        }
        aux = fgetc(file);
    }
    fclose(file);

    //inicio da estrutura geral da lista
    struct lista **main = (struct lista**)malloc(cont_linha * sizeof(struct lista*));

    leitura_arquivo(main);

    printf("linha: %d\nvirgula: %d\n", cont_linha, cont_virg);
    for (int i = 0; i < cont_virg; i++) {
        printf("Lista de adjacência do vértice %d: ", i);
        imprime(main[i]);
        printf("\n");
    }

    return 0;
}