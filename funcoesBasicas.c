#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoesBasicas.h"
#include "rubroNegra.h"
#include "avl.h"

struct resultados {
    long double tempoInsercao[2];
    long double tempoRemocao[2];
    long double tempoPesquisa[2];
    int rotacoesInsercao[2];
    int rotacoesRemocao[2];
};

resultados *criaResults() {
    resultados *results = (resultados*) malloc(sizeof(resultados));
    if (!results) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    results->tempoInsercao[0] = results->tempoInsercao[1] = 0.0;
    results->tempoRemocao[0] = results->tempoRemocao[1] = 0.0;
    results->tempoPesquisa[0] = results->tempoPesquisa[1] = 0.0;
    results->rotacoesInsercao[0] = results->rotacoesInsercao[1] = 0;
    results->rotacoesRemocao[0] = results->rotacoesRemocao[1] = 0;

    return results;
}

void addRotacoesInsercoes(resultados *results, int tipoArv, int qtdRotacoes) {
    if (tipoArv) {
        results->rotacoesInsercao[1] += qtdRotacoes; // Rotações na inserção da RubroNegra
    } else {
        results->rotacoesInsercao[0] += qtdRotacoes; // Rotações na inserção da AVL
    }
}

void addRotacoesRemocoes(resultados *results, int tipoArv, int qtdRotacoes) {
    if (tipoArv) {
        results->rotacoesRemocao[1] += qtdRotacoes; // Rotações na remoção da RubroNegra
    } else {
        results->rotacoesRemocao[0] += qtdRotacoes; // Rotações na remoção da AVL
    }
}

void exibirResultados(resultados *results) {
    printf("----------------------------------------------------------AVL--------------------------------------------------------\n");
    printf("|    Rotacoes-Insercao    |    Rotacoes-Remocao    |    Tempo-Insercao    |    Tempo-Remocao    |   Tempo-Pesquisa  |\n");
    printf("            %d                %d                       %Lf                 %Lf             %Lf\n", results->rotacoesInsercao[0], results->rotacoesRemocao[0], results->tempoInsercao[0], results->tempoRemocao[0], results->tempoPesquisa[0]);

    printf("---------------------------------------------------RubroNegra----------------------------------------------------------\n");
    printf("|    Rotacoes-Insercao    |    Rotacoes-Remocao    |    Tempo-Insercao    |    Tempo-Remocao    |   Tempo-Pesquisa  |\n");
    printf("            %d                %d                       %Lf                 %Lf             %Lf\n", results->rotacoesInsercao[1], results->rotacoesRemocao[1], results->tempoInsercao[1], results->tempoRemocao[1], results->tempoPesquisa[1]);
}

void geraMensagens() {
    int resposta;
    int valorInicial;
    int valorFinal;
    int valorIncrementado;
    int valorMax;
    char nomeArquivo[50], nomeArquivoPesquisa[50];

    printf("Voce gostaria de gerar o vetor de insercao? \n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    scanf(" %d", &resposta);

    if (resposta == 1) {
        printf("Digite o nome do arquivo de insercao:");
        scanf(" %49s", nomeArquivo);

        printf("\nDigite o valor Inicial:");
        scanf(" %d", &valorInicial);

        printf("\nDigite a quantidade de numeros:");
        scanf(" %d", &valorFinal);

        printf("\nDigite o valor de Incrementacao:");
        scanf(" %d", &valorIncrementado);

        geraVetorOrdenado(valorInicial, valorFinal, valorIncrementado, nomeArquivo);
        resposta = 2;
    }

    printf("Voce gostaria de gerar o vetor de pesquisa?? \n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    scanf(" %d", &resposta);

    if (resposta == 1) {
        printf("\nDigite o nome do arquivo de pesquisa:");
        scanf(" %49s", nomeArquivoPesquisa);

        printf("\nDigite o valor maximo aleatorio:");
        scanf(" %d", &valorMax);

        geraVetorAleatorio(nomeArquivoPesquisa, valorMax);
        resposta = 2;
    }

    printf("Voce gostaria de gerar o vetor de remocao? \n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    scanf(" %d", &resposta);

    if (resposta == 1) {
        printf("\nDigite o nome do arquivo de remocao:");
        scanf("%49s", nomeArquivo);

        printf("\nDigite o valor Inicial:");
        scanf(" %d", &valorInicial);

        printf("\nDigite a quantidade de numeros:");
        scanf(" %d", &valorFinal);

        printf("\nDigite o valor de Incrementacao:");
        scanf(" %d", &valorIncrementado);

        geraVetorOrdenado(valorInicial, valorFinal, valorIncrementado, nomeArquivo);
        resposta = 2;
    }
    printf("\n");
}

void imprimirResultados(rubro *arvRN, avl *arvAVL, int tipoArvore) {
    if (tipoArvore == 0) {
        printf("\nAVL - Em Ordem\n");
        AVLimprimeOrdem(AVLgetRaiz(arvAVL));
    } else if (tipoArvore == 1) {
        printf("\nRubro Negra - Em Ordem\n");
        arvRNimprimeOrdem(arvRNgetRaiz(arvRN));
    } else {
        printf("\nAVL - Em Ordem\n");
        AVLimprimeOrdem(AVLgetRaiz(arvAVL));
        printf("\nRubro Negra - Em Ordem\n");
        arvRNimprimeOrdem(arvRNgetRaiz(arvRN));
    }
}

void geraMenu(rubro *arvRN, avl *arvAVL, int tipoArvore, resultados *results) {
    char nomeArq[50];

    printf("Digite o nome do arquivo que deseja utilizar para inserir: ");
    scanf(" %49s", nomeArq);
    processaCarga(arvAVL, arvRN, nomeArq, 1, tipoArvore, results); // 1 Para Inserir
    //imprimirResultados(arvRN, arvAVL, tipoArvore);

    printf("\nDigite o nome do arquivo que deseja utilizar para pesquisa: ");
    scanf(" %49s", nomeArq);

    processaCarga(arvAVL, arvRN, nomeArq, 3, tipoArvore, results); // 3 para pesquisa

    printf("\nDigite o nome do arquivo que deseja utilizar para remover: ");
    scanf(" %49s", nomeArq);
    processaCarga(arvAVL, arvRN, nomeArq, 2, tipoArvore, results); // 2 para Remover
    //imprimirResultados(arvRN, arvAVL, tipoArvore);
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

void geraVetorAleatorio(char *nomeArq, int maxValor){
    FILE *arquivo = fopen(nomeArq, "w+");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < maxValor; i++) {
        fprintf(arquivo, "%d\n", rand() % maxValor);
    }

    fclose(arquivo);
}

int processaCarga(avl *arv, rubro *arvRN, char *nomeArquivo, int tipo, int tipoArvore, resultados *results) {
    int verificador = 0, retorno = 0, pesquisa = 0;
    clock_t inicio, fim;

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
                inicio = clock();
                retorno += AVLinsereNo(arv, valor, results);
                fim = clock();
                results->tempoInsercao[0] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);
                verificador++;
            } else if (tipoArvore == 1) { // Apenas RubroNegra
                inicio = clock();
                retorno += arvRNinsereNo(arvRN, valor, results);
                fim = clock();
                results->tempoInsercao[1] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);
                verificador++;
            } else { // Ambas
                inicio = clock();
                retorno += AVLinsereNo(arv, valor, results);
                fim = clock();
                results->tempoInsercao[0] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);

                inicio = clock();
                retorno += arvRNinsereNo(arvRN, valor, results);
                fim = clock();
                results->tempoInsercao[1] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);

                verificador++;
            }
        }
    } else if (tipo == 2) { // Remoção
        while (fscanf(arquivo, "%d", &valor) == 1) {
            if (tipoArvore == 0) { // Apenas AVL
                inicio = clock();
                retorno += AVLremoveNo(arv, valor, results);
                fim = clock();
                results->tempoRemocao[0] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);
                verificador++;
            } else if (tipoArvore == 1) { // Apenas RubroNegra
                inicio = clock();
                retorno += arvRNremoveNo(arvRN, valor, results);
                fim = clock();
                results->tempoRemocao[1] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);
                verificador++;
            } else { // Ambas
                inicio = clock();
                retorno += AVLremoveNo(arv, valor, results);
                fim = clock();
                results->tempoRemocao[0] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);

                inicio = clock();
                retorno += arvRNremoveNo(arvRN, valor, results);
                fim = clock();
                results->tempoRemocao[1] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);

                verificador++;
            }
        }
    } else if(tipo == 3){
        while (fscanf(arquivo, "%d", &valor) == 1) {
            if (tipoArvore == 0) { // Apenas AVL
                inicio = clock();
                retorno += pesquisaAVL(arv, valor);
                fim = clock();
                results->tempoPesquisa[0] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);
                verificador++;
            } else if (tipoArvore == 1) { // Apenas RubroNegra
                inicio = clock();
                retorno += pesquisaRubro(arvRN, valor);
                fim = clock();
                results->tempoPesquisa[1] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);
                verificador++;
            } else { // Ambas
                inicio = clock();
                retorno += pesquisaAVL(arv, valor);
                fim = clock();
                results->tempoPesquisa[0] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);

                inicio = clock();
                retorno += pesquisaRubro(arvRN, valor);
                fim = clock();
                results->tempoPesquisa[1] += ((long double) (fim - inicio) / CLOCKS_PER_SEC);

                pesquisa = 1;
                verificador += 2;
            }
        }
    }

    if(pesquisa) {
        if(verificador == retorno) {
            printf("\nTodas os elementos encontrados!\n");
        } else {
            printf("\n%d nao encontrados!\n", (verificador - retorno)/2);
        }

    } else if (verificador > 0) {
        printf("\nQuantidade de registros processados: %d\n", verificador);
    }

    fclose(arquivo);
    return retorno;
}
