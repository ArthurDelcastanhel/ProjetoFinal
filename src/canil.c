#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canil.h"


// FUNÇÕES DA ÁRVORE AVL (para o cadastro dos cães)
// função que devolve a altura de um nó da AVL
int alturaAVL(NoAVL *n) {
    if (n == NULL) {        // se o nó não existir (for vazio)
        return 0;           // a altura dele é zero
    } else {                // caso o nó exista
        return n->altura;   // devolve a altura guardada dentro dele
    }
}

// função simples para descobrir qual entre dois números é o maior
int maior(int a, int b) {
    if (a > b) {            // se o valor 'a' for maior que 'b'
        return a;           // devolve 'a'
    } else {                // se não for
        return b;           // devolve 'b'
    }
}

// calcula a diferença de altura entre o lado esquerdo e o direito do nó
int fatorBalanceamento(NoAVL *n) {
    if (n == NULL) {                                    // se o nó for nulo
        return 0;                                       // não há desbalanceamento, retorna 0
    } else {                                            // se o nó existir
        return alturaAVL(n->esq) - alturaAVL(n->dir);   // subtrai a altura da direita da altura da esquerda
    }
}

// gira a subárvore para a direita quando o lado esquerdo fica pesado demais
NoAVL* rotacaoDireita(NoAVL *y) {
    NoAVL *x = y->esq;      // 'x' pega o filho da esquerda de 'y' (que vai virar a nova raiz)
    NoAVL *T2 = x->dir;     // 'T2' guarda a subárvore direita de 'x' para não perdermos

    x->dir = y;             // 'y' desce e vira filho da direita de 'x'
    y->esq = T2;            // a subárvore 'T2' é encaixada na esquerda de 'y'

    // recalcula a altura de 'y' somando 1 à maior altura entre seus dois filhos
    y->altura = maior(alturaAVL(y->esq), alturaAVL(y->dir)) + 1;
    // recalcula a altura de 'x' do mesmo jeito
    x->altura = maior(alturaAVL(x->esq), alturaAVL(x->dir)) + 1;

    return x;               // devolve 'x', que agora está no topo dessa parte da árvore
}

// gira a subárvore para a esquerda quando o lado direito fica pesado demais
NoAVL* rotacaoEsquerda(NoAVL *x) {
    NoAVL *y = x->dir;      // 'y' pega o filho da direita de 'x' (vai virar a nova raiz)
    NoAVL *T2 = y->esq;     // 'T2' guarda a subárvore esquerda de 'y'

    y->esq = x;             // 'x' desce e vira filho da esquerda de 'y'
    x->dir = T2;            // 'T2' é encaixada na direita de 'x'

    // atualiza as alturas de 'x' e depois de 'y' após o giro
    x->altura = maior(alturaAVL(x->esq), alturaAVL(x->dir)) + 1;
    y->altura = maior(alturaAVL(y->esq), alturaAVL(y->dir)) + 1;

    return y;               // devolve 'y' como nova raiz desse trecho
}

// insere um novo cão na árvore AVL e faz o balanceamento se precisar
NoAVL* inserirAVL(NoAVL* no, int id, char* nome, char* raca, int idade) {
    if (no == NULL) {                                       // se achou um lugar vazio na árvore
        NoAVL* novo = (NoAVL*)malloc(sizeof(NoAVL));        // reserva espaço na memória para o novo cão
        novo->id = id;                                      // guarda o ID digitado
        strcpy(novo->nome, nome);                           // copia o nome para dentro da struct
        strcpy(novo->raca, raca);                           // copia a raça para dentro da struct
        novo->idade = idade;                                // guarda a idade
        novo->altura = 1;                                   // todo nó novo começa como folha, com altura 1
        novo->esq = NULL;                                   // começa sem filho na esquerda
        novo->dir = NULL;                                   // começa sem filho na direita
        return novo;                                        // entrega o nó recém-criado
    }

    if (id < no->id) {                                      // se o ID novo for menor que o ID atual
        no->esq = inserirAVL(no->esq, id, nome, raca, idade); // continua procurando vaga pelo lado esquerdo
    } else if (id > no->id) {                               // Se o ID novo for maior que o ID atual
        no->dir = inserirAVL(no->dir, id, nome, raca, idade); // Continua procurando vaga pelo lado direito
    } else {                                                // Se o ID for igual
        return no;                                          // Não faz nada, pois não aceita ID repetido
    }

    // Atualiza a altura do nó atual depois de ter inserido lá embaixo
    no->altura = 1 + maior(alturaAVL(no->esq), alturaAVL(no->dir));

    // Verifica se o nó ficou torto (desbalanceado)
    int balance = fatorBalanceamento(no);

    // Caso 1: Pesado na esquerda e inseriu na esquerda (Rotação simples à direita)
    if (balance > 1 && id < no->esq->id) {
        return rotacaoDireita(no);
    }
    // Caso 2: Pesado na direita e inseriu na direita (Rotação simples à esquerda)
    if (balance < -1 && id > no->dir->id) {
        return rotacaoEsquerda(no);
    }
    // Caso 3: Pesado na esquerda, mas inseriu na direita do filho (Rotação dupla Esquerda-Direita)
    if (balance > 1 && id > no->esq->id) {
        no->esq = rotacaoEsquerda(no->esq);                 // Gira o filho para a esquerda primeiro
        return rotacaoDireita(no);                          // Depois gira o pai para a direita
    }
    // Caso 4: Pesado na direita, mas inseriu na esquerda do filho (Rotação dupla Direita-Esquerda)
    if (balance < -1 && id < no->dir->id) {
        no->dir = rotacaoDireita(no->dir);                  // Gira o filho para a direita primeiro
        return rotacaoEsquerda(no);                         // Depois gira o pai para a esquerda
    }

    return no;                                              // Devolve o nó sem mudanças se já estiver equilibrado
}

// Procura um cão específico na AVL pelo ID
NoAVL* buscarAVL(NoAVL* raiz, int id) {
    if (raiz == NULL || raiz->id == id) {   // Se a árvore acabou (não achou) ou se achou o ID exato
        return raiz;                        // Retorna o próprio nó (ou NULL se não existir)
    }
    if (id < raiz->id) {                    // Se o ID procurado for menor que o nó atual
        return buscarAVL(raiz->esq, id);    // Procura do lado esquerdo
    } else {                                // Se for maior
        return buscarAVL(raiz->dir, id);    // Procura do lado direito
    }
}

// Acha o nó com o menor ID (usado na hora de remover um nó com dois filhos)
NoAVL* menorValorNo(NoAVL* no) {
    NoAVL* atual = no;                      // Começa pelo nó recebido
    while (atual->esq != NULL) {            // Enquanto houver filho na esquerda
        atual = atual->esq;                 // Vai descendo para a esquerda (onde ficam os menores valores)
    }
    return atual;                           // Retorna o menor nó encontrado
}

// Remove um cão da árvore AVL e rebalanceia se for necessário
NoAVL* removerAVL(NoAVL* raiz, int id) {
    if (raiz == NULL) {                                     // Se a árvore estiver vazia ou não achar o ID
        return raiz;                                        // Retorna NULL mesmo
    }

    if (id < raiz->id) {                                    // Se o ID que queremos apagar está na esquerda
        raiz->esq = removerAVL(raiz->esq, id);              // Chama a remoção para o lado esquerdo
    } else if (id > raiz->id) {                             // Se o ID está na direita
        raiz->dir = removerAVL(raiz->dir, id);              // Chama a remoção para o lado direito
    } else {                                                // Achamos o nó que deve ser removido!
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {   // Se o nó tiver apenas 1 filho ou nenhum
            NoAVL *temp;                                    // Cria um ponteiro auxiliar
            if (raiz->esq != NULL) {                        // Se o filho que existe for o da esquerda
                temp = raiz->esq;                           // 'temp' aponta para o filho da esquerda
            } else {                                        // Caso contrário
                temp = raiz->dir;                           // 'temp' aponta para o da direita (que pode até ser NULL)
            }

            if (temp == NULL) {                             // Se não tinha filho nenhum (nó folha)
                temp = raiz;                                // 'temp' guarda o nó atual para limparmos da memória
                raiz = NULL;                                // O lugar dele fica vazio
            } else {                                        // Se tinha 1 filho
                *raiz = *temp;                              // Copia todos os dados do filho para o lugar do pai
            }
            free(temp);                                     // Libera a memória do nó apagado
        } else {                                            // Se o nó tiver os 2 filhos
            NoAVL* temp = menorValorNo(raiz->dir);          // Pega o menor nó do lado direito para substituir
            raiz->id = temp->id;                            // Copia o ID do substituto
            strcpy(raiz->nome, temp->nome);                 // Copia o nome do substituto
            strcpy(raiz->raca, temp->raca);                 // Copia a raça do substituto
            raiz->idade = temp->idade;                      // Copia a idade do substituto
            raiz->dir = removerAVL(raiz->dir, temp->id);    // Remove o nó substituto que ficou duplicado lá embaixo
        }
    }

    if (raiz == NULL) {                                     // Se a árvore ficou vazia após apagar o único nó
        return raiz;                                        // Já retorna NULL direto
    }

    // Atualiza a altura do nó atual
    raiz->altura = 1 + maior(alturaAVL(raiz->esq), alturaAVL(raiz->dir));

    // Calcula o fator de balanceamento para ver se entortou após a remoção
    int balance = fatorBalanceamento(raiz);

    // Rebalanceia com as 4 rotações caso tenha saído do limite (-1, 0, 1)
    if (balance > 1 && fatorBalanceamento(raiz->esq) >= 0) {
        return rotacaoDireita(raiz);
    }
    if (balance > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    if (balance < -1 && fatorBalanceamento(raiz->dir) <= 0) {
        return rotacaoEsquerda(raiz);
    }
    if (balance < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;                                            // Devolve a raiz atualizada e balanceada
}

// Imprime todos os cães em ordem crescente de ID
void emOrdemAVL(NoAVL* raiz) {
    if (raiz != NULL) {                                     // Se o nó não for nulo
        emOrdemAVL(raiz->esq);                              // Visita primeiro todos os menores (esquerda)
        printf("[ID: %d] Nome: %s | Raca: %s | Idade: %d ano(s)\n", raiz->id, raiz->nome, raiz->raca, raiz->idade); // Mostra na tela
        emOrdemAVL(raiz->dir);                              // Visita depois todos os maiores (direita)
    }
}

// Conta quantos cães estão cadastrados na árvore no total (para o relatório)
int contarCaesAVL(NoAVL* raiz) {
    if (raiz == NULL) {                                     // Se chegou numa ponta vazia
        return 0;                                           // Soma zero
    } else {                                                // Se tem um cão aqui
        return 1 + contarCaesAVL(raiz->esq) + contarCaesAVL(raiz->dir); // Conta 1 (ele mesmo) + os da esquerda + os da direita
    }
}

// ==========================================
// FUNÇÕES DA ABB (Estoque de Suprimentos)
// ==========================================

// Insere um item no estoque usando uma Árvore de Busca Binária (ABB)
NoABB* inserirABB(NoABB* raiz, int codigo, char* item, int quantidade) {
    if (raiz == NULL) {                                     // Se encontrou a posição vazia na árvore
        NoABB* novo = (NoABB*)malloc(sizeof(NoABB));        // Aloca memória para o novo item de estoque
        novo->codigo = codigo;                              // Salva o código do item
        strcpy(novo->item, item);                           // Salva o nome do produto
        novo->quantidade = quantidade;                      // Salva a quantidade inicial
        novo->esq = NULL;                                   // Inicia ponteiro esquerdo vazio
        novo->dir = NULL;                                   // Inicia ponteiro direito vazio
        return novo;                                        // Retorna o novo nó criado
    }
    if (codigo < raiz->codigo) {                            // Se o código for menor que o atual
        raiz->esq = inserirABB(raiz->esq, codigo, item, quantidade); // Vai para a esquerda
    } else if (codigo > raiz->codigo) {                     // Se o código for maior que o atual
        raiz->dir = inserirABB(raiz->dir, codigo, item, quantidade); // Vai para a direita
    }
    return raiz;                                            // Retorna a raiz sem alterar se o código já existir
}

// Busca um produto no estoque pelo código na ABB
NoABB* buscarABB(NoABB* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo == codigo) {           // Se não achou ou se é exatamente este nó
        return raiz;                                        // Retorna o resultado
    }
    if (codigo < raiz->codigo) {                            // Se o código buscado for menor
        return buscarABB(raiz->esq, codigo);                // Busca na subárvore esquerda
    } else {                                                // Se for maior
        return buscarABB(raiz->dir, codigo);                // Busca na subárvore direita
    }
}

// Lista o estoque em ordem crescente de código
void emOrdemABB(NoABB* raiz) {
    if (raiz != NULL) {                                     // Se o nó existe
        emOrdemABB(raiz->esq);                              // Imprime primeiro os códigos menores
        printf("[Cod: %d] Item: %s | Qtd: %d\n", raiz->codigo, raiz->item, raiz->quantidade); // Mostra o item
        emOrdemABB(raiz->dir);                              // Imprime depois os códigos maiores
    }
}

// Conta quantos tipos de itens existem cadastrados na ABB do estoque
int contarItensABB(NoABB* raiz) {
    if (raiz == NULL) {                                     // Se o nó for vazio
        return 0;                                           // Retorna 0
    } else {                                                // Se o nó existir
        return 1 + contarItensABB(raiz->esq) + contarItensABB(raiz->dir); // Soma 1 com os filhos dos dois lados
    }
}

// ==========================================
// FUNÇÕES DA FILA (Atendimento Veterinário)
// ==========================================

// Prepara a fila para uso deixando os ponteiros zerados
void inicializarFila(FilaEspera *f) {
    f->inicio = NULL;                                       // Começo da fila aponta para nada
    f->fim = NULL;                                          // Fim da fila aponta para nada
}

// Coloca um cão no final da fila de atendimento
void enfileirar(FilaEspera *f, char* nomeCao, char* motivo) {
    NoFila *novo = (NoFila*)malloc(sizeof(NoFila));         // Cria espaço na memória para o atendimento
    strcpy(novo->nomeCao, nomeCao);                         // Guarda o nome do cão
    strcpy(novo->motivo, motivo);                           // Guarda o motivo da consulta
    novo->prox = NULL;                                      // Como ele é o último da fila, não tem ninguém atrás dele

    if (f->fim == NULL) {                                   // Se a fila estava totalmente vazia
        f->inicio = novo;                                   // Ele passa a ser o primeiro da fila também
    } else {                                                // Se já tinha gente na fila
        f->fim->prox = novo;                                // O antigo último agora aponta para esse novo cão
    }
    f->fim = novo;                                          // Atualiza o ponteiro de fim para o novo cão
    printf("-> Cao '%s' entrou na fila de espera.\n", nomeCao); // Avisa na tela
}

// Chama o primeiro cão da fila para ser atendido e tira ele da espera
void desenfileirar(FilaEspera *f) {
    if (f->inicio == NULL) {                                // Verifica se não tem ninguém esperando
        printf("Fila de espera vazia!\n");                  // Avisa que não há cães na fila
        return;                                             // Sai da função
    }
    NoFila *temp = f->inicio;                               // Guarda o primeiro da fila num ponteiro temporário
    printf("-> Atendendo agora: %s (Motivo: %s)\n", temp->nomeCao, temp->motivo); // Mostra quem foi chamado
    f->inicio = f->inicio->prox;                            // O segundo da fila vira o novo primeiro

    if (f->inicio == NULL) {                                // Se a fila acabou de ficar vazia após chamar este cão
        f->fim = NULL;                                      // O ponteiro de fim também precisa virar NULL
    }
    free(temp);                                             // Libera a memória do atendimento que já foi feito
}

// Mostra todos os cães que estão aguardando na fila por ordem de chegada
void mostrarFila(FilaEspera *f) {
    NoFila *atual = f->inicio;                              // Começa a leitura pelo primeiro da fila
    printf("\n--- FILA DE ESPERA VETERINARIA ---\n");       // Cabeçalho na tela
    if (atual == NULL) {                                    // Se não tiver ninguém
        printf("Nenhum cao aguardando atendimento.\n");     // Avisa o usuário
        return;                                             // Sai da função
    }
    int pos = 1;                                            // Variável para numerar a posição na fila (1º, 2º...)
    while (atual != NULL) {                                 // Enquanto não chegar ao final da fila
        printf("%d. Cao: %s | Motivo: %s\n", pos, atual->nomeCao, atual->motivo); // Imprime os dados do cão
        pos = pos + 1;                                      // Aumenta o número da posição
        atual = atual->prox;                                // Passa para o próximo da fila
    }
}

// Conta quantos cães estão esperando atendimento no momento
int contarFila(FilaEspera *f) {
    int cont = 0;                                           // Começa o contador em zero
    NoFila *atual = f->inicio;                              // Começa pelo início da fila
    while (atual != NULL) {                                 // Percorre até o final
        cont = cont + 1;                                    // Soma 1 para cada cão encontrado
        atual = atual->prox;                                // Vai para o próximo
    }
    return cont;                                            // Devolve o total contado
}

// ==========================================
// FUNÇÕES DA PILHA (Histórico / Undo)
// ==========================================

// Registra uma ação nova no topo da pilha de histórico
void empilhar(NoPilha **topo, char* descricao) {
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));      // Aloca memória para o registro do histórico
    strcpy(novo->descricao, descricao);                     // Copia o texto do que foi feito
    novo->prox = *topo;                                     // Faz o novo item apontar para o antigo topo da pilha
    *topo = novo;                                           // Atualiza o topo para ser este novo item
}

// Remove a última ação colocada na pilha (Desfazer)
void desempilhar(NoPilha **topo) {
    if (*topo == NULL) {                                    // Se a pilha estiver vazia
        printf("Nenhuma acao no historico para desfazer.\n"); // Avisa que não tem nada para remover
        return;                                             // Sai da função
    }
    NoPilha *temp = *topo;                                  // Guarda o item do topo para poder apagar
    printf("-> Acao desfeita/removida do log: %s\n", temp->descricao); // Mostra qual ação foi desfeita
    *topo = temp->prox;                                     // O topo passa a ser o item que estava logo abaixo
    free(temp);                                             // Libera a memória do item removido
}

// Lista todo o histórico, do mais recente para o mais antigo
void mostrarPilha(NoPilha *topo) {
    printf("\n--- HISTORICO DE ACOES (DO MAIS RECENTE AO MAIS ANTIGO) ---\n");
    if (topo == NULL) {                                     // Se não houve nenhuma ação ainda
        printf("Historico vazio.\n");                       // Informa na tela
        return;                                             // Sai da função
    }
    NoPilha *atual = topo;                                  // Começa pelo topo da pilha
    while (atual != NULL) {                                 // Enquanto houver itens para baixo
        printf("- %s\n", atual->descricao);                 // Imprime a descrição da ação
        atual = atual->prox;                                // Desce para o próximo item da pilha
    }
}

// ==========================================
// PERSISTÊNCIA DE DADOS (Arquivos TXT)
// ==========================================

// Função auxiliar que percorre a árvore AVL gravando cada cão no arquivo
void salvarAuxAVL(NoAVL *raiz, FILE *f) {
    if (raiz != NULL) {                                     // Se o nó existe
        fprintf(f, "%d %s %s %d\n", raiz->id, raiz->nome, raiz->raca, raiz->idade); // Escreve os dados numa linha do arquivo
        salvarAuxAVL(raiz->esq, f);                         // Faz o mesmo para os filhos da esquerda
        salvarAuxAVL(raiz->dir, f);                         // Faz o mesmo para os filhos da direita
    }
}

// Função auxiliar que percorre a árvore ABB gravando cada item de estoque no arquivo
void salvarAuxABB(NoABB *raiz, FILE *f) {
    if (raiz != NULL) {                                     // Se o nó existe
        fprintf(f, "%d %s %d\n", raiz->codigo, raiz->item, raiz->quantidade); // Escreve código, nome e quantidade no arquivo
        salvarAuxABB(raiz->esq, f);                         // Grava a subárvore esquerda
        salvarAuxABB(raiz->dir, f);                         // Grava a subárvore direita
    }
}

// Salva todos os cães e itens de estoque em arquivos de texto antes de fechar
void salvarDados(NoAVL *caes, NoABB *estoque) {
    FILE *fCaes = fopen("caes.txt", "w");                   // Abre (ou cria) o arquivo caes.txt para escrita
    if (fCaes != NULL) {                                    // Se conseguiu abrir o arquivo sem erro
        salvarAuxAVL(caes, fCaes);                          // Chama a função que escreve todos os cães lá dentro
        fclose(fCaes);                                      // Fecha o arquivo para salvar de verdade no disco
    }

    FILE *fEstoque = fopen("estoque.txt", "w");             // Abre (ou cria) o arquivo estoque.txt para escrita
    if (fEstoque != NULL) {                                 // Se abriu tudo certo
        salvarAuxABB(estoque, fEstoque);                    // Grava todos os itens da árvore ABB de estoque
        fclose(fEstoque);                                   // Fecha o arquivo
    }
    printf("Dados salvos com sucesso em 'caes.txt' e 'estoque.txt'!\n"); // Confirma para o usuário
}

// Lê os arquivos de texto ao abrir o programa para recuperar os cadastros anteriores
void carregarDados(NoAVL **caes, NoABB **estoque) {
    FILE *fCaes = fopen("caes.txt", "r");                   // Tenta abrir o arquivo de cães em modo leitura ("r")
    if (fCaes != NULL) {                                    // Se o arquivo já existir no computador
        int id, idade;                                      // Variáveis para ler os números
        char nome[50], raca[40];                            // Variáveis para ler os textos
        while (fscanf(fCaes, "%d %s %s %d", &id, nome, raca, &idade) == 4) { // Lê linha por linha enquanto achar os 4 dados
            *caes = inserirAVL(*caes, id, nome, raca, idade); // Insere cada cão lido de volta na árvore AVL
        }
        fclose(fCaes);                                      // Fecha o arquivo após terminar a leitura
    }

    FILE *fEstoque = fopen("estoque.txt", "r");             // Tenta abrir o arquivo de estoque para leitura
    if (fEstoque != NULL) {                                 // Se o arquivo existir
        int codigo, qtd;                                    // Variáveis para código e quantidade
        char item[50];                                      // Variável para o nome do produto
        while (fscanf(fEstoque, "%d %s %d", &codigo, item, &qtd) == 3) { // Lê cada linha do arquivo
            *estoque = inserirABB(*estoque, codigo, item, qtd); // Coloca o produto de volta na árvore ABB
        }
        fclose(fEstoque);                                   // Fecha o arquivo de estoque
    }
}