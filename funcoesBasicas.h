#ifndef RUBRONEGRA_FUNCOESBASICAS_H
#define RUBRONEGRA_FUNCOESBASICAS_H

#include "rubroNegra.h"
#include "avl.h"

typedef struct resultados resultados;

resultados *criaResults();
void addRotacoesRemocoes(resultados *results, int tipoArv, int qtdRotacoes);
void addRotacoesInsercoes(resultados *results, int tipoArv, int qtdRotacoes);
void exibirResultados(resultados *results);

void geraMensagens();
void geraMenu(rubro *arvRN, avl *arvAVL, int tipoArvore, resultados *results);
void geraVetorOrdenado(int valorInicial, int valorFinal, int valorIncrementado, char *nomeArq);
void geraVetorAleatorio(char *nomeArq, int maxValor);
int processaCarga(avl *arv, rubro *arvRN,char *nomeArquivo, int tipo, int tipoArvore, resultados *results);

#endif
