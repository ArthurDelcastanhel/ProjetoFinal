#include <stdio.h>
#include <stdlib.h>
#include "canil.h"

int main() {
    NoAVL *caes = NULL;
    NoABP *estoque = NULL;
    FilaEspera fila;
    inicializarFila(&fila);
    NoPilha *pilhaHistorico = NULL;

    // Escolhi alguns dados aleatórios só para fazer um teste
    caes = inserirAVL(caes, 101, "Bob", "Labrador", 3);
    caes = inserirAVL(caes, 102, "Mel", "Poodle", 5);
    estoque = inserirABP(estoque, 50, "Racao_15kg", 10);

    int opcao;
    do {
        printf("\n==============================\n");
        printf("   CANIL - GESTÃO \n");
        printf("==============================\n");
        printf("1. Cadastrar Cão \n");
        printf("2. Listar Cães Cadastrados\n");
        printf("3. Adicionar à Fila de Espera (Fila)\n");
        printf("4. Chamar Próximo Atendimento\n");
        printf("5. Ver Fila de Espera\n");
        printf("6. Ver Historico de Ações\n");
        printf("7. Desfazer Ultima Ação\n");
        printf("8. Salvar Dados (Persistência)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                int id, idade;
                char nome[50], raca[40];
                printf("ID/Microchip: ");
                scanf("%d", &id);
                printf("Nome do cão: ");
                scanf("%s", nome);
                printf("Raça: ");
                scanf("%s", raca);
                printf("Idade: ");
                scanf("%d", &idade);

                caes = inserirAVL(caes, id, nome, raca, idade);
                char acao[100];
                sprintf(acao, "Cadastro do cão %s", nome);
                empilhar(&pilhaHistorico, acao);
                printf("Cão cadastrado com sucesso!\n");
                break;
            }
            case 2:
                printf("\n LISTA DE CÃES \n");
                emOrdemAVL(caes);
                break;
            case 3: {
                char nome[50], motivo[50];
                printf("Nome do cão: ");
                scanf("%s", nome);
                printf("Motivo do atendimento: ");
                scanf("%s", motivo);
                enfileirar(&fila, nome, motivo);
                char acao[100];
                sprintf(acao, "Adicionado %s à fila", nome);
                empilhar(&pilhaHistorico, acao);
                break;
            }
            case 4:
                desenfileirar(&fila);
                break;
            case 5:
                mostrarFila(&fila);
                break;
            case 6:
                mostrarPilha(pilhaHistorico);
                break;
            case 7:
                desempilhar(&pilhaHistorico);
                break;
            case 8:
                salvarDados(estoque);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}