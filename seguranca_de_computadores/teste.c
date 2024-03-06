#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

//primeiro passo, escolher dois numeros primos grandes e distintos denotados como p e q, depois calcule o valor de N
int achar_n(int p, int q){
    return p*q;
}

//segundo passo: totiente de n
int return_totiente(int p, int q){
    return (p-1) * (q-1);
}

//terceiro passo, fazer o mdc ou verificar se eh primo, fazer sua contagem.
//verificar num primo para o "E"
bool eh_primo(int num){
    if (num <= 1)
        return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}

//se ambos forem primos basta fazer (p-1) * (q e-1), se nao forem, tera que fazer o MDC
bool verificar_nums_primos_p_q(int p, int q){
    if (p <= 1 || q <= 1) {
        printf("Um dos números não é primo.\n");
        return false;
    }
    
    if (!eh_primo(p)) {
        printf("%d não é primo.\n", p);
        return false;
    }

    if (!eh_primo(q)) {
        printf("%d não é primo.\n", q);
        return false;
    }

    return true;
}

//calcular MDc caso nao sejam primos
int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mdc_de_nao_primo(int num){
    int result = 0;
    for (int i = 2; i < num; ++i) {
        if (num % i == 0) {
            result = mdc(num, i);
            break;
        }
    }
    return result;
}


//agora acha o "E"
int achar_e(int n, int totiente){
    int *mod = malloc(100 * sizeof(int)); // Alocando dinamicamente memória para o vetor mod
    if (mod == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    int aux_armazena=0; // Aqui definimos um array mod com espaço suficiente para armazenar valores
    for(int i=totiente; i>=0; i--){
        if(mdc(i,totiente) == 1){
            if(mdc(i,n) == 1){
                if(eh_primo(i)){
                    mod[aux_armazena] = i; // Armazenamos o valor diretamente no array mod
                    aux_armazena++;
                }
            }
        }
    }

    int tam_pont = aux_armazena; // Usamos o tamanho real do array mod, que é o valor de aux_armazena
    
    srand(time(NULL));

    int indice_aleatorio = rand() % tam_pont;

    int e = mod[indice_aleatorio];
    free(mod); // Liberando a memória alocada para o vetor mod

    return e;
}

int main (){
    int p_main=3, q_main=11;
    printf("P: %d\nQ: %d\n", p_main, q_main);

    printf("N: %d\n", achar_n(p_main,q_main));

    printf("totiente: %d\n", return_totiente(p_main,q_main));

    verificar_nums_primos_p_q(p_main,q_main);

    printf("E:%d\n",achar_e(achar_n(p_main, q_main), return_totiente(p_main, q_main)));

    return 0;
}