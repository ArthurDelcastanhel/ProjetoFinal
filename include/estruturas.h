#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "modelos.h"

/* ============================================================================
 * 1. ÁRVORE BALANCEADA (AVL) - Cadastro de Animais (Chave: ID)
 * ============================================================================ */
typedef struct NoAVL {
    Animal dados;
    int altura;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
} NoAVL;

/* ============================================================================
 * 2. ÁRVORE BINÁRIA DE PESQUISA (ABP) - Cadastro de Adotantes (Chave: Nome)
 * ============================================================================ */
typedef struct NoABP {
    Adotante dados;
    struct NoABP *esquerda;
    struct NoABP *direita;
} NoABP;

/* ============================================================================
 * 3. FILA DINÂMICA (FIFO) - Fila de Espera de Adoção
 * ============================================================================ */
typedef struct NoFila {
    SolicitacaoAdocao dados;
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} FilaAdocao;

/* ============================================================================
 * 4. PILHA DINÂMICA (LIFO) - Histórico de Operações Recentes
 * ============================================================================ */
typedef struct NoPilha {
    char descricao_acao[MAX_DESCRICAO];
    char data_hora[MAX_DATA];
    struct NoPilha *abaixo;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int tamanho;
} PilhaHistorico;

/* ============================================================================
 * 5. LISTA DUPLAMENTE ENCADEADA - Prontuário / Agenda de Vacinação
 * ============================================================================ */
typedef struct NoListaDupla {
    int id_registro;
    int id_animal;
    char descricao_procedimento[MAX_DESCRICAO];
    char data[MAX_DATA];
    struct NoListaDupla *anterior;
    struct NoListaDupla *proximo;
} NoListaDupla;

typedef struct {
    NoListaDupla *inicio;
    NoListaDupla *fim;
    int tamanho;
} ListaProntuario;

#endif // ESTRUTURAS_H
