#include<stdio.h>
#include<stdbool.h>

//primeiro passo, escolher dois numeros primos grandes e distintos denotados como p e q, depois calcule o valor de N
int achar_n(int p, int q){
    return p*q;
}

//verificar num primo para o totienti
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
    
    printf("%d\n", achar_n(p_main,q_main));


    return 0;
}