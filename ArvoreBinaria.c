// CÓDIGO FEITO POR PEDRO HENRIQUE GOMES CHAGAS
// CC6N - ESTRUTURA DE DADOS II 

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore binária
typedef struct No {
  int valor; // Valor armazenado no nó
  struct No * esq; // Ponteiro para o nó filho à esquerda
  struct No * dir; // Ponteiro para o nó filho à direita
}
NoArvore;

// Função para criar um novo nó na árvore
NoArvore * criarNo(int valor) {
  NoArvore * novo = (NoArvore * ) malloc(sizeof(NoArvore));
  if (novo == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(1);
  }
  novo -> valor = valor;
  novo -> esq = NULL;
  novo -> dir = NULL;
  return novo;
}

// Função para inserir um valor na árvore
NoArvore * inserirNo(NoArvore * raiz, int valor) {
  if (raiz == NULL) {
    return criarNo(valor);
  }
  if (valor < raiz -> valor) {
    raiz -> esq = inserirNo(raiz -> esq, valor);
  } else {
    raiz -> dir = inserirNo(raiz -> dir, valor);
  }
  return raiz;
}

// Função para encontrar o menor valor na subárvore
NoArvore * acharMenor(NoArvore * n) {
  NoArvore * atual = n;
  while (atual && atual -> esq != NULL) {
    atual = atual -> esq;
  }
  return atual;
}

// Função para remover um valor da árvore
NoArvore * removerNo(NoArvore * raiz, int valor) {
  if (raiz == NULL) {
    return NULL;
  }
  if (valor < raiz -> valor) {
    raiz -> esq = removerNo(raiz -> esq, valor);
  } else if (valor > raiz -> valor) {
    raiz -> dir = removerNo(raiz -> dir, valor);
  } else {
    // Se o nó tem um ou nenhum filho
    if (raiz -> esq == NULL) {
      NoArvore * temp = raiz -> dir;
      free(raiz);
      return temp;
    } else if (raiz -> dir == NULL) {
      NoArvore * temp = raiz -> esq;
      free(raiz);
      return temp;
    }

    // Nó com dois filhos: obtenha o sucessor (menor valor na subárvore direita)
    NoArvore * temp = acharMenor(raiz -> dir);
    raiz -> valor = temp -> valor;
    raiz -> dir = removerNo(raiz -> dir, temp -> valor);
  }
  return raiz;
}

// Função para percorrer a árvore em ordem (in-order traversal)
void emOrdem(NoArvore * raiz) {
  if (raiz != NULL) {
    emOrdem(raiz -> esq);
    printf("%d ", raiz -> valor);
    emOrdem(raiz -> dir);
  }
}

// Função para percorrer a árvore em pré-ordem (pre-order traversal)
void preOrdem(NoArvore * raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz -> valor);
    preOrdem(raiz -> esq);
    preOrdem(raiz -> dir);
  }
}

// Função para percorrer a árvore em pós-ordem (post-order traversal)
void posOrdem(NoArvore * raiz) {
  if (raiz != NULL) {
    posOrdem(raiz -> esq);
    posOrdem(raiz -> dir);
    printf("%d ", raiz -> valor);
  }
}

// Função para exibir a árvore (de forma simples, só para ter uma ideia)
void mostrarArvore(NoArvore * raiz, int espaco) {
  if (raiz == NULL) {
    return;
  }
  espaco += 5;
  mostrarArvore(raiz -> dir, espaco);
  for (int i = 5; i < espaco; i++) {
    printf(" ");
  }
  printf("%d\n", raiz -> valor);
  mostrarArvore(raiz -> esq, espaco);
}

int main() {
  NoArvore * raiz = NULL;

  // Inserindo alguns valores na árvore
  raiz = inserirNo(raiz, 20);
  raiz = inserirNo(raiz, 10);
  raiz = inserirNo(raiz, 30);
  raiz = inserirNo(raiz, 5);
  raiz = inserirNo(raiz, 15);
  raiz = inserirNo(raiz, 25);
  raiz = inserirNo(raiz, 35);

  // Exibindo a árvore inicial
  printf("Árvore binária:\n");
  mostrarArvore(raiz, 0);

  // Removendo um valor
  raiz = removerNo(raiz, 10);
  printf("\nÁrvore após remover 10:\n");
  mostrarArvore(raiz, 0);

  // Percorrendo a árvore
  printf("\nPercurso em ordem:\n");
  emOrdem(raiz);
  printf("\n\nPercurso em pré-ordem:\n");
  preOrdem(raiz);
  printf("\n\nPercurso em pós-ordem:\n");
  posOrdem(raiz);
  printf("\n");

  return 0;
}
