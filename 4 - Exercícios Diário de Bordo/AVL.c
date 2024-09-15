// CÓDIGO FEITO POR PEDRO HENRIQUE GOMES CHAGAS
// CC6N - ESTRUTURA DE DADOS II 
// ÁRVORE AVL

#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura de um nó da árvore AVL
typedef struct NodoAVL {
    int valor;
    struct NodoAVL *esq;
    struct NodoAVL *dir;
    int alt;
} NodoAVL;

// Alocando memória e inicializando um novo nó
NodoAVL *criarNodo(int valor) {
    NodoAVL *novoNodo = (NodoAVL *)malloc(sizeof(NodoAVL));
    if (novoNodo == NULL) {
        printf("Erro: Não foi possível alocar memória para o nó.\n");
        exit(-1);
    }
    novoNodo->valor = valor;
    novoNodo->esq = NULL;
    novoNodo->dir = NULL;
    novoNodo->alt = 0;  // altura inicial do nó
    return novoNodo;
}

// Obter a altura de um nó
int obterAltura(NodoAVL *nodo) {
    return nodo ? nodo->alt : -1;
}

// Calcula o fator de balanceamento de um nó
int fatorDeBalanceamento(NodoAVL *nodo) {
    return nodo ? obterAltura(nodo->esq) - obterAltura(nodo->dir) : 0;
}

// Rotação simples para a direita para balanceamento
NodoAVL *rotacionarParaDireita(NodoAVL *nodo) {
    NodoAVL *novoTopo = nodo->esq;
    nodo->esq = novoTopo->dir;
    novoTopo->dir = nodo;

    // Atualiza as alturas após a rotação
    nodo->alt = 1 + (obterAltura(nodo->esq) > obterAltura(nodo->dir) ? obterAltura(nodo->esq) : obterAltura(nodo->dir));
    novoTopo->alt = 1 + (obterAltura(novoTopo->esq) > obterAltura(novoTopo->dir) ? obterAltura(novoTopo->esq) : obterAltura(novoTopo->dir));

    return novoTopo;
}

// Rotação simples para a esquerda para balanceamento
NodoAVL *rotacionarParaEsquerda(NodoAVL *nodo) {
    NodoAVL *novoTopo = nodo->dir;
    nodo->dir = novoTopo->esq;
    novoTopo->esq = nodo;

    // Atualiza as alturas após a rotação
    nodo->alt = 1 + (obterAltura(nodo->esq) > obterAltura(nodo->dir) ? obterAltura(nodo->esq) : obterAltura(nodo->dir));
    novoTopo->alt = 1 + (obterAltura(novoTopo->esq) > obterAltura(novoTopo->dir) ? obterAltura(novoTopo->esq) : obterAltura(novoTopo->dir));

    return novoTopo;
}

// Balancear a árvore, aplicando rotações, se necessário
NodoAVL *ajustarBalanceamento(NodoAVL *raiz, int valorInserido) {
    raiz->alt = 1 + (obterAltura(raiz->esq) > obterAltura(raiz->dir) ? obterAltura(raiz->esq) : obterAltura(raiz->dir));
    int bal = fatorDeBalanceamento(raiz);

    // Rotação à direita, se estiver desbalanceado à esquerda
    if (bal > 1 && valorInserido < raiz->esq->valor) {
        return rotacionarParaDireita(raiz);
    }

    // Rotação à esquerda, se estiver desbalanceado à direita
    if (bal < -1 && valorInserido > raiz->dir->valor) {
        return rotacionarParaEsquerda(raiz);
    }

    // Rotação dupla esquerda-direita
    if (bal > 1 && valorInserido > raiz->esq->valor) {
        raiz->esq = rotacionarParaEsquerda(raiz->esq);
        return rotacionarParaDireita(raiz);
    }

    // Rotação dupla direita-esquerda
    if (bal < -1 && valorInserido < raiz->dir->valor) {
        raiz->dir = rotacionarParaDireita(raiz->dir);
        return rotacionarParaEsquerda(raiz);
    }

    return raiz;
}

// Função de inserção na árvore AVL
NodoAVL *inserirNodo(NodoAVL *raiz, int valor) {
    if (!raiz) {
        return criarNodo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esq = inserirNodo(raiz->esq, valor); // Insere à esquerda
    } else if (valor > raiz->valor) {
        raiz->dir = inserirNodo(raiz->dir, valor); // Insere à direita
    } else {
        return raiz;  // Evita duplicatas
    }

    // Ajusta balanceamento após inserção
    return ajustarBalanceamento(raiz, valor);
}

// Encontrar o nó com o valor mínimo
NodoAVL *encontrarMinimo(NodoAVL *nodo) {
    NodoAVL *atual = nodo;
    while (atual && atual->esq) {
        atual = atual->esq;
    }
    return atual;
}

// Encontrar o nó com o valor máximo
NodoAVL *encontrarMaximo(NodoAVL *nodo) {
    NodoAVL *atual = nodo;
    while (atual && atual->dir) {
        atual = atual->dir;
    }
    return atual;
}

// Função para remover um nó da árvore AVL
NodoAVL *removerNodo(NodoAVL *raiz, int valor) {
    if (!raiz) {
        return raiz;  // Caso base: árvore vazia
    }

    if (valor < raiz->valor) {
        raiz->esq = removerNodo(raiz->esq, valor);  // Remove à esquerda
    } else if (valor > raiz->valor) {
        raiz->dir = removerNodo(raiz->dir, valor);  // Remove à direita
    } else {
        // Nó com um ou zero filhos
        if (!raiz->esq) {
            NodoAVL *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (!raiz->dir) {
            NodoAVL *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos: encontra o sucessor
        NodoAVL *temp = obterAltura(raiz->esq) > obterAltura(raiz->dir) ? encontrarMaximo(raiz->esq) : encontrarMinimo(raiz->dir);
        raiz->valor = temp->valor;

        if (temp == encontrarMaximo(raiz->esq)) {
            raiz->esq = removerNodo(raiz->esq, temp->valor);
        } else {
            raiz->dir = removerNodo(raiz->dir, temp->valor);
        }
    }

    // Ajusta balanceamento após remoção
    return ajustarBalanceamento(raiz, valor);
}

// Percurso in-order para exibir a árvore
void exibirEmOrdem(NodoAVL *raiz) {
    if (raiz) {
        exibirEmOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        exibirEmOrdem(raiz->dir);
    }
}

// Percurso pre-order para exibir a árvore
void exibirPreOrdem(NodoAVL *raiz) {
    if (raiz) {
        printf("%d ", raiz->valor);
        exibirEmOrdem(raiz->esq);
        exibirEmOrdem(raiz->dir);
    }
}

// Percurso post-order para exibir a árvore
void exibirPosOrdem(NodoAVL *raiz) {
    if (raiz) {
        exibirEmOrdem(raiz->esq);
        exibirEmOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

// Função para exibir nós com indentação
void exibirNodo(int valor, int espacos) {
    for (int i = 0; i < espacos; i++) {
        printf("   ");
    }
    printf("%d\n", valor);
}

// Exibe a árvore em formato estruturado
void exibirArvoreEstruturada(NodoAVL *nodo, int espacos) {
    if (nodo) {
        exibirArvoreEstruturada(nodo->dir, espacos + 1);
        exibirNodo(nodo->valor, espacos);
        exibirArvoreEstruturada(nodo->esq, espacos + 1);
    }
}

// Função principal para testar a árvore AVL
int main() {
    NodoAVL *raiz = NULL;
    raiz = inserirNodo(raiz, 30);
    raiz = inserirNodo(raiz, 24);
    raiz = inserirNodo(raiz, 20);
    raiz = inserirNodo(raiz, 35);
    raiz = inserirNodo(raiz, 27);
    raiz = inserirNodo(raiz, 33);
    raiz = inserirNodo(raiz, 38);
    raiz = inserirNodo(raiz, 25);
    raiz = inserirNodo(raiz, 22);
    raiz = inserirNodo(raiz, 34);
    raiz = inserirNodo(raiz, 40);
    raiz = inserirNodo(raiz, 29);

    exibirArvoreEstruturada(raiz, 3);

    printf("\nInserindo 31...\n");
    raiz = inserirNodo(raiz, 31);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nInserindo 15...\n");
    raiz = inserirNodo(raiz, 15);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nInserindo 23...\n");
    raiz = inserirNodo(raiz, 23);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nRemovendo 24...\n");
    raiz = removerNodo(raiz, 24);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nRemovendo 35...\n");
    raiz = removerNodo(raiz, 35);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nInserindo 24...\n");
    raiz = inserirNodo(raiz, 24);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nRemovendo 27...\n");
    raiz = removerNodo(raiz, 27);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nInserindo 32...\n");
    raiz = inserirNodo(raiz, 32);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nRemovendo 30...\n");
    raiz = removerNodo(raiz, 30);
    exibirArvoreEstruturada(raiz, 3);

    printf("\nInserindo 21...\n");
    raiz = inserirNodo(raiz, 21);
    exibirArvoreEstruturada(raiz, 3);

    return 0;
}

