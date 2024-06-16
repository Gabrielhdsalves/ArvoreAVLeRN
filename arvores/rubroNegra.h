#ifndef RUBRONEGRA_RUBRONEGRA_H
#define RUBRONEGRA_RUBRONEGRA_H

typedef struct no no;

typedef struct rubro rubro;
typedef struct resultados resultados;

rubro *arvRNcriaRubro();

no *arvRNcriaNo(int chave, rubro *rubro);

int arvRNinsereNo(rubro *rubro, int chave, resultados *results);

int arvRNremoveNo(rubro *rubro, int chave, resultados *results);

void arvRNatualizaCor_Insercao(rubro *rubro, no *novoNo, resultados *results);

void arvRNatualizaCor_Removido(rubro *rubro, no *noRemovido, resultados *results);

void arvRNimprimeOrdem(no *raiz);

void arvRNimprimePreOrdem(no *raiz);

no *arvRNgetRaiz(rubro *rubro);

void arvRNrotacaoDireita(rubro *rubro, no *y);

void arvRNrotacaoEsquerda(rubro *rubro, no *y);

int pesquisaRubro(rubro *arvRN, int chave);

#endif
