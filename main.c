#include <stdio.h>
#include <stdlib.h>
#include "rubroNegra.h"
#include "funcoesBasicas.h"

int main(void) {
    rubro *arvRN;
    avl *arvAVL;
    arvRN = arvRNcriaRubro();
    arvAVL = AVLcriaArvore();


    if(!arvRN || !arvAVL) {
        printf("Falha ao alocar árvore");
        return 0;
    }

    geraMensagens();
    geraMenu(arvRN, arvAVL, 3);


    return 1;
}