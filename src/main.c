#include <stdio.h>
#include <stdlib.h>
#include "canil.h"

int main() {
    NoAVL *caes = NULL;
    NoABB *estoque = NULL;
    FilaEspera fila;
    inicializarFila(&fila);
    NoPilha *pilhaHistorico = NULL;

    // carrega os dados salvos caso já exista algum arquivo de execuções anteriores
    carregarDados(&caes, &estoque);

    // se não houver nenhum cão cadastrado ainda, permite que você crie os iniciais
    if (caes == NULL) {
        int qtdInicial;
        printf("Quantos cães iniciais voce deseja cadastrar agora? (Digite 0 para pular): ");
        if (scanf("%d", &qtdInicial) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            qtdInicial = 0;
        }

        int i = 0;
        while (i < qtdInicial) {
            int id, idade;
            char nome[50], raca[40];

            printf("\n    Cadastro Inicial %d    \n", i + 1);
            printf("ID/Microchip: ");
            scanf("%d", &id);
            printf("Nome do cão (sem espaços): ");
            scanf("%s", nome);
            printf("Raça (sem espaços): ");
            scanf("%s", raca);
            printf("Idade: ");
            scanf("%d", &idade);

            caes = inserirAVL(caes, id, nome, raca, idade);
            i = i + 1;
        }
    }

    int opcao;
    do {
        printf("\n==============================\n");
        printf("   CANIL - GESTÃO \n");
        printf("==============================\n");
        printf("1. Cadastrar Cão\n");
        printf("2. Listar Cães Cadastrados\n");
        printf("3. Adicionar a Fila de Espera\n");
        printf("4. Chamar Próximo Atendimento\n");
        printf("5. Ver Fila de Espera\n");
        printf("6. Ver Historico de Ações\n");
        printf("7. Desfazer Ultima Ação\n");
        printf("8. Cadastrar Item no Estoque (ABB)\n");
        printf("9. Listar Estoque\n");
        printf("10. Salvar Dados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        // valida a leitura para evitar loop infinito caso entre texto ou EOF
        // antes estava com um erro onde se eu digitasse um inteiro em um scanf que solicita string, entrava em loop infinito o menu de opções
        int lidos = scanf("%d", &opcao);
        if (lidos == EOF) {
            opcao = 0;
            printf("\nEntrada encerrada. Encerrando o sistema...\n");
            break;
        }
        if (lidos != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} // limpa o buffer até a quebra de linha
            printf("Entrada inválida! Digite apenas um número.\n");
            continue;
        }

        switch(opcao) {
            case 1: {
                int id, idade;
                char nome[50], raca[40];
                printf("ID: ");
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
                sprintf(acao, "Adicionado %s a fila", nome);
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
            case 8: {
                int codigo, qtd;
                char item[50];
                printf("Código do item: ");
                scanf("%d", &codigo);
                printf("Nome do item (sem espaços): ");
                scanf("%s", item);
                printf("Quantidade: ");
                scanf("%d", &qtd);

                estoque = inserirABB(estoque, codigo, item, qtd);
                char acao[100];
                sprintf(acao, "Adicionado %s ao estoque", item);
                empilhar(&pilhaHistorico, acao);
                printf("Item cadastrado no estoque!\n");
                break;
            }
            case 9:
                printf("\n ESTOQUE DO CANIL \n");
                emOrdemABB(estoque);
                break;
            case 10:
                salvarDados(caes, estoque);
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