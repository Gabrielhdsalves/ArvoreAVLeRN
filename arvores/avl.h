#ifndef INC_7_AVL_AVL_H
#define INC_7_AVL_AVL_H

typedef struct resultados resultados;

typedef struct no no;
typedef struct avl avl;

avl *AVLcriaArvore();

int AVLinsereNo(avl *arv, int valor, resultados *results);

int AVLremoveNo(avl *arv, int valor, resultados *results);

void AVLimprimeOrdem(no *raiz);

void AVLimprimePreOrdem(no *raiz);

no *AVLgetRaiz(avl *arv);

int AVLgetNumElementos(avl *arv);

void AVLatualizaFB_insercao(avl *arv, no *novoNo, resultados *results);

void AVLbalanceamento(avl *arv, no *noDesbal, resultados *results, int tipo);

void AVLrotacaoDir(no *noDesbal);

void AVLrotacaoEsq(no *noDesbal);

void AVLatualizaFB_remocao(avl *arv, no *pai, int chaveRemovida, resultados *results);

int pesquisaAVL(avl *arv, int chave);


#endif