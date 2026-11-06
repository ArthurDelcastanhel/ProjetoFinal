#ifndef MODELOS_H
#define MODELOS_H

#include <stdbool.h>

#define MAX_NOME 80
#define MAX_RACA 50
#define MAX_CPF 15
#define MAX_TELEFONE 20
#define MAX_DESCRICAO 120
#define MAX_DATA 12

/**
 * Enumeração para representar a espécie do animal no abrigo.
 */
typedef enum {
    ESPECIE_CACHORRO = 1,
    ESPECIE_GATO = 2,
    ESPECIE_OUTRO = 3
} Especie;

/**
 * Enumeração para representar a situação atual do animal.
 */
typedef enum {
    STATUS_DISPONIVEL = 1,
    STATUS_EM_TRATAMENTO = 2,
    STATUS_ADOTADO = 3
} StatusAnimal;

/**
 * Entidade principal: Animal acolhido pelo abrigo.
 * Será armazenada em uma Árvore AVL indexada pelo código (id).
 */
typedef struct {
    int id;
    char nome[MAX_NOME];
    Especie especie;
    char raca[MAX_RACA];
    int idade_meses;
    bool vacinado;
    StatusAnimal status;
} Animal;

/**
 * Entidade: Adotante / Interessado cadastrado na ONG.
 * Será armazenada em uma Árvore Binária de Pesquisa (ABP) indexada pelo nome.
 */
typedef struct {
    int id;
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char telefone[MAX_TELEFONE];
} Adotante;

/**
 * Entidade para solicitação na fila de adoção.
 */
typedef struct {
    int id_adotante;
    char nome_adotante[MAX_NOME];
    int id_animal_pretendido;
    char data_solicitacao[MAX_DATA];
} SolicitacaoAdocao;

#endif // MODELOS_H
