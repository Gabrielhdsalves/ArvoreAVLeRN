#include <stdio.h>
#include "stdlib.h"
#include "funcoesBasicas.h"
#include "rubroNegra.h"
#include "avl.h"

void geraMensagens() {
    int resposta;
    int valorInicial;
    int valorFinal;
    int valorIncrementado;
    char nomeArquivo[50];

    printf("Voce gostaria de gerar o vetor? \n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    scanf(" %d", &resposta);

    if(resposta == 1) {
        printf("Digite o nome do arquivo:");
        scanf(" %s", nomeArquivo);

        printf("Digite o valor Inicial:");
        scanf(" %d", &valorInicial);

        printf("Digite o valor Final:");
        scanf(" %d", &valorFinal);

        printf("Digite o valor de Incrementacao:");
        scanf(" %d", &valorIncrementado);

        geraVetorOrdenado(valorInicial, valorFinal,valorIncrementado,nomeArquivo);
    }
    printf("\n");
}

void imprimirResultados(rubro *arvRN, avl *arvAVL, int tipoArvore) {
    if(tipoArvore == 0) {
        printf("\nAVL - Em Ordem\n");
        AVLimprimeOrdem(AVLgetRaiz(arvAVL));
        printf("\nAVL - Pre Ordem\n");
        AVLimprimePreOrdem(AVLgetRaiz(arvAVL));
    } else if (tipoArvore == 1) {
        printf("\nRubro Negra - Em Ordem\n");
        arvRNimprimeOrdem(arvRNgetRaiz(arvRN));
        printf("\nRubro Negra - Pre Ordem\n");
        arvRNimprimePreOrdem(arvRNgetRaiz(arvRN));
    } else {
        printf("\nAVL - Em Ordem\n");
        AVLimprimeOrdem(AVLgetRaiz(arvAVL));
        printf("\nAVL - Pre Ordem\n");
        AVLimprimePreOrdem(AVLgetRaiz(arvAVL));

        printf("\nRubro Negra - Em Ordem\n");
        arvRNimprimeOrdem(arvRNgetRaiz(arvRN));
        printf("\nRubro Negra - Pre Ordem\n");
        arvRNimprimePreOrdem(arvRNgetRaiz(arvRN));
    }
}

void geraMenu(rubro *arvRN, avl *arvAVL, int tipoArvore) {
    char nomeArq[50];

    printf("Digite o nome do arquivo que deseja utilizar para inserir:");
    scanf(" %s", nomeArq);
    processaCarga(arvAVL, arvRN,nomeArq, 1, tipoArvore); // 1 Para Inserir
    imprimirResultados(arvRN, arvAVL, tipoArvore);

    printf("\nDigite o nome do arquivo que deseja utilizar para remover:");
    scanf(" %s", nomeArq);
    processaCarga(arvAVL, arvRN,nomeArq, 2, tipoArvore); // 2 para Remover
    imprimirResultados(arvRN, arvAVL, tipoArvore);
}


void geraVetorOrdenado(int valorInicial, int valorFinal, int valorIncrementado, char *nomeArq) {
    FILE *arquivo = fopen(nomeArq, "w+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    for (int i = valorInicial; i < valorFinal; i += valorIncrementado) {
        fprintf(arquivo, "%d\n", i);
    }

    fclose(arquivo);
}

int processaCarga(avl *arv, rubro *arvRN, char *nomeArquivo, int tipo, int tipoArvore) {
    int verificador = 0, retorno = 0;
    if (arv == NULL || arvRN == NULL || nomeArquivo == NULL) {
        fprintf(stderr, "Parâmetros inválidos.\n");
        return -1;
    }

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return -2;
    }

    int valor;
    if (tipo == 1) { // Inserção
        while (fscanf(arquivo, "%d", &valor) == 1) {
            if (tipoArvore == 0) { // Apenas AVL
                retorno += AVLinsereNo(arv, valor);
                verificador++;
            } else if (tipoArvore == 1) { // Apenas RubroNegra
                retorno += arvRNinsereNo(arvRN, valor);
                verificador++;
            } else { // Ambas
                retorno += AVLinsereNo(arv, valor);
                retorno += arvRNinsereNo(arvRN, valor);
                verificador = verificador + 2;
            }
        }

        if(verificador == retorno) {
            return 1;
        } else {
            return 0;
        }

    } else { // Remoção
        while (fscanf(arquivo, "%d", &valor) == 1) {
            if (tipoArvore == 0) { // Apenas AVL
                retorno += AVLremoveNo(arv, valor);
                verificador++;
            } else if (tipoArvore == 1) { // Apenas RubroNegra
                retorno += arvRNremoveNo(arvRN, valor);
                verificador++;
            } else { // Ambas
                retorno += AVLremoveNo(arv, valor);
                retorno += arvRNremoveNo(arvRN, valor);
                verificador = verificador + 2;
            }
        }

        if(verificador == retorno) {
            return 1;
        } else {
            return 0;
        }
    }



    fclose(arquivo);
    return 0;
}