#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


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

    if(ta_vazia){
        l->fim = l->fim = novo;
    } else {
        l->fim->next = novo;
        l->fim = l->fim->next;
    }
}

int main (){
    struct lista *main = criar_lista();

    add(main, 'b');
    add(main, 'i');
    add(main, 'a');

    return 0;
}