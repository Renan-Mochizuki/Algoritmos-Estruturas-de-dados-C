#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define ESQUERDO 1
#define DIREITO 2
#define FormatoValor "%d"
#define FormatoLado "%d"

typedef int Boolean;
typedef int TipoValor;
typedef int Lado;

// Declarando struct de um nó da árvore
typedef struct arvoreNo {
  TipoValor valor;
  struct arvoreNo* esq;
  struct arvoreNo* dir;
} itemNo;

// Declarando struct da árvore
typedef struct arvore {
  itemNo* raiz;
} Arvore;

// Função recursiva que imprime os elementos da árvore
void ImprimirValoresRecursiva(Arvore* arvore, itemNo* no) {
  // Faça o percurso in-ordem
  if (no) {
    ImprimirValoresRecursiva(arvore, no->esq);
    // Destacando a raiz na impressão
    if (no == arvore->raiz)
      printf("*%d* ", no->valor);
    else
      printf("%d ", no->valor);
    ImprimirValoresRecursiva(arvore, no->dir);
  }
}

// Função que imprime os elementos da árvore
void ImprimirValores(Arvore* arvore) {
  // Se a árvore estiver vazia
  if (!arvore->raiz) {
    printf("A arvore esta vazia\n");
    return;
  }

  printf("\nOs elementos da arvore seguindo o in-ordem: (*raiz*)\n");
  ImprimirValoresRecursiva(arvore, arvore->raiz);
  printf("\n\n");
}

// Função que retorna o ponteiro para a árvore
Arvore* CriarArvore() {
  Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  return arvore;
}

// Função recursiva que retorna o nó que possui o valor, ou então, retorna NULL caso não for encontrado
itemNo* BuscarValorRecursiva(itemNo* no, TipoValor valor) {
  // Se o nó não existir (for NULL) retorne NULL
  if (!no) return NULL;

  // Se o valor for encontrado, retorne o nó
  if (no->valor == valor) return no;

  // Se o valor ainda não for encontrado, busque no nó à esquerda
  itemNo* auxiliar = BuscarValorRecursiva(no->esq, valor);

  // Se o valor for encontrado retorne o nó
  if (auxiliar) return auxiliar;

  // Se o valor ainda não for encontrado, por fim, busque no nó à direita
  return BuscarValorRecursiva(no->dir, valor);
}

// Função que retorna o nó que possui o valor, ou então, retorna NULL caso não for encontrado
itemNo* BuscarValor(Arvore* arvore, TipoValor valor) {
  return BuscarValorRecursiva(arvore->raiz, valor);
}

// Função que insere um valor ainda não existente na árvore
Boolean InserirValor(Arvore* arvore, itemNo* noPai, TipoValor valor, Lado lado) {
  // Caso o valor já exista na árvore, retorne FALSE
  if (BuscarValor(arvore, valor)) {
    return FALSE;
  }

  // Declarando o novo nó a ser inserido na árvore
  itemNo* novoNo = malloc(sizeof(itemNo));
  novoNo->valor = valor;
  novoNo->esq = NULL;
  novoNo->dir = NULL;

  // Se a árvore estiver vazia, o novo nó será a raiz
  if (!arvore->raiz || !noPai) {
    novoNo->esq = arvore->raiz;
    arvore->raiz = novoNo;
    return TRUE;
  }

  if (lado == ESQUERDO) {
    // Atribua o nó conectado à esquerda do pai para o novo nó
    // Conecte o novo nó ao pai
    novoNo->esq = noPai->esq;
    noPai->esq = novoNo;
  } else {
    // Atribua o nó conectado à direita do pai para o novo nó
    // Conecte o novo nó ao pai
    novoNo->dir = noPai->dir;
    noPai->dir = novoNo;
  }

  return TRUE;
}

// Função que retorna o nó pai de um nó
itemNo* RetornarNoPai(itemNo* raiz, itemNo* noFilho) {
  // Se não tiver raiz ou se o noFilho for a própria raiz, retorne NULL
  if (!raiz || raiz == noFilho) return NULL;

  // Se o filho da esquerda ou direita existir e for o nó passado, então retorne essa raiz
  if (raiz->esq && raiz->esq == noFilho) return raiz;
  if (raiz->dir && raiz->dir == noFilho) return raiz;

  // Se ainda não for encontrado, busque no nó da esquerda
  itemNo* auxiliar = RetornarNoPai(raiz->esq, noFilho);
  if (auxiliar) return auxiliar;

  // Por fim, busque no nó da direita
  return RetornarNoPai(raiz->dir, noFilho);
}

// Função recursiva que remove um nó da árvore
Boolean RemoverNoRecursiva(itemNo* noPai, itemNo* noRemover) {
  // Se o nó a ser removido for NULL (chegou no fim) retorne FALSE
  if (!noRemover) return FALSE;

  // Se o no a ser removido não tiver nenhum filho
  if (!noRemover->esq && !noRemover->dir) {
    // Se o nó a ser removido for o filho da esquerda ou direita do pai, limpa o ponteiro
    if (noPai->esq && noPai->esq == noRemover) noPai->esq = NULL;
    if (noPai->dir && noPai->dir == noRemover) noPai->dir = NULL;
  } else if (noRemover->esq || noRemover->dir) {  // Se tiver um filho
    // Pega um filho do noRemover, atribue ao no a ser removido e repete essa promoção até o último filho ser excluído
    itemNo* noRemoverFilho = noRemover->esq ? noRemover->esq : noRemover->dir;
    noRemover->valor = noRemoverFilho->valor;  // Aqui estamos apenas promovendo o valor e não o próprio nó, TODO: promoção do nó em vez do valor
    return RemoverNoRecursiva(noRemover, noRemoverFilho);
  }

  free(noRemover);
  return TRUE;
}

// Função que remove um nó da árvore
Boolean RemoverNo(Arvore* arvore, itemNo* noRemover) {
  // Se o nó não tiver nenhum filho e for a raiz
  if (!noRemover->esq && !noRemover->dir && noRemover == arvore->raiz) {
    arvore->raiz = NULL;
    free(noRemover);
    return TRUE;
  }

  itemNo* noPai = RetornarNoPai(arvore->raiz, noRemover);
  return RemoverNoRecursiva(noPai, noRemover);
}

// Função que remove um valor da árvore
Boolean RemoverValor(Arvore* arvore, TipoValor valor) {
  itemNo* noRemover = BuscarValor(arvore, valor);
  return RemoverNo(arvore, noRemover);
}

// Função recursiva que limpa a árvore
void LimparArvoreRecursiva(itemNo* no) {
  // Limpe a árvore pelo percurso pos-ordem
  if (no) {
    LimparArvoreRecursiva(no->esq);
    LimparArvoreRecursiva(no->dir);
    free(no);
  }
}

// Função que limpa a árvore
void LimparArvore(Arvore* arvore) {
  LimparArvoreRecursiva(arvore->raiz);
}

// Função recursiva que conta quantos valores a árvore tem
int ContarValoresRecursiva(itemNo* no) {
  if (!no) return 0;

  return 1 + ContarValoresRecursiva(no->esq) + ContarValoresRecursiva(no->dir);
}

// Função que conta quantos valores a árvore tem
int ContarValores(Arvore* arvore) {
  return ContarValoresRecursiva(arvore->raiz);
}

// Função recursiva para encontrar o nó com espaço livre mais próximo da raiz
void EncontrarNoLivreRecursiva(itemNo* no, int alturaAtual, int* menorAltura, itemNo** noLivre) {
  // Se o no passado não existir, finalize a função
  if (!no) return;

  // Se o nó atual tem espaço vazio
  if (!no->esq || !no->dir) {
    // Se a altura atual for menor que a menor altura encontrada até então
    if (alturaAtual < *menorAltura) {
      // Altere a nova altura menor e o nó livre
      *menorAltura = alturaAtual;
      *noLivre = no;
    }
  }

  // Verifica o lado esquerdo e direito aumentando a alturaAtual
  EncontrarNoLivreRecursiva(no->esq, alturaAtual + 1, menorAltura, noLivre);
  EncontrarNoLivreRecursiva(no->dir, alturaAtual + 1, menorAltura, noLivre);
}

// Função que retorna um nó livre mais próximo da raiz (mais alto)
itemNo* EncontrarNoLivre(Arvore* arvore) {
  // Se a árvore estiver vazia
  if (arvore->raiz == NULL) return NULL;

  itemNo* noLivre = NULL;
  int menorAltura = 999999;  // Ou __INT_MAX__

  EncontrarNoLivreRecursiva(arvore->raiz, 0, &menorAltura, &noLivre);

  return noLivre;
}

// Função que imprime os valores desde a raiz até o nó
void ImprimirRotaDoNoValores(Arvore* arvore, itemNo* no) {
  if (!no) return;

  itemNo* noPai = RetornarNoPai(arvore->raiz, no);

  ImprimirRotaDoNoValores(arvore, noPai);

  if (no == arvore->raiz) {
    printf("%d", no->valor);
  } else {
    printf("->%d", no->valor);
  }
}

// Função que imprime os lados seguidos desde a raiz até o nó
void ImprimirRotaDoNoLados(Arvore* arvore, itemNo* noPai, itemNo* no) {
  itemNo* noAvo = RetornarNoPai(arvore->raiz, noPai);

  if (!noPai) return;

  ImprimirRotaDoNoLados(arvore, noAvo, noPai);

  if (noPai->esq == no) {
    printf("->Esq");
  } else {
    printf("->Dir");
  }
}

// Função que imprime tanto os valores quanto os lados seguidos desde a raiz até o nó
void ImprimirRotaDoNo(Arvore* arvore, itemNo* no) {
  ImprimirRotaDoNoValores(arvore, no);
  printf("\n");
  itemNo* noPai = RetornarNoPai(arvore->raiz, no);
  printf("Raiz");
  ImprimirRotaDoNoLados(arvore, noPai, no);
  printf("\n");
}

int main(void) {
  Arvore* arvore = CriarArvore();
  TipoValor valorDigitado, valorNoPai;
  Lado lado = 0;
  int escolha = 1;

  while (escolha > 0 && escolha < 7) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores no arvore automaticamente\n");
    printf("2 - Inserir valores no arvore escolhendo o no pai\n");
    printf("3 - Remover valores\n");
    printf("4 - Buscar valores\n");
    printf("5 - Ver quantos itens a arvore possui\n");
    printf("6 - Imprimir arvore\n");
    printf("7 - Sair\n");

    scanf("%d", &escolha);
    printf("\n");

    valorDigitado = 0;
    valorNoPai = 0;

    switch (escolha) {
      case 1:
        printf("Digite um valor negativo para parar\n");
        while (valorDigitado >= 0) {
          itemNo* noLivre;

          printf("Digite um valor para ser inserido\n");
          scanf(FormatoValor, &valorDigitado);

          if (valorDigitado < 0) break;

          noLivre = EncontrarNoLivre(arvore);
          // Verifica qual lado que está livre
          if (noLivre && !noLivre->esq)
            lado = ESQUERDO;
          else if (noLivre && !noLivre->dir)
            lado = DIREITO;

          Boolean funcaoSucedida = InserirValor(arvore, noLivre, valorDigitado, lado);

          if (funcaoSucedida)
            ImprimirValores(arvore);
          else
            printf("\nO valor ja existe na arvore\n");
        }
        break;

      case 2:
        printf("Digite um valor negativo para parar\n");
        while (valorDigitado >= 0) {
          printf("Digite um valor para ser inserido\n");
          scanf(FormatoValor, &valorDigitado);

          if (valorDigitado < 0) break;

          itemNo* noPai = NULL;

          if (arvore->raiz) {
            while (!noPai) {
              ImprimirValores(arvore);
              printf("Digite o valor do no que deseja inserir em baixo dele\n");
              scanf(FormatoValor, &valorNoPai);

              if (valorNoPai < 0) break;

              noPai = BuscarValor(arvore, valorNoPai);
            }
            if (valorNoPai < 0) break;

            printf("\nDigite qual lado deseja\n");
            printf("Esquerdo (1), Direito (2)\n");
            scanf(FormatoLado, &lado);
          } else {
            printf("A arvore esta vazia, o valor sera a raiz\n");
          }

          Boolean funcaoSucedida = InserirValor(arvore, noPai, valorDigitado, lado);

          if (funcaoSucedida)
            ImprimirValores(arvore);
          else
            printf("\nO valor ja existe na arvore\n");
        }
        break;

      case 3:
        printf("Digite um valor negativo para parar\n");
        while (valorDigitado >= 0) {
          if (!arvore->raiz) {
            printf("A arvore esta vazia\n");
            break;
          }

          ImprimirValores(arvore);
          printf("Digite um valor para ser removido\n");
          scanf(FormatoValor, &valorDigitado);

          if (valorDigitado < 0) break;

          Boolean funcaoSucedida = RemoverValor(arvore, valorDigitado);

          if (!funcaoSucedida) printf("\nO valor nao foi removido\n");
        }
        break;

      case 4:
        printf("Digite um valor para ser buscado\n");
        scanf(FormatoValor, &valorDigitado);

        itemNo* noEncontrado = BuscarValor(arvore, valorDigitado);

        if (noEncontrado) {
          ImprimirValores(arvore);
          printf("Percurso do valor desde a raiz:\n");
          ImprimirRotaDoNo(arvore, noEncontrado);
        } else {
          printf("\nO valor nao foi encontrado\n");
        }
        break;

      case 5:
        printf("A arvore possui %d itens\n", ContarValores(arvore));
        break;

      case 6:
        ImprimirValores(arvore);
        break;
    }
  }

  LimparArvore(arvore);

  return 0;
}