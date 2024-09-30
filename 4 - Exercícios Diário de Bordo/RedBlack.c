// CÓDIGO FEITO POR PEDRO HENRIQUE GOMES CHAGAS
// CC6N - ESTRUTURA DE DADOS II 
// ÁRVORE REDBLACK

#include <stdio.h>
#include <stdlib.h>

typedef enum { VERMELHO, PRETO } Cor;

typedef struct No {
    int chave;
    Cor cor;
    struct No *esq, *dir, *pai;
} No;

No* novoNo(int chave) {
    No *no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->cor = VERMELHO;
    no->esq = no->dir = no->pai = NULL;
    return no;
}

// Rotaciona à esquerda
void rotacionarEsquerda(No **raiz, No *x) {
    No *y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL) y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL) *raiz = y;
    else if (x == x->pai->esq) x->pai->esq = y;
    else x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

// Rotaciona à direita
void rotacionarDireita(No **raiz, No *x) {
    No *y = x->esq;
    x->esq = y->dir;
    if (y->dir != NULL) y->dir->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL) *raiz = y;
    else if (x == x->pai->dir) x->pai->dir = y;
    else x->pai->esq = y;
    y->dir = x;
    x->pai = y;
}

// Balanceia a árvore após inserção
void balancearArvore(No **raiz, No *z) {
    while (z != *raiz && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            No *tio = z->pai->pai->dir;
            if (tio != NULL && tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacionarEsquerda(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionarDireita(raiz, z->pai->pai);
            }
        } else {
            No *tio = z->pai->pai->esq;
            if (tio != NULL && tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacionarDireita(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionarEsquerda(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

// Insere um novo nó na árvore Red-Black
void inserirRB(No **raiz, int chave) {
    No *novo = novoNo(chave);
    No *pai = NULL;
    No *atual = *raiz;

    while (atual != NULL) {
        pai = atual;
        if (novo->chave < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    novo->pai = pai;
    if (pai == NULL)
        *raiz = novo;
    else if (novo->chave < pai->chave)
        pai->esq = novo;
    else
        pai->dir = novo;

    balancearArvore(raiz, novo);
}

// Imprime a árvore em ordem
void imprimirInOrdem(No *raiz) {
    if (raiz != NULL) {
        imprimirInOrdem(raiz->esq);
        printf("%d (%s) ", raiz->chave, raiz->cor == VERMELHO ? "R" : "B");
        imprimirInOrdem(raiz->dir);
    }
}

// Imprime a árvore com profundidade
void imprimirArvore(No *raiz, int espacos) {
    if (raiz != NULL) {
        imprimirArvore(raiz->dir, espacos + 5);
        for (int i = 0; i < espacos; i++) printf(" ");
        printf("%d (%s)\n", raiz->chave, raiz->cor == VERMELHO ? "R" : "B");
        imprimirArvore(raiz->esq, espacos + 5);
    }
}

int main() {
    No *raiz = NULL;
    int valores[] = {10, 20, 30, 15, 25, 5, 1, 12, 18, 35};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        inserirRB(&raiz, valores[i]);
    }

    printf("Árvore Red-Black In-Ordem:\n");
    imprimirInOrdem(raiz);
    printf("\n\n");

    printf("Árvore Red-Black Estrutura:\n");
    imprimirArvore(raiz, 0);

    return 0;
}
