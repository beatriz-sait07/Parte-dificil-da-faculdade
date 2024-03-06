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
    int tam;
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
    l->tam = 0;

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
                email = (char *)realloc(email, tam * sizeof(char)); //aumentando o tamanho dinamicamente
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

void verifica_email(struct lista **l, struct lista *p, struct lista *e, int i) {
    struct node *aux = l[i]->inicio;
    struct node *aux_p = p->inicio, *aux_e = e->inicio;

    while (aux != NULL) {
        printf("entrou laco GERAL\n");
        if (aux->letras >= 'a' && aux->letras <= 'z') {
            printf("entrou condicao 000\n");
            aux = aux->next;
            while (aux != NULL && aux->letras >= 'a' && aux->letras <= 'z') {
                aux = aux->next;
                if (aux != NULL && aux->letras == '@') { // Verifica '@' e '@' maiúsculo
                    printf("entrou condicao 222\n");
                    aux = aux->next;
                    if (aux != NULL) {
                        printf("entrou condicao 333\n");
                        if (aux->letras == aux_e->letras) {
                            printf("entrou condicao 444\n");
                            aux = aux->next;
                            aux_e = aux_e->next;
                            do {
                                printf("entrou do");
                                if (aux->letras == aux_e->letras) {
                                    printf("entrou condicao 555\n");
                                    aux = aux->next;
                                    aux_e = aux_e->next;
                                } //bota o else
                            } while (aux != NULL && aux_e != NULL);
                            if(aux == NULL && aux_e == NULL){
                                printf("Email Dicente: ");
                                imprime(l[i]);
                            }

                        } else if (aux->letras == aux_p->letras) {
                            aux = aux->next;
                            aux_e = aux_e->next;
                            do {
                                if (aux != NULL && aux_e != NULL && aux->letras == aux_e->letras) {
                                    aux = aux->next;
                                    aux_e = aux_e->next;
                                } //bota o else
                            } while (aux != NULL && aux_e != NULL);
                                if(aux == NULL && aux_e == NULL){
                                printf("Email Docente: ");
                                imprime(l[i]);
                            }
                        } else {
                            printf("Email nao institucional do IFMS! \n");
                        }
                    }
                    break;
                }
            } // Verificação sobrenome
            if (aux != NULL && aux->letras >= 'a' && aux->letras <= 'z') {
                printf("entrou condicao 111\n");
                aux = aux->next;
                while (aux != NULL && aux->letras >= 'a' && aux->letras <= 'z') {
                    aux = aux->next;
                } // Verificação caso haja números em sobrenomes
                if (aux != NULL && aux->letras >= '0' && aux->letras <= '9') {
                    aux = aux->next;
                }
                while (aux != NULL && aux->letras >= '0' && aux->letras <= '9') {
                    aux = aux->next;
                }
            }
        }
        if (aux != NULL) {
            aux = aux->next;
        }
    }
}


int main (){
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

    //inicio da estrutura geral da lista + listas para auxiliar na verificacao.
    struct lista **main = (struct lista**)malloc(cont_virg * sizeof(struct lista*));
    struct lista *estudante = criar_lista();
    struct lista *prof = criar_lista();
    char e[21] = "estudante.ifms.edu.br";
    char p[12] = "ifms.edu.br";

    for(int i=0; i<21; i++){ //laco para add letra a letra em estudantes
        add(estudante, e[i]);
    }
    for(int i=0; i<12; i++){ // laco para add letra a letra em prof
        add(prof, p[i]);
    }


    // imprime(estudante);
    // printf("\n");
    // imprime(prof);
    // printf("\n");

    leitura_arquivo(main);

    printf("linha: %d\nvirgula: %d\n", cont_linha, cont_virg);
    
    for (int i = 0; i < cont_virg; i++) {
        printf("Lista %d: ", i);
        imprime(main[i]);
        printf("\n");
    }

    verifica_email(main, estudante, prof, 1);
    return 0;
}