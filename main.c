#include <stdio.h>
#include "rubroNegra.h"
#include "funcoesBasicas.h"

int main(void) {
    rubro *arvRN;
    avl *arvAVL;
    resultados *rtResultados = criaResults();

    arvRN = arvRNcriaRubro();
    arvAVL = AVLcriaArvore();

    if(!arvRN || !arvAVL) {
        printf("Falha ao alocar árvore");
        return 0;
    }

    geraMensagens();
    geraMenu(arvRN, arvAVL, 3, rtResultados);
    exibirResultados(rtResultados);
    return 1;
}