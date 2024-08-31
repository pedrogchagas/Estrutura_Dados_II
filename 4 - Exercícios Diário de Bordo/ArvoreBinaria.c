// CÓDIGO FEITO POR PEDRO HENRIQUE GOMES CHAGAS
// CC6N - ESTRUTURA DE DADOS II 
// ATIVIDADE 1 E 2 FEITAS NO MESMO ARQUIVO
// JUNTANDO A ÁRVORE BINÁRIA FEITA COM AS FUNÇÕES DE "preOrdem", "emOrdem" e "posOrdem" 

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore binária
typedef struct No {
  int valor; // Valor armazenado no nó
  struct No * esq; // Ponteiro para o nó filho à esquerda
  struct No * dir; // Ponteiro para o nó filho à direita
}
NoArvore;

// Estrutura para representar a pilha usada nas travessias iterativas
typedef struct Pilha {
  NoArvore * no; // Ponteiro para um nó da árvore
  struct Pilha * prox; // Ponteiro para o próximo elemento da pilha
}
Pilha;

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
    if (raiz -> esq == NULL) {
      NoArvore * temp = raiz -> dir;
      free(raiz);
      return temp;
    } else if (raiz -> dir == NULL) {
      NoArvore * temp = raiz -> esq;
      free(raiz);
      return temp;
    }
    NoArvore * temp = acharMenor(raiz -> dir);
    raiz -> valor = temp -> valor;
    raiz -> dir = removerNo(raiz -> dir, temp -> valor);
  }
  return raiz;
}

// Função para buscar um nó na árvore
NoArvore * buscarNo(NoArvore * raiz, int valor) {
  while (raiz != NULL) {
    if (valor == raiz -> valor) {
      return raiz;
    } else if (valor < raiz -> valor) {
      raiz = raiz -> esq;
    } else {
      raiz = raiz -> dir;
    }
  }
  return NULL; // Retorna NULL se o valor não for encontrado
}

// Função para empilhar um nó na pilha
void empilhar(Pilha ** topo, NoArvore * no) {
  Pilha * novo = (Pilha * ) malloc(sizeof(Pilha));
  novo -> no = no;
  novo -> prox = * topo;
  * topo = novo;
}

// Função para desempilhar um nó da pilha
NoArvore * desempilhar(Pilha ** topo) {
  if ( * topo == NULL) {
    return NULL;
  }
  Pilha * temp = * topo;
  * topo = ( * topo) -> prox;
  NoArvore * noDesempilhado = temp -> no;
  free(temp);
  return noDesempilhado;
}

// Função para percorrer a árvore em ordem (in-order) de forma iterativa
void emOrdemIterativa(NoArvore * raiz) {
  Pilha * pilha = NULL;
  NoArvore * atual = raiz;

  while (atual != NULL || pilha != NULL) {
    while (atual != NULL) {
      empilhar( & pilha, atual);
      atual = atual -> esq;
    }
    atual = desempilhar( & pilha);
    printf("%d ", atual -> valor);
    atual = atual -> dir;
  }
}

// Função para percorrer a árvore em pré-ordem (pre-order) de forma iterativa
void preOrdemIterativa(NoArvore * raiz) {
  if (raiz == NULL) {
    return;
  }

  Pilha * pilha = NULL;
  empilhar( & pilha, raiz);

  while (pilha != NULL) {
    NoArvore * atual = desempilhar( & pilha);
    printf("%d ", atual -> valor);

    if (atual -> dir != NULL) {
      empilhar( & pilha, atual -> dir);
    }
    if (atual -> esq != NULL) {
      empilhar( & pilha, atual -> esq);
    }
  }
}

// Função para percorrer a árvore em pós-ordem (post-order) de forma iterativa
void posOrdemIterativa(NoArvore * raiz) {
  if (raiz == NULL) {
    return;
  }

  Pilha * pilha1 = NULL;
  Pilha * pilha2 = NULL;
  empilhar( & pilha1, raiz);

  while (pilha1 != NULL) {
    NoArvore * atual = desempilhar( & pilha1);
    empilhar( & pilha2, atual);

    if (atual -> esq != NULL) {
      empilhar( & pilha1, atual -> esq);
    }
    if (atual -> dir != NULL) {
      empilhar( & pilha1, atual -> dir);
    }
  }

  while (pilha2 != NULL) {
    NoArvore * atual = desempilhar( & pilha2);
    printf("%d ", atual -> valor);
  }
}

// Função para exibir a árvore de forma hierárquica
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

  // Buscando um valor na árvore
  NoArvore * resultadoBusca = buscarNo(raiz, 25);
  if (resultadoBusca != NULL) {
    printf("\nValor 25 encontrado na árvore.\n");
  } else {
    printf("\nValor 25 não encontrado na árvore.\n");
  }

  // Percorrendo a árvore
  printf("\nPercurso em ordem (iterativo):\n");
  emOrdemIterativa(raiz);
  printf("\n\nPercurso em pré-ordem (iterativo):\n");
  preOrdemIterativa(raiz);
  printf("\n\nPercurso em pós-ordem (iterativo):\n");
  posOrdemIterativa(raiz);
  printf("\n");

  return 0;
}