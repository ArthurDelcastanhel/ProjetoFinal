#ifndef CANIL_H
#define CANIL_H

// estrutura da Árvore AVL para guardar o cadastro dos cães
typedef struct NoAVL {
    int id;                 // código único ou número do microchip do cão
    char nome[50];          // nome do cachorro
    char raca[40];          // raça do cachorro
    int idade;              // idade em anos
    int altura;             // altura do nó na árvore pra calcular o balanceamento
    struct NoAVL *esq;      // ponteiro para o filho da esquerda (IDs menores)
    struct NoAVL *dir;      // ponteiro para o filho da direita (IDs maiores)
} NoAVL;

// estrutura da Árvore de Busca Binária (ABB) para o estoque do canil
typedef struct NoABB {
    int codigo;             // código do produto no estoque
    char item[50];          // nome do item (ex: ração. vacina, etc)
    int quantidade;         // quantidade disponível
    struct NoABB *esq;      // ponteiro para o filho da esquerda (códigos menores)
    struct NoABB *dir;      // ponteiro para o filho da direita (códigos maiores)
} NoABB;

// nó da fila para organizar os cães esperando atendimento veterinário
typedef struct NoFila {
    char nomeCao[50];       // nome do cão que vai ser atendido
    char motivo[50];        // motivo da consulta (ex: castração, vacina, etc)
    struct NoFila *prox;    // ponteiro para o próximo cão da fila
} NoFila;

// estrutura que guarda o começo e o fim da fila
typedef struct {
    NoFila *inicio;         // ponteiro para o primeiro da fila (quem será atendido)
    NoFila *fim;            // ponteiro para o último da fila (onde entram novos cães)
} FilaEspera;

// nó da Pilha para guardar o histórico de ações e permitir desfazer (Undo)
typedef struct NoPilha {
    char descricao[100];    // texto explicando o que foi feito no sistema
    struct NoPilha *prox;   // ponteiro para o item de baixo na pilha
} NoPilha;

// protótipos das funções da Árvore AVL (Cães)
int alturaAVL(NoAVL *n);
int maior(int a, int b);
int fatorBalanceamento(NoAVL *n);
NoAVL* rotacaoDireita(NoAVL *y);
NoAVL* rotacaoEsquerda(NoAVL *x);
NoAVL* inserirAVL(NoAVL* no, int id, char* nome, char* raca, int idade);
NoAVL* buscarAVL(NoAVL* raiz, int id);
NoAVL* menorValorNo(NoAVL* no);
NoAVL* removerAVL(NoAVL* raiz, int id);
void emOrdemAVL(NoAVL* raiz);
int contarCaesAVL(NoAVL* raiz);

// protótipos das funções da Árvore de Busca Binária - ABB (usada para realizar e estrutura o estoque)
NoABB* inserirABB(NoABB* raiz, int codigo, char* item, int quantidade);
NoABB* buscarABB(NoABB* raiz, int codigo);
void emOrdemABB(NoABB* raiz);
int contarItensABB(NoABB* raiz);

// protótipos das funções da fila (usada para implementar uma fila de espera de atendimento)
void inicializarFila(FilaEspera *f);
void enfileirar(FilaEspera *f, char* nomeCao, char* motivo);
void desenfileirar(FilaEspera *f);
void mostrarFila(FilaEspera *f);
int contarFila(FilaEspera *f);

// protótipos das funções da pilha (histórico)
void empilhar(NoPilha **topo, char* descricao);
void desempilhar(NoPilha **topo);
void mostrarPilha(NoPilha *topo);

// protótipos das funções de salvar e carregar dados (persistência no código/aplicação)
void salvarAuxAVL(NoAVL *raiz, FILE *f);
void salvarAuxABB(NoABB *raiz, FILE *f);
void salvarDados(NoAVL *caes, NoABB *estoque);
void carregarDados(NoAVL **caes, NoABB **estoque);

#endif