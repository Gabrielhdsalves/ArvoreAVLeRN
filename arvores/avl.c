//
// Created by gabhe on 29/05/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct no {
    int chave;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
    int fb;
};
struct avl {
    struct no *sentinela;
    int numElementos;
};

avl *AVLcriaArvore() {
    avl *arv = (avl *) malloc(sizeof(avl));

    if(!arv){
       return NULL;
    }

    arv->sentinela = (no*) malloc(sizeof (no));

    if(!arv->sentinela) {
       free(arv);
       return NULL;
    }

    arv->sentinela->Fdir = NULL;
    arv->sentinela->Fesq = NULL;
    arv->sentinela->pai = NULL;
    arv->sentinela->fb = 0;
    arv->numElementos = 0;
    arv->sentinela->chave = -1000;

    return arv;
}

int AVLinsereNo(avl *arv, int valor) {
    no *novoNo = (no*) malloc(sizeof(no));
    no *aux;

    if(!novoNo) {
        return 0;
    }

    novoNo->pai = arv->sentinela;
    novoNo->Fdir = NULL;
    novoNo->Fesq = NULL;
    novoNo->fb = 0;
    novoNo->chave = valor;

    if(!arv->sentinela->Fdir) {
        arv->sentinela->Fdir = novoNo;
        return 1;
    }

    aux = arv->sentinela->Fdir;
    while(aux) {
        novoNo->pai = aux;
        if(aux->chave > novoNo->chave) {
            aux = aux->Fesq;
        } else {
            aux = aux->Fdir;
        }
    }

    if(novoNo->pai->chave > novoNo->chave) {
        novoNo->pai->Fesq = novoNo;
    } else {
        novoNo->pai->Fdir = novoNo;
    }

    AVLatualizaFB_insercao(arv, novoNo);

    return 1;
}

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Retorna -1 caso o elemento a ser removido não esteja na árvore
int AVLremoveNo(avl *arv, int valor) {
    no *aux;
    no *proxNo;
    int auxValor;

    if(!arv->sentinela->Fdir) {
        return 0;
    }

    aux = arv->sentinela->Fdir;
    while(aux && aux->chave != valor) {
        if(aux->chave > valor) {
            aux = aux->Fesq;
        } else {
            aux = aux->Fdir;
        }
    }

    if(!aux) {
        return -1;
    }

    arv->numElementos--;

    if(!aux->Fdir && !aux->Fesq) {
        if(aux->pai->chave > valor) {
            aux->pai->Fesq = NULL;
        } else {
            aux->pai->Fdir = NULL;
        }
        AVLatualizaFB_remocao(arv, aux->pai, valor);
        free(aux);
        return 1;
    }
    if(!aux->Fdir) {
        if(aux->pai->chave > valor){
            aux->pai->Fesq = aux->Fesq;
        } else {
            aux->pai->Fdir = aux->Fesq;
        }
        aux->Fesq->pai = aux->pai;
        AVLatualizaFB_remocao(arv, aux->pai, valor);
        free(aux);
        return 1;
    }
    if(!aux->Fesq) {
        if(aux->pai->chave > valor){
            aux->pai->Fesq = aux->Fdir;
        } else {
            aux->pai->Fdir = aux->Fdir;
        }
        aux->Fdir->pai = aux->pai;
        AVLatualizaFB_remocao(arv, aux->pai, valor);
        free(aux);
        return 1;
    }

    proxNo = aux->Fdir;
    // Procurando o no mais a esquerda da árvore direita;
    while(proxNo->Fesq) {
        proxNo = proxNo->Fesq;
    }

    // Substituindo de lugar do no que queremos remover
    aux->chave = proxNo->chave;
    if (proxNo->pai == aux)
    {
        aux->Fdir = proxNo->Fdir;
        if (proxNo->Fdir)
        {
            proxNo->Fdir->pai = aux;
        }

    } else {
        proxNo->pai->Fesq = proxNo->Fdir;
        if (proxNo->Fdir)
        {
            proxNo->Fdir->pai = proxNo->pai;
        }
    }

    AVLatualizaFB_remocao(arv, proxNo->pai, proxNo->chave);
    free(proxNo);
    return 1;
}

void AVLimprimeOrdem(no *raiz){
    if (raiz){
        AVLimprimeOrdem(raiz->Fesq);
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        AVLimprimeOrdem(raiz->Fdir);
    }
}

void AVLimprimePreOrdem(no *raiz){
    if (raiz){
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        AVLimprimePreOrdem(raiz->Fesq);
        AVLimprimePreOrdem(raiz->Fdir);
    }
}

no *AVLgetRaiz(avl *arv){
    return arv->sentinela->Fdir;
}

int AVLgetNumElementos(avl *arv){
    return arv->numElementos;
}




//Função que verifica o desbalanceamento na inserção
void AVLatualizaFB_insercao(avl *arv, no *novoNo) {
    no *aux = novoNo;
    do {
        if(aux->pai->chave > novoNo->chave ) {
            aux->pai->fb--;
        } else {
            aux->pai->fb++;
        }
        aux = aux->pai;
    } while(aux->fb != 2 && aux->fb != -2 && aux != arv->sentinela->Fdir && aux->fb != 0);

    if (aux->fb == 2 || aux->fb == -2){
        AVLbalanceamento(arv, aux);
    }
}

//Função que faz o balanceamento após inseção
void AVLbalanceamento(avl *arv, no *noDesbal) {
    no *filho, *neto;
    int fbNeto;
    if(noDesbal->fb == 2) {
        filho = noDesbal->Fdir;
        if (filho->fb == -1) {
            neto = filho->Fesq;
            fbNeto = neto->fb;
            neto->fb = 0;
            AVLrotacaoDir(filho);
            AVLrotacaoEsq(noDesbal);
            if(fbNeto == -1) {
                filho->fb = 1;
                noDesbal->fb = 0;
            } else if(fbNeto == 1) {
                noDesbal->fb = -1;
                filho->fb = 0;
            } else {
                noDesbal->fb = 0;
                filho->fb = 0;
            }
        } else {
            AVLrotacaoEsq(noDesbal);
            if(filho->fb == 1) {
                noDesbal->fb = 0;
                filho->fb = 0;
            } else {
                noDesbal->fb = 1;
                filho->fb = -1;
            }
        }
    } else {
        filho = noDesbal->Fesq;
        if (filho->fb == 1) {
            neto = filho->Fdir;
            fbNeto = neto->fb;
            neto->fb = 0;
            AVLrotacaoEsq(filho);
            AVLrotacaoDir(noDesbal);
            if(fbNeto == -1) {
                filho->fb = 0;
                noDesbal->fb = 1;
            } else if(fbNeto == 1) {
                noDesbal->fb = 0;
                filho->fb = -1;
            } else {
                noDesbal->fb = 0;
                filho->fb = 0;
            }
        } else {
            AVLrotacaoDir(noDesbal);
            if(filho->fb == -1) {
                noDesbal->fb = 0;
                filho->fb = 0;
            } else {
                noDesbal->fb = -1;
                filho->fb = 1;
            }
        }
    }
}

//Função que implementa a rotação à direita
void AVLrotacaoDir(no *noDesbal) {
    no *neto = noDesbal->Fesq->Fdir;
    if(noDesbal->pai->chave > noDesbal->chave) {
        noDesbal->pai->Fesq = noDesbal->Fesq;
    } else {
        noDesbal->pai->Fdir = noDesbal->Fesq;
    }

    noDesbal->Fesq->pai = noDesbal->pai;
    noDesbal->pai = noDesbal->Fesq;
    noDesbal->Fesq->Fdir = noDesbal;

    noDesbal->Fesq = neto;
    if(neto) {
        neto->pai = noDesbal;
    }
}

//Função que implementa a rotação à esquerda
void AVLrotacaoEsq(no *noDesbal) {
    no *neto = noDesbal->Fdir->Fesq;
    if(noDesbal->pai->chave > noDesbal->chave) {
        noDesbal->pai->Fesq = noDesbal->Fdir;
    } else {
        noDesbal->pai->Fdir = noDesbal->Fdir;
    }
    noDesbal->Fdir->pai = noDesbal->pai;
    noDesbal->pai = noDesbal->Fdir;
    noDesbal->Fdir->Fesq = noDesbal;

    noDesbal->Fdir = neto;
    if(neto) {
        neto->pai = noDesbal;
    }
}

//Função que verifica o desbalanceamento na remoção
void AVLatualizaFB_remocao(avl *arv, no *pai, int chaveRemovida) {
    no *aux = pai;
    if(aux == arv->sentinela) {
        return;
    }

    if(aux->chave > chaveRemovida ) {
        aux->fb++;
    } else {
        aux->fb--;
    }

    while(aux->fb == 0 && aux != arv->sentinela->Fdir) {
        aux = aux->pai;
        if(chaveRemovida < aux->chave) {
            aux->fb++;
        } else {
            aux->fb--;
        }
    }

    if(aux->fb == 2 || aux->fb == -2) {
        AVLbalanceamento(arv, aux);
        if((aux->pai != arv->sentinela ) && (aux->pai->fb == 0)) {
            AVLatualizaFB_remocao(arv, aux->pai->pai, chaveRemovida);
        }
    }
}