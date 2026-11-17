#ifndef PROJETOFINAL_CANIL_H
#define PROJETOFINAL_CANIL_H

// usado Árvore AVL para estruturar o cadastro dos cães por ID
typedef struct NoAVL {
    int id;
    char nome[50];
    char raca[40];
    int idade;
    int altura;
    struct NoAVL *esq;
    struct NoAVL *dir;
} NoAVL;

// estrutura da Árvore Binária de Busca para para estruturar o estoque de ração e medicamentos
typedef struct NoABB {
    int codigo;
    char item[50];
    int quantidade;
    struct NoABB *esq;
    struct NoABB *dir;
} NoABB;

// estrutura da fila dinâmica para estruturar uma fila de espera para atendimentos e cadastros
typedef struct NoFila {
    char nomeCao[50];
    char motivo[50];
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaEspera;

// estrutura da pilha para implementar a ação de histórico de ações para desfazer (undo)
typedef struct NoPilha {
    char descricao[100];
    struct NoPilha *prox;
} NoPilha;

// declaração dos protótipos das funções AVL
int alturaAVL(NoAVL *n);
int maior(int a, int b);
int fatorBalanceamento(NoAVL *n);
NoAVL* rotacaoDireita(NoAVL *y);
NoAVL* rotacaoEsquerda(NoAVL *x);
NoAVL* inserirAVL(NoAVL* no, int id, char* nome, char* raca, int idade);
void emOrdemAVL(NoAVL* raiz);

// protótipos das funções de árvore de busca binária
NoABB* inserirABP(NoABB* raiz, int codigo, char* item, int quantidade);
void emOrdemABP(NoABB* raiz);

// declaração das funções de fila
void inicializarFila(FilaEspera *f);
void enfileirar(FilaEspera *f, char* nomeCao, char* motivo);
void desenfileirar(FilaEspera *f);
void mostrarFila(FilaEspera *f);

// declaração das funções de pilha
void empilhar(NoPilha **topo, char* descricao);
void desempilhar(NoPilha **topo);
void mostrarPilha(NoPilha *topo);

// persistência da aplicação
void salvarDados(NoABB *estoque);

#endif //PROJETOFINAL_CANIL_H