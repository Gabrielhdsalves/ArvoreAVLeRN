#include "rubroNegra.h"
#include <stdio.h>
#include <stdlib.h>

struct no {
    int chave;
    no *Fdir;
    no *Fesq;
    no *pai;
    char cor;
};

struct rubro {
    no *sentinela;
    no *nulo;
    int qtdElementos;
};

//Cria uma árvore rubronegra e retorna um ponteiro para ela
rubro *arvRNcriaRubro() {
    rubro *arvRN = (rubro*) malloc(sizeof(rubro));

    if(!arvRN) {
        return NULL;
    }

    arvRN->sentinela = (no*) malloc(sizeof(no));

    if(!arvRN->sentinela) {
        free(arvRN);
        return NULL;
    }

    arvRN->nulo = (no*) malloc(sizeof(no));

    if(!arvRN->nulo) {
        free(arvRN);
        return NULL;
    }

    arvRN->qtdElementos = 0;

    // Sentinela
    arvRN->sentinela->Fdir = arvRN->sentinela->Fesq = arvRN->sentinela->pai = NULL;
    arvRN->sentinela->cor = 'P';
    arvRN->sentinela->chave = -1000;

    // Nó nulo
    arvRN->nulo->Fdir = arvRN->nulo->Fesq = arvRN->nulo->pai = NULL;
    arvRN->nulo->cor = 'P';
    arvRN->nulo->chave = -1000;

    return arvRN;
}

//Cria um novo nó e retorna um ponteiro para ele
no *arvRNcriaNo(int chave, rubro *arvRN){
    no *novoNo = (no*) malloc(sizeof (no));

    if(novoNo){
        novoNo->chave = chave;
        novoNo->Fdir = novoNo->Fesq = arvRN->nulo;
        novoNo->pai = arvRN->sentinela;
        novoNo->cor = 'V';
        arvRN->qtdElementos++;
    } else {
        printf("Erro ao Alocar no!");
        return NULL;
    }

    return novoNo;
}

//Função para inserir um novo nó na árvora, retorna 0 caso haja algum erro e retorna 1 caso seja feita a inserção
int arvRNinsereNo(rubro *arvRN, int chave) {
    no *novoNo = arvRNcriaNo(chave, arvRN);
    no *aux;

    if(!novoNo) {
        return 0;
    }

    if(!arvRN->sentinela->Fdir) {
        arvRN->sentinela->Fdir = novoNo;
        novoNo->cor = 'P';
        return 1;
    }

    aux = arvRN->sentinela->Fdir;

    while(aux && aux != arvRN->nulo) {
        novoNo->pai = aux;
        if(aux->chave > chave) {
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

    if(novoNo->pai->cor == 'V') {
        arvRNatualizaCor_Insercao(arvRN, novoNo);
    }

    return 1;
}

void arvRNtransplanta(rubro *arvRN, no *u, no *v) {
    if (u->pai == arvRN->sentinela) {
        arvRN->sentinela->Fdir = v;
    } else if (u == u->pai->Fesq) {
        u->pai->Fesq = v;
    } else {
        u->pai->Fdir = v;
    }
    v->pai = u->pai;
}

no* arvRNprocuraSucessor(no *x, rubro *arvRN) {

    while (x->Fesq != arvRN->nulo) {
        x = x->Fesq;
    }
    return x;
}

//Função para remover um nó da árvore rubronegra, retorna 0 em caso de erro na remoção e 1 em caso de sucesso
int arvRNremoveNo(rubro *arvRN, int chave) {
    no *noRemovido = arvRN->sentinela->Fdir;
    no *x, *sucessorY;

    // Procurar o nó a ser removido
    while (noRemovido != arvRN->nulo && noRemovido->chave != chave) {
        if (noRemovido->chave > chave) {
            noRemovido = noRemovido->Fesq;
        } else {
            noRemovido = noRemovido->Fdir;
        }
    }

    // Nó não encontrado
    if (noRemovido == arvRN->nulo) {
        printf("O no não esta na rubro!\n");
        return 0;
    }

    sucessorY = noRemovido;
    char sucessorY_original_cor = sucessorY->cor;

    if (noRemovido->Fesq == arvRN->nulo) {
        x = noRemovido->Fdir;
        arvRNtransplanta(arvRN, noRemovido, noRemovido->Fdir);
    } else if (noRemovido->Fdir == arvRN->nulo) {
        x = noRemovido->Fesq;
        arvRNtransplanta(arvRN, noRemovido, noRemovido->Fesq);
    } else {
        sucessorY = arvRNprocuraSucessor(noRemovido->Fdir, arvRN);
        sucessorY_original_cor = sucessorY->cor;
        x = sucessorY->Fdir;

        if (sucessorY->pai == noRemovido) {
            x->pai = sucessorY;
        } else {
            arvRNtransplanta(arvRN, sucessorY, sucessorY->Fdir);
            sucessorY->Fdir = noRemovido->Fdir;
            sucessorY->Fdir->pai = sucessorY;
        }

        arvRNtransplanta(arvRN, noRemovido, sucessorY);
        sucessorY->Fesq = noRemovido->Fesq;
        sucessorY->Fesq->pai = sucessorY;
        sucessorY->cor = noRemovido->cor;
    }

    if (sucessorY_original_cor == 'P') {
        arvRNatualizaCor_Removido(arvRN, x);
    }

    free(noRemovido);
    arvRN->qtdElementos--;
    return 1;
}



void arvRNatualizaCor_Insercao(rubro *arvRN, no *novoNo) {
    while (novoNo != arvRN->sentinela && novoNo->pai->cor == 'V') {
        no *pai = novoNo->pai;
        no *avo = pai->pai;

        if (pai == avo->Fesq) { // Esquerda do avô
            no *tio = avo->Fdir;

            if (tio->cor == 'V') { // Primeiro caso
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                novoNo = avo;
            } else {
                if (novoNo == pai->Fdir) { // Segundo caso
                    arvRNrotacaoEsquerda(arvRN, pai);
                    novoNo = pai;
                    pai = novoNo->pai;
                } // Terceiro caso
                pai->cor = 'P';
                avo->cor = 'V';
                arvRNrotacaoDireita(arvRN, avo);
            }
        } else { // Direita do avô
            no *tio = avo->Fesq;

            if (tio->cor == 'V') { // Primeiro caso
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                novoNo = avo;
            } else {
                if (novoNo == pai->Fesq) { // Segundo caso
                    arvRNrotacaoDireita(arvRN, pai);
                    novoNo = pai;
                    pai = novoNo->pai;
                } // Terceiro caso
                pai->cor = 'P';
                avo->cor = 'V';
                arvRNrotacaoEsquerda(arvRN, avo);
            }
        }
    }
    arvRN->sentinela->Fdir->cor = 'P';
}

void arvRNatualizaCor_Removido(rubro *arvRN, no *x) {
    while (x != arvRN->sentinela->Fdir && x->cor == 'P') {
        if (x == x->pai->Fesq) {
            no *w = x->pai->Fdir;
            if (w->cor == 'V') {
                w->cor = 'P';
                x->pai->cor = 'V';
                arvRNrotacaoEsquerda(arvRN, x->pai);
                w = x->pai->Fdir;
            }
            if (w->Fesq->cor == 'P' && w->Fdir->cor == 'P') {
                w->cor = 'V';
                x = x->pai;
            } else {
                if (w->Fdir->cor == 'P') {
                    w->Fesq->cor = 'P';
                    w->cor = 'V';
                    arvRNrotacaoDireita(arvRN, w);
                    w = x->pai->Fdir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'P';
                w->Fdir->cor = 'P';
                arvRNrotacaoEsquerda(arvRN, x->pai);
                x = arvRN->sentinela->Fdir;
            }
        } else {
            no *w = x->pai->Fesq;
            if (w->cor == 'V') {
                w->cor = 'P';
                x->pai->cor = 'V';
                arvRNrotacaoDireita(arvRN, x->pai);
                w = x->pai->Fesq;
            }
            if (w->Fesq->cor == 'P' && w->Fdir->cor == 'P') {
                w->cor = 'V';
                x = x->pai;
            } else {
                if (w->Fesq->cor == 'P') {
                    w->Fdir->cor = 'P';
                    w->cor = 'V';
                    arvRNrotacaoEsquerda(arvRN, w);
                    w = x->pai->Fesq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'P';
                w->Fesq->cor = 'P';
                arvRNrotacaoDireita(arvRN, x->pai);
                x = arvRN->sentinela->Fdir;
            }
        }
    }
    x->cor = 'P';
}



void arvRNimprimeOrdem(no *raiz){
    if (raiz && raiz->chave != -1000){
        arvRNimprimeOrdem(raiz->Fesq);
        printf("%d - %d - %c\n", raiz->chave, raiz->pai->chave, raiz->cor);
        arvRNimprimeOrdem(raiz->Fdir);
    }
}

void arvRNimprimePreOrdem(no *raiz) {
    if (raiz && raiz->chave != -1000){
        printf("%d - %d - %c\n", raiz->chave, raiz->pai->chave, raiz->cor);
        arvRNimprimePreOrdem(raiz->Fesq);
        arvRNimprimePreOrdem(raiz->Fdir);
    }
}

no *arvRNgetRaiz(rubro *arvRN) {
    return arvRN->sentinela->Fdir;
}

void arvRNrotacaoEsquerda(rubro *arvRN, no *x) {
    no *y = x->Fdir;
    x->Fdir = y->Fesq;
    if (y->Fesq != arvRN->nulo) {
        y->Fesq->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == arvRN->nulo) {
        arvRN->sentinela->Fdir = y;
    } else if (x == x->pai->Fesq) {
        x->pai->Fesq = y;
    } else {
        x->pai->Fdir = y;
    }
    y->Fesq = x;
    x->pai = y;
}

void arvRNrotacaoDireita(rubro *arvRN, no *x) {
    no *y = x->Fesq;
    x->Fesq = y->Fdir;
    if (y->Fdir != arvRN->nulo) {
        y->Fdir->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == arvRN->nulo) {
        arvRN->sentinela->Fdir = y;
    } else if (x == x->pai->Fdir) {
        x->pai->Fdir = y;
    } else {
        x->pai->Fesq = y;
    }
    y->Fdir = x;
    x->pai = y;
}
