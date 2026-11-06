#include <stdio.h>
#include <stdlib.h>
#include "modelos.h"
#include "estruturas.h"

void exibir_cabecalho(void) {
    printf("\n============================================================\n");
    printf("   SISTEMA DE GESTAO - ABRIGO DE ADOCAO DE ANIMAIS (ONG)    \n");
    printf("   IFSC - Engenharia de Telecomunicacoes - Programacao II   \n");
    printf("============================================================\n");
}

void exibir_menu_principal(void) {
    printf("\n[ MENU PRINCIPAL ]\n");
    printf("  1. Gerenciar Animais (Arvore AVL)\n");
    printf("  2. Gerenciar Adotantes (Arvore Binaria de Pesquisa - ABP)\n");
    printf("  3. Fila de Espera para Adocao (Fila FIFO)\n");
    printf("  4. Prontuario e Vacinacao (Lista Duplamente Encadeada)\n");
    printf("  5. Historico de Operacoes (Pilha LIFO)\n");
    printf("  6. Relatorios Gerais\n");
    printf("  0. Salvar e Sair\n");
    printf("------------------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    int opcao = -1;

    exibir_cabecalho();

    do {
        exibir_menu_principal();
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer de entrada
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                printf("\n[Modulo AVL - Cadastro de Animais em construcao...]\n");
                break;
            case 2:
                printf("\n[Modulo ABP - Cadastro de Adotantes em construcao...]\n");
                break;
            case 3:
                printf("\n[Modulo Fila - Fila de Adocao em construcao...]\n");
                break;
            case 4:
                printf("\n[Modulo Lista Dupla - Prontuario em construcao...]\n");
                break;
            case 5:
                printf("\n[Modulo Pilha - Historico de Acoes em construcao...]\n");
                break;
            case 6:
                printf("\n[Modulo de Relatorios em construcao...]\n");
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
