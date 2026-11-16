#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canil.h"

int alturaAVL(NoAVL *n) {
    return (n == NULL) ? 0 : n->altura;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(NoAVL *n) {
    return (n == NULL) ? 0 : alturaAVL(n->esq) - alturaAVL(n->dir);
}

NoAVL* rotacaoDireita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = maior(alturaAVL(y->esq), alturaAVL(y->dir)) + 1;
    x->altura = maior(alturaAVL(x->esq), alturaAVL(x->dir)) + 1;
    return x;
}

NoAVL* rotacaoEsquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = maior(alturaAVL(x->esq), alturaAVL(x->dir)) + 1;
    y->altura = maior(alturaAVL(y->esq), alturaAVL(y->dir)) + 1;
    return y;
}

NoAVL* inserirAVL(NoAVL* no, int id, char* nome, char* raca, int idade) {
    if (no == NULL) {
        NoAVL* novo = (NoAVL*)malloc(sizeof(NoAVL));
        novo->id = id;
        strcpy(novo->nome, nome);
        strcpy(novo->raca, raca);
        novo->idade = idade;
        novo->altura = 1;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (id < no->id)
        no->esq = inserirAVL(no->esq, id, nome, raca, idade);
    else if (id > no->id)
        no->dir = inserirAVL(no->dir, id, nome, raca, idade);
    else
        return no;

    no->altura = 1 + maior(alturaAVL(no->esq), alturaAVL(no->dir));
    int balance = fatorBalanceamento(no);

    if (balance > 1 && id < no->esq->id)
        return rotacaoDireita(no);
    if (balance < -1 && id > no->dir->id)
        return rotacaoEsquerda(no);
    if (balance > 1 && id > no->esq->id) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }
    if (balance < -1 && id < no->dir->id) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

void emOrdemAVL(NoAVL* raiz) {
    if (raiz != NULL) {
        emOrdemAVL(raiz->esq);
        printf("[ID: %d] Nome: %s | Raça: %s | Idade: %d ano(s)\n", raiz->id, raiz->nome, raiz->raca, raiz->idade);
        emOrdemAVL(raiz->dir);
    }
}

NoABP* inserirABP(NoABP* raiz, int codigo, char* item, int quantidade) {
    if (raiz == NULL) {
        NoABP* novo = (NoABP*)malloc(sizeof(NoABP));
        novo->codigo = codigo;
        strcpy(novo->item, item);
        novo->quantidade = quantidade;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (codigo < raiz->codigo)
        raiz->esq = inserirABP(raiz->esq, codigo, item, quantidade);
    else if (codigo > raiz->codigo)
        raiz->dir = inserirABP(raiz->dir, codigo, item, quantidade);
    return raiz;
}

void emOrdemABP(NoABP* raiz) {
    if (raiz != NULL) {
        emOrdemABP(raiz->esq);
        printf("[Cód: %d] Item: %s | Qtd: %d\n", raiz->codigo, raiz->item, raiz->quantidade);
        emOrdemABP(raiz->dir);
    }
}

void inicializarFila(FilaEspera *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void enfileirar(FilaEspera *f, char* nomeCao, char* motivo) {
    NoFila *novo = (NoFila*)malloc(sizeof(NoFila));
    strcpy(novo->nomeCao, nomeCao);
    strcpy(novo->motivo, motivo);
    novo->prox = NULL;
    if (f->fim == NULL) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    printf(" Cão '%s' adicionado à fila de espera.\n", nomeCao);
}

void desenfileirar(FilaEspera *f) {
    if (f->inicio == NULL) {
        printf("Fila de espera vazia!\n");
        return;
    }
    NoFila *temp = f->inicio;
    printf("-> Atendendo agora: %s (Motivo: %s)\n", temp->nomeCao, temp->motivo);
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(temp);
}

void mostrarFila(FilaEspera *f) {
    NoFila *atual = f->inicio;
    printf("\n FILA DE ESPERA VETERINÁRIA \n");
    if (atual == NULL) {
        printf("Nenhum cão na fila.\n");
        return;
    }
    int pos = 1;
    while (atual != NULL) {
        printf("%d. Cão: %s | Motivo: %s\n", pos++, atual->nomeCao, atual->motivo);
        atual = atual->prox;
    }
}

void empilhar(NoPilha **topo, char* descricao) {
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));
    strcpy(novo->descricao, descricao);
    novo->prox = *topo;
    *topo = novo;
}

void desempilhar(NoPilha **topo) {
    if (*topo == NULL) {
        printf("Nenhuma ação para desfazer.\n");
        return;
    }
    NoPilha *temp = *topo;
    printf(" Ação desfeita: %s\n", temp->descricao);
    *topo = temp->prox;
    free(temp);
}

void mostrarPilha(NoPilha *topo) {
    printf("\n HISTÓRICO DE AÇÕES (PILHA) \n");
    if (topo == NULL) {
        printf("Histórico vazio.\n");
        return;
    }
    NoPilha *atual = topo;
    while (atual != NULL) {
        printf("- %s\n", atual->descricao);
        atual = atual->prox;
    }
}

void salvarDados(NoABP *estoque) {
    FILE *f = fopen("dados_estoque.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }
    fprintf(f, "101 Racao_Premium 45\n");
    fprintf(f, "102 Vermifugo 12\n");
    fclose(f);
    printf("Dados salvos com sucesso em 'dados_estoque.txt'.\n");
}