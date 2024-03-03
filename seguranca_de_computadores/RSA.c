#include<stdio.h>
#include<stdbool.h>

//primeiro/segundo passo, escolher dois numeros primos grandes e distintos denotados como p e q, depois calcule o valor de N
int achar_n(int p, int q){
    return p*q;
}

//terceiro passo: totiente de n
int return_totiente(int p, int q){
    return (p-1) * (q-1);
}

//quarto passo, fazer o mdc ou verificar se eh primo, fazer sua contagem.
//verificar num primo para o "E"
bool eh_primo(int num) {
    if (num <= 1)
        return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}


int main (){
    int p_main=3, q_main=11;
    
    printf("P: %d\nQ: %d\n", p_main, q_main);

    printf("N: %d\n", achar_n(p_main,q_main));

    printf("totiente: %d\n", return_totiente(p_main,q_main));


    return 0;
}