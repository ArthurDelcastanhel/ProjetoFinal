#ifndef PROJETOFINAL_CANIL_H
#define PROJETOFINAL_CANIL_H

typedef struct NoAVL {
    int id;
    char nome[50];
    char raca[40];
    int idade;
    int altura;
    struct NoAVL *esq;
    struct NoAVL *dir;
} NoAVL;

typedef struct NoABP {
    int codigo;
    char item[50];
    int quantidade;
    struct NoABP *esq;
    struct NoABP *dir;
} NoABP;

typedef struct NoFila {
    char nomeCao[50];
    char motivo[50];
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaEspera;

typedef struct NoPilha {
    char descricao[100];
    struct NoPilha *prox;
} NoPilha;

int alturaAVL(NoAVL *n);
int maior(int a, int b);
int fatorBalanceamento(NoAVL *n);
NoAVL* rotacaoDireita(NoAVL *y);
NoAVL* rotacaoEsquerda(NoAVL *x);
NoAVL* inserirAVL(NoAVL* no, int id, char* nome, char* raca, int idade);
void emOrdemAVL(NoAVL* raiz);


NoABP* inserirABP(NoABP* raiz, int codigo, char* item, int quantidade);
void emOrdemABP(NoABP* raiz);

void inicializarFila(FilaEspera *f);
void enfileirar(FilaEspera *f, char* nomeCao, char* motivo);
void desenfileirar(FilaEspera *f);
void mostrarFila(FilaEspera *f);

void empilhar(NoPilha **topo, char* descricao);
void desempilhar(NoPilha **topo);
void mostrarPilha(NoPilha *topo);

void salvarDados(NoABP *estoque);

#endif //PROJETOFINAL_CANIL_H