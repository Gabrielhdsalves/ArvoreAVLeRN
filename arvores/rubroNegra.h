#ifndef RUBRONEGRA_RUBRONEGRA_H
#define RUBRONEGRA_RUBRONEGRA_H

typedef struct no no;

typedef struct rubro rubro;

rubro *arvRNcriaRubro();

no *arvRNcriaNo(int chave, rubro *rubro);

int arvRNinsereNo(rubro *rubro, int chave);

int arvRNremoveNo(rubro *rubro, int chave);

void arvRNatualizaCor_Insercao(rubro *rubro, no *novoNo);

void arvRNatualizaCor_Removido(rubro *rubro, no *noRemovido);

void arvRNimprimeOrdem(no *raiz);

void arvRNimprimePreOrdem(no *raiz);

no *arvRNgetRaiz(rubro *rubro);

void arvRNrotacaoDireita(rubro *rubro, no *y);

void arvRNrotacaoEsquerda(rubro *rubro, no *y);

#endif //RUBRONEGRA_RUBRONEGRA_H
