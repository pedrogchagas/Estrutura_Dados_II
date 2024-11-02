// CÓDIGO FEITO POR PEDRO HENRIQUE GOMES CHAGAS
// CC6N - ESTRUTURA DE DADOS II 
// Árvore Treap

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do nó da Treap com chave, prioridade, filho esquerdo e direito
struct NoTreap {
    int chave;
    int prioridade;
    struct NoTreap *esquerda, *direita;
};

// Função para criar um novo nó na Treap
struct NoTreap *criarNo(int chave) {
    struct NoTreap *novoNo = (struct NoTreap *)malloc(sizeof(struct NoTreap));
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        exit(-1);
    }
    novoNo->chave = chave;
    novoNo->prioridade = rand() % 100;  // Prioridade aleatória
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

// Função de rotação à direita
struct NoTreap *rotacaoDireita(struct NoTreap *no) {
    struct NoTreap *novaRaiz = no->esquerda;
    no->esquerda = novaRaiz->direita;
    novaRaiz->direita = no;
    return novaRaiz;
}

// Função de rotação à esquerda
struct NoTreap *rotacaoEsquerda(struct NoTreap *no) {
    struct NoTreap *novaRaiz = no->direita;
    no->direita = novaRaiz->esquerda;
    novaRaiz->esquerda = no;
    return novaRaiz;
}

// Função para inserir um nó na Treap
struct NoTreap *inserir(struct NoTreap *raiz, int chave) {
    if (raiz == NULL)
        return criarNo(chave);

    if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);

        // Verifica a prioridade para manter a propriedade do heap
        if (raiz->esquerda->prioridade > raiz->prioridade)
            raiz = rotacaoDireita(raiz);
    } else if (chave > raiz->chave) {
        raiz->direita = inserir(raiz->direita, chave);

        if (raiz->direita->prioridade > raiz->prioridade)
            raiz = rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para excluir um nó da Treap
struct NoTreap *excluir(struct NoTreap *raiz, int chave) {
    if (raiz == NULL)
        return raiz;

    if (chave < raiz->chave) {
        raiz->esquerda = excluir(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = excluir(raiz->direita, chave);
    } else {
        if (raiz->esquerda == NULL) {
            struct NoTreap *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            struct NoTreap *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Prioridade do filho direito é maior, rotação à esquerda
        if (raiz->esquerda->prioridade < raiz->direita->prioridade) {
            raiz = rotacaoEsquerda(raiz);
            raiz->esquerda = excluir(raiz->esquerda, chave);
        } else {
            raiz = rotacaoDireita(raiz);
            raiz->direita = excluir(raiz->direita, chave);
        }
    }

    return raiz;
}

// Função para buscar uma chave na Treap
struct NoTreap *buscar(struct NoTreap *raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return buscar(raiz->esquerda, chave);
    else
        return buscar(raiz->direita, chave);
}

// Função para imprimir a Treap em pré-ordem
void imprimirPreOrdem(struct NoTreap *raiz) {
    if (raiz != NULL) {
        printf("Chave: %d, Prioridade: %d\n", raiz->chave, raiz->prioridade);
        imprimirPreOrdem(raiz->esquerda);
        imprimirPreOrdem(raiz->direita);
    }
}

// Função principal para testar a Treap
int main() {
    srand(time(0)); // Inicializa a semente para a geração de prioridade aleatória

    struct NoTreap *raiz = NULL;
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Treap em pré-ordem:\n");
    imprimirPreOrdem(raiz);

    int chaveParaBuscar = 60;
    struct NoTreap *resultadoBusca = buscar(raiz, chaveParaBuscar);
    if (resultadoBusca != NULL)
        printf("\nChave %d encontrada com prioridade %d.\n", resultadoBusca->chave, resultadoBusca->prioridade);
    else
        printf("\nChave %d não encontrada na Treap.\n", chaveParaBuscar);

    printf("\nExcluindo chave 50:\n");
    raiz = excluir(raiz, 50);
    imprimirPreOrdem(raiz);

    return 0;
}
