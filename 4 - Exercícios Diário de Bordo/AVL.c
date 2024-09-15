// CÓDIGO FEITO POR PEDRO HENRIQUE GOMES CHAGAS
// CC6N - ESTRUTURA DE DADOS II 
// ÁRVORE AVL

#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó da árvore AVL
typedef struct NodoAVL {
    int valor;
    struct NodoAVL *esq;
    struct NodoAVL *dir;
    int alt;
} NodoAVL;

// Função para criar e inicializar um novo nó
NodoAVL *criarNodo(int valor) {
    NodoAVL *novoNodo = (NodoAVL *)malloc(sizeof(NodoAVL));
    if (novoNodo == NULL) {
        printf("Erro: Falha ao alocar memória para o nó.\n");
        exit(-1);
    }
    novoNodo->valor = valor;
    novoNodo->esq = NULL;
    novoNodo->dir = NULL;
    novoNodo->alt = 0;
    return novoNodo;
}

// Obter a altura de um nó
int obterAltura(NodoAVL *nodo) {
    return nodo ? nodo->alt : -1;
}

// Calcular o fator de balanceamento de um nó
int fatorDeBalanceamento(NodoAVL *nodo) {
    return nodo ? obterAltura(nodo->esq) - obterAltura(nodo->dir) : 0;
}

// Rotação simples à direita para balancear
NodoAVL *rotacionarParaDireita(NodoAVL *nodo) {
    NodoAVL *novoTopo = nodo->esq;
    nodo->esq = novoTopo->dir;
    novoTopo->dir = nodo;
    
    nodo->alt = 1 + (obterAltura(nodo->esq) > obterAltura(nodo->dir) ? obterAltura(nodo->esq) : obterAltura(nodo->dir));
    novoTopo->alt = 1 + (obterAltura(novoTopo->esq) > obterAltura(novoTopo->dir) ? obterAltura(novoTopo->esq) : obterAltura(novoTopo->dir));
    
    return novoTopo;
}

// Rotação simples à esquerda para balancear
NodoAVL *rotacionarParaEsquerda(NodoAVL *nodo) {
    NodoAVL *novoTopo = nodo->dir;
    nodo->dir = novoTopo->esq;
    novoTopo->esq = nodo;
    
    nodo->alt = 1 + (obterAltura(nodo->esq) > obterAltura(nodo->dir) ? obterAltura(nodo->esq) : obterAltura(nodo->dir));
    novoTopo->alt = 1 + (obterAltura(novoTopo->esq) > obterAltura(novoTopo->dir) ? obterAltura(novoTopo->esq) : obterAltura(novoTopo->dir));
    
    return novoTopo;
}

// Ajustar o balanceamento da árvore após inserção ou remoção
NodoAVL *ajustarBalanceamento(NodoAVL *raiz, int valorInserido) {
    raiz->alt = 1 + (obterAltura(raiz->esq) > obterAltura(raiz->dir) ? obterAltura(raiz->esq) : obterAltura(raiz->dir));
    int bal = fatorDeBalanceamento(raiz);
    
    if (bal > 1 && valorInserido < raiz->esq->valor) {
        return rotacionarParaDireita(raiz);
    }
    if (bal < -1 && valorInserido > raiz->dir->valor) {
        return rotacionarParaEsquerda(raiz);
    }
    if (bal > 1 && valorInserido > raiz->esq->valor) {
        raiz->esq = rotacionarParaEsquerda(raiz->esq);
        return rotacionarParaDireita(raiz);
    }
    if (bal < -1 && valorInserido < raiz->dir->valor) {
        raiz->dir = rotacionarParaDireita(raiz->dir);
        return rotacionarParaEsquerda(raiz);
    }
    
    return raiz;
}

// Inserir um novo nó na árvore AVL
NodoAVL *inserirNodo(NodoAVL *raiz, int valor) {
    if (!raiz) {
        return criarNodo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esq = inserirNodo(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserirNodo(raiz->dir, valor);
    } else {
        return raiz; // Valor duplicado não permitido
    }
    
    return ajustarBalanceamento(raiz, valor);
}

// Encontrar o nó com o menor valor
NodoAVL *encontrarMinimo(NodoAVL *nodo) {
    NodoAVL *atual = nodo;
    while (atual && atual->esq) {
        atual = atual->esq;
    }
    return atual;
}

// Remover um nó da árvore AVL
NodoAVL *removerNodo(NodoAVL *raiz, int valor) {
    if (!raiz) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esq = removerNodo(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = removerNodo(raiz->dir, valor);
    } else {
        if (!raiz->esq) {
            NodoAVL *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (!raiz->dir) {
            NodoAVL *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        NodoAVL *temp = encontrarMinimo(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir = removerNodo(raiz->dir, temp->valor);
    }
    
    return ajustarBalanceamento(raiz, valor);
}

// Exibir a árvore de forma estruturada com indentação
void exibirArvoreEstruturada(NodoAVL *nodo, int espacos) {
    if (nodo) {
        exibirArvoreEstruturada(nodo->dir, espacos + 1);
        for (int i = 0; i < espacos; i++) {
            printf("   ");
        }
        printf("%d\n", nodo->valor);
        exibirArvoreEstruturada(nodo->esq, espacos + 1);
    }
}

// Função principal com inserções e remoções simplificadas
int main() {
    NodoAVL *raiz = NULL;
    int valoresInserir[] = {30, 24, 20, 35, 27, 33, 38, 25, 22, 34, 40, 29};
    int valoresRemover[] = {24, 35, 27, 30};

    // Inserir valores
    for (int i = 0; i < sizeof(valoresInserir) / sizeof(valoresInserir[0]); i++) {
        raiz = inserirNodo(raiz, valoresInserir[i]);
    }
    exibirArvoreEstruturada(raiz, 3);

    // Remover valores
    for (int i = 0; i < sizeof(valoresRemover) / sizeof(valoresRemover[0]); i++) {
        printf("\nRemovendo %d...\n", valoresRemover[i]);
        raiz = removerNodo(raiz, valoresRemover[i]);
        exibirArvoreEstruturada(raiz, 3);
    }

    return 0;
}
