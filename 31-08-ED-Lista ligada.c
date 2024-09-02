#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int valor;
  struct node *proximo;
} itemNo;

typedef struct {
  int tamanho;
  itemNo *primeiro;
} listaLigada;

// Função para criar uma nova lista ligada
listaLigada *CriarLista() {
  listaLigada *lista = malloc(sizeof(listaLigada));
  lista->tamanho = 0;
  lista->primeiro = NULL;
  return lista;
}

// Função para inserir um novo item no início da lista
void InserirInicioLista(listaLigada *lista, int valor) {
  // Declarando o novo nó com o valor
  itemNo *itemNovo = malloc(sizeof(itemNo));
  itemNovo->valor = valor;
  // Aumentando o tamanho
  lista->tamanho++;

  // Se a lista estiver vazia, defina o próximo do itemNovo
  // como NULL e primeiro item como o novo nó
  if (lista->primeiro == NULL) {
    itemNovo->proximo = NULL;
    lista->primeiro = itemNovo;
    return;
  }

  // Definindo o proximo do itemNovo como o primeiro item da lista atualmente
  // e alterando o primeiro item da lista como o item novo
  itemNovo->proximo = lista->primeiro;
  lista->primeiro = itemNovo;
}

// Função para inserir um novo item no fim da lista
void InserirFimLista(listaLigada *lista, int valor) {
  // Declarando o novo nó
  itemNo *itemNovo = malloc(sizeof(itemNo));
  itemNovo->valor = valor;
  itemNovo->proximo = NULL;
  // Aumentando o tamanho
  lista->tamanho++;

  // Se a lista estiver vazia, defina o primeiro item como o novo nó
  if (lista->primeiro == NULL) {
    lista->primeiro = itemNovo;
    return;
  }

  itemNo *itemAtual = lista->primeiro;

  // Loop para percorrer até o próximo item ser NULL
  while (itemAtual->proximo != NULL) {
    itemAtual = itemAtual->proximo;
  }

  // Atribuindo o último item como o itemNovo
  itemAtual->proximo = itemNovo;
}

// Função para imprimir a lista
void ImprimirLista(listaLigada *lista) {
  // Se a lista estiver vazia
  if (lista->primeiro == NULL) {
    printf("\nLista vazia\n");
    return;
  }

  itemNo *itemAtual = lista->primeiro;

  printf("\nA lista esta assim: \n");
  // Loop pra percorrer até o NULL
  while (itemAtual != NULL) {
    printf("%d, ", itemAtual->valor);
    itemAtual = itemAtual->proximo;
  }
  printf("\n\n");
}

// Função para limpar a lista
void LimparLista(listaLigada *lista) {
  // Verifica se a lista não está vazia
  if (lista->primeiro != NULL) {
    itemNo *itemAtual = lista->primeiro;
    itemNo *itemProximo = itemAtual->proximo;
    // Loop que percorre a lista até o próximo item ser NULL
    while (itemProximo != NULL) {
      free(itemAtual);
      itemAtual = itemProximo;
      itemProximo = itemProximo->proximo;
    } // Caso o while acontecer, o último item ainda não foi liberado

    // Libera o último item, ou se a lista tiver só um item, libera
    free(itemAtual);
  }
}
int main(void) {
  listaLigada *lista = CriarLista();
  int numeroDigitado = 0;
  int escolha = 1;

  while (escolha < 11 && escolha > 0) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores no inicio da lista\n");
    printf("2 - Inserir valores no fim da lista\n");
    printf("3 - Inserir valores na lista com indice\n");
    printf("4 - Remover o valor do inicio da lista\n");
    printf("5 - Remover o valor do fim da lista\n");
    printf("6 - Remover um valor da lista pelo indice\n");
    printf("7 - Remover um certo valor\n");
    printf("8 - Buscar um valor\n");
    printf("9 - Ver quantos itens a lista possui\n");
    printf("10 - Imprimir lista\n");
    printf("-1 - Sair\n");

    scanf("%d", &escolha);
    printf("\n");

    switch (escolha) {
    case 1:
      printf("Digite um numero negativo para parar\n");
      do {
        printf("Digite um numero para ser inserido\n");
        scanf("%d", &numeroDigitado);

        if (numeroDigitado < 0) {
          break;
        }

        InserirInicioLista(lista, numeroDigitado);
        ImprimirLista(lista);
      } while (numeroDigitado > 0);
      break;
    case 2:
      printf("Digite um numero negativo para parar\n");
      do {
        printf("Digite um numero para ser inserido\n");
        scanf("%d", &numeroDigitado);

        if (numeroDigitado < 0) {
          break;
        }

        InserirFimLista(lista, numeroDigitado);
        ImprimirLista(lista);
      } while (numeroDigitado > 0);
      break;
    case 3:
      break;

    case 4:
      break;

    case 5:
      break;

    case 6:
      break;

    case 9:
      printf("A lista possui %d itens\n", lista->tamanho);
      break;
    }
  }

  LimparLista(lista);

  return 0;
}