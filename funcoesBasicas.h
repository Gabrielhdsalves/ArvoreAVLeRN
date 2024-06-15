#ifndef RUBRONEGRA_FUNCOESBASICAS_H
#define RUBRONEGRA_FUNCOESBASICAS_H

#include "rubroNegra.h"
#include "avl.h"

void geraMensagens();
void geraMenu(rubro *arvRN, avl *arvAVL, int tipoArvore);
void geraVetorOrdenado(int valorInicial, int valorFinal, int valorIncrementado, char *nomeArq);
int processaCarga(avl *arv, rubro *arvRN,char *nomeArquivo, int tipo, int tipoArvore);


#endif //RUBRONEGRA_FUNCOESBASICAS_H
