#include<stdio.h>
#include<stdbool.h>

//primeiro passo, escolher dois numeros primos grandes e distintos denotados como p e q, depois calcule o valor de N
int achar_n(int p, int q){
    return p*q;
}

int main (){
    int p_main=3, q_main=11;
    
    printf("%d\n", achar_n(p_main,q_main));

    verificar_nums_primos_p_q(p_main,q_main);

    return 0;
}