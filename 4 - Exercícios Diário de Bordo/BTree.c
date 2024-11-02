// CÓDIGO FEITO POR PEDRO HENRIQUE GOMES CHAGAS
// CC6N - ESTRUTURA DE DADOS II 
// ÁRVORE 'B-Tree'

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 5  // Ordem da árvore B, define o máximo de filhos

// Estrutura de um nó da árvore B
struct NoBTree {
    int numChaves;                        // Número de chaves no nó
    int chaves[ORDEM - 1];                // Array de chaves no nó
    struct NoBTree *filhos[ORDEM];        // Array de ponteiros para os filhos
    int folha;                            // Booleano: 1 se o nó é folha, 0 caso contrário
};

// Função para criar um novo nó na árvore B
struct NoBTree *criarNo(int folha) {
    struct NoBTree *novoNo = (struct NoBTree *)malloc(sizeof(struct NoBTree));
    novoNo->numChaves = 0;
    novoNo->folha = folha;

    for (int i = 0; i < ORDEM; i++)
        novoNo->filhos[i] = NULL;

    return novoNo;
}

// Função auxiliar para dividir um nó cheio e promover a chave mediana
void dividirNo(struct NoBTree *pai, int i, struct NoBTree *filho) {
    struct NoBTree *novoNo = criarNo(filho->folha);
    novoNo->numChaves = ORDEM / 2 - 1;

    for (int j = 0; j < ORDEM / 2 - 1; j++)
        novoNo->chaves[j] = filho->chaves[j + ORDEM / 2];

    if (!filho->folha) {
        for (int j = 0; j < ORDEM / 2; j++)
            novoNo->filhos[j] = filho->filhos[j + ORDEM / 2];
    }

    filho->numChaves = ORDEM / 2 - 1;

    for (int j = pai->numChaves; j >= i + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    pai->filhos[i + 1] = novoNo;

    for (int j = pai->numChaves - 1; j >= i; j--)
        pai->chaves[j + 1] = pai->chaves[j];
    pai->chaves[i] = filho->chaves[ORDEM / 2 - 1];
    pai->numChaves++;
}

// Função para inserir uma nova chave na árvore B
void inserirNaBTree(struct NoBTree **raiz, int chave) {
    if ((*raiz)->numChaves == ORDEM - 1) {
        struct NoBTree *novaRaiz = criarNo(0);
        novaRaiz->filhos[0] = *raiz;
        dividirNo(novaRaiz, 0, *raiz);
        int i = (novaRaiz->chaves[0] < chave) ? 1 : 0;
        inserirNaNaoCheia(novaRaiz->filhos[i], chave);
        *raiz = novaRaiz;
    } else {
        inserirNaNaoCheia(*raiz, chave);
    }
}

// Função auxiliar para inserir em um nó não cheio
void inserirNaNaoCheia(struct NoBTree *no, int chave) {
    int i = no->numChaves - 1;

    if (no->folha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        while (i >= 0 && chave < no->chaves[i])
            i--;
        i++;
        if (no->filhos[i]->numChaves == ORDEM - 1) {
            dividirNo(no, i, no->filhos[i]);
            if (chave > no->chaves[i])
                i++;
        }
        inserirNaNaoCheia(no->filhos[i], chave);
    }
}

// Função para buscar uma chave na árvore B
struct NoBTree *buscar(struct NoBTree *no, int chave) {
    int i = 0;
    while (i < no->numChaves && chave > no->chaves[i])
        i++;

    if (i < no->numChaves && no->chaves[i] == chave)
        return no;

    if (no->folha)
        return NULL;

    return buscar(no->filhos[i], chave);
}

// Função para imprimir a árvore B em pré-ordem
void imprimirPreOrdem(struct NoBTree *no) {
    int i;
    for (i = 0; i < no->numChaves; i++) {
        if (!no->folha)
            imprimirPreOrdem(no->filhos[i]);
        printf("%d ", no->chaves[i]);
    }
    if (!no->folha)
        imprimirPreOrdem(no->filhos[i]);
}

// Função principal para testar a árvore B
int main() {
    struct NoBTree *raiz = criarNo(1);

    int chaves[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(chaves) / sizeof(chaves[0]);

    for (int i = 0; i < n; i++)
        inserirNaBTree(&raiz, chaves[i]);

    printf("Árvore B em pré-ordem:\n");
    imprimirPreOrdem(raiz);

    int chaveParaBuscar = 20;
    struct NoBTree *resultadoBusca = buscar(raiz, chaveParaBuscar);
    if (resultadoBusca != NULL)
        printf("\nChave %d encontrada na árvore B.\n", chaveParaBuscar);
    else
        printf("\nChave %d não encontrada na árvore B.\n", chaveParaBuscar);

    return 0;
}
