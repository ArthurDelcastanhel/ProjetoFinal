#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "canil.h"


// funções da árvore avl (para o cadastro dos cães)
// função que devolve a altura de um nó da avl
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

// insere um novo cão na árvore avl e faz o balanceamento se precisar
NoAVL* inserirAVL(NoAVL* no, int id, char* nome, char* raca, int idadeAnos, int idadeMeses) {
    if (no == NULL) {                                       // se achou um lugar vazio na árvore
        NoAVL* novo = (NoAVL*)malloc(sizeof(NoAVL));        // reserva espaço na memória para o novo cão
        novo->id = id;                                      // guarda o id digitado
        strcpy(novo->nome, nome);                           // copia o nome para dentro da struct
        strcpy(novo->raca, raca);                           // copia a raça para dentro da struct
        novo->idadeAnos = idadeAnos;                        // guarda os anos da idade
        novo->idadeMeses = idadeMeses;                      // guarda os meses da idade
        novo->altura = 1;                                   // tod0 nó novo começa como folha, com altura 1
        novo->esq = NULL;                                   // começa sem filho na esquerda
        novo->dir = NULL;                                   // começa sem filho na direita
        return novo;                                        // entrega o nó recém-criado
    }

    if (id < no->id) {                                      // se o id novo for menor que o id atual
        no->esq = inserirAVL(no->esq, id, nome, raca, idadeAnos, idadeMeses); // continua procurando um lugar vago pelo lado esquerdo
    } else if (id > no->id) {                               // se o id novo for maior que o id atual
        no->dir = inserirAVL(no->dir, id, nome, raca, idadeAnos, idadeMeses); // continua procurando vaga pelo lado direito
    } else {                                                // se o id for igual
        return no;                                          // não faz nada, pois não aceita id repetido
    }

    // atualiza a altura do nó atual depois de ter inserido lá embaixo
    no->altura = 1 + maior(alturaAVL(no->esq), alturaAVL(no->dir));

    // verifica se o nó ficou torto (desbalanceado)
    int balance = fatorBalanceamento(no);

    // caso 1: pesado na esquerda e inseriu na esquerda (rotação simples à direita)
    if (balance > 1 && id < no->esq->id) {
        return rotacaoDireita(no);
    }
    // caso 2: pesado na direita e inseriu na direita (rotação simples à esquerda)
    if (balance < -1 && id > no->dir->id) {
        return rotacaoEsquerda(no);
    }
    // caso 3: pesado na esquerda, mas inseriu na direita do filho (rotação dupla esquerda-direita)
    if (balance > 1 && id > no->esq->id) {
        no->esq = rotacaoEsquerda(no->esq);                 // gira o filho para a esquerda primeiro
        return rotacaoDireita(no);                          // depois gira o pai para a direita
    }
    // caso 4: pesado na direita, mas inseriu na esquerda do filho (rotação dupla direita-esquerda)
    if (balance < -1 && id < no->dir->id) {
        no->dir = rotacaoDireita(no->dir);                  // gira o filho para a direita primeiro
        return rotacaoEsquerda(no);                         // depois gira o pai para a esquerda
    }

    return no;                                              // devolve o nó sem mudanças se já estiver equilibrado
}

// procura um cão específico na avl pelo id
NoAVL* buscarAVL(NoAVL* raiz, int id) {
    if (raiz == NULL || raiz->id == id) {   // se a árvore acabou (não achou) ou se achou o id exato
        return raiz;                        // retorna o próprio nó (ou null se não existir)
    }
    if (id < raiz->id) {                    // se o id procurado for menor que o nó atual
        return buscarAVL(raiz->esq, id);    // procura do lado esquerdo
    } else {                                // se for maior
        return buscarAVL(raiz->dir, id);    // procura do lado direito
    }
}

// acha o nó com o menor id (usado na hora de remover um nó com dois filhos)
NoAVL* menorValorNo(NoAVL* no) {
    NoAVL* atual = no;                      // começa pelo nó recebido
    while (atual->esq != NULL) {            // enquanto houver filho na esquerda
        atual = atual->esq;                 // vai descendo para a esquerda (onde ficam os menores valores)
    }
    return atual;                           // retorna o menor nó encontrado
}

// remove um cão da árvore avl e rebalanceia se for necessário
NoAVL* removerAVL(NoAVL* raiz, int id) {
    if (raiz == NULL) {                                     // se a árvore estiver vazia ou não achar o id
        return raiz;                                        // retorna null mesmo
    }

    if (id < raiz->id) {                                    // se o id que queremos apagar está na esquerda
        raiz->esq = removerAVL(raiz->esq, id);              // chama a remoção para o lado esquerdo
    } else if (id > raiz->id) {                             // se o id está na direita
        raiz->dir = removerAVL(raiz->dir, id);              // chama a remoção para o lado direito
    } else {                                                // achamos o nó que deve ser removido!
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {   // se o nó tiver apenas 1 filho ou nenhum
            NoAVL *temp;                                    // cria um ponteiro auxiliar
            if (raiz->esq != NULL) {                        // se o filho que existe for o da esquerda
                temp = raiz->esq;                           // 'temp' aponta para o filho da esquerda
            } else {                                        // caso contrário
                temp = raiz->dir;                           // 'temp' aponta para o da direita (que pode até ser null)
            }

            if (temp == NULL) {                             // se não tinha filho nenhum (nó folha)
                temp = raiz;                                // 'temp' guarda o nó atual para limparmos da memória
                raiz = NULL;                                // o lugar dele fica vazio
            } else {                                        // se tinha 1 filho
                *raiz = *temp;                              // copia todos os dados do filho para o lugar do pai
            }
            free(temp);                                     // libera a memória do nó apagado
        } else {                                            // se o nó tiver os 2 filhos
            NoAVL* temp = menorValorNo(raiz->dir);          // pega o menor nó do lado direito para substituir
            raiz->id = temp->id;                            // copia o id do substituto
            strcpy(raiz->nome, temp->nome);                 // copia o nome do substituto
            strcpy(raiz->raca, temp->raca);                 // copia a raça do substituto
            raiz->idadeAnos = temp->idadeAnos;              // copia os anos do substituto
            raiz->idadeMeses = temp->idadeMeses;            // copia os meses do substituto
            raiz->dir = removerAVL(raiz->dir, temp->id);    // remove o nó substituto que ficou duplicado lá embaixo
        }
    }

    if (raiz == NULL) {                                     // se a árvore ficou vazia após apagar o único nó
        return raiz;                                        // já retorna null direto
    }

    // atualiza a altura do nó atual
    raiz->altura = 1 + maior(alturaAVL(raiz->esq), alturaAVL(raiz->dir));

    // calcula o fator de balanceamento para ver se entortou após a remoção
    int balance = fatorBalanceamento(raiz);

    // rebalanceia com as 4 rotações caso tenha saído do limite (-1, 0, 1)
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

    return raiz;                                            // devolve a raiz atualizada e balanceada
}

// imprime todos os cães em ordem crescente de id
void emOrdemAVL(NoAVL* raiz) {
    if (raiz != NULL) {                                     // se o nó não for nulo
        emOrdemAVL(raiz->esq);                              // visita primeiro todos os menores (esquerda)
        printf("ID: %d | Nome: %s | Raça: %s | Idade: %d ano(s) e %d mes(es)\n",
               raiz->id, raiz->nome, raiz->raca, raiz->idadeAnos, raiz->idadeMeses); // mostra na tela
        emOrdemAVL(raiz->dir);                              // visita depois todos os maiores (direita)
    }
}

// conta quantos cães estão cadastrados na árvore no total (para o relatório)
int contarCaesAVL(NoAVL* raiz) {
    if (raiz == NULL) {                                     // se chegou numa ponta vazia
        return 0;                                           // soma zero
    } else {                                                // se tem um cão aqui
        return 1 + contarCaesAVL(raiz->esq) + contarCaesAVL(raiz->dir); // conta 1 (ele mesmo) + os da esquerda + os da direita
    }
}


// funções da abb (estoque de suprimentos)
// insere um item no estoque usando uma árvore de busca binária (abb)
NoABB* inserirABB(NoABB* raiz, int codigo, char* item, int quantidade) {
    if (raiz == NULL) {                                     // se encontrou a posição vazia na árvore
        NoABB* novo = (NoABB*)malloc(sizeof(NoABB));        // aloca memória para o novo item de estoque
        novo->codigo = codigo;                              // salva o código do item
        strcpy(novo->item, item);                           // salva o nome do produto
        novo->quantidade = quantidade;                      // salva a quantidade inicial
        novo->esq = NULL;                                   // inicia ponteiro esquerdo vazio
        novo->dir = NULL;                                   // inicia ponteiro direito vazio
        return novo;                                        // retorna o novo nó criado
    }
    if (codigo < raiz->codigo) {                            // se o código for menor que o atual
        raiz->esq = inserirABB(raiz->esq, codigo, item, quantidade); // vai para a esquerda
    } else if (codigo > raiz->codigo) {                     // se o código for maior que o atual
        raiz->dir = inserirABB(raiz->dir, codigo, item, quantidade); // vai para a direita
    }
    return raiz;                                            // retorna a raiz sem alterar se o código já existir
}

// busca um produto no estoque pelo código na abb
NoABB* buscarABB(NoABB* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo == codigo) {           // se não achou ou se é exatamente este nó
        return raiz;                                        // retorna o resultado
    }
    if (codigo < raiz->codigo) {                            // se o código buscado for menor
        return buscarABB(raiz->esq, codigo);                // busca na subárvore esquerda
    } else {                                                // se for maior
        return buscarABB(raiz->dir, codigo);                // busca na subárvore direita
    }
}

// lista o estoque em ordem crescente de código
void emOrdemABB(NoABB* raiz) {
    if (raiz != NULL) {                                     // se o nó existe
        emOrdemABB(raiz->esq);                              // imprime primeiro os códigos menores
        printf("Código: %d | Item: %s | Quantidade: %d\n", raiz->codigo, raiz->item, raiz->quantidade); // mostra o item
        emOrdemABB(raiz->dir);                              // imprime depois os códigos maiores
    }
}

// conta quantos tipos de itens existem cadastrados na abb do estoque
int contarItensABB(NoABB* raiz) {
    if (raiz == NULL) {                                     // se o nó for vazio
        return 0;                                           // retorna 0
    } else {                                                // se o nó existir
        return 1 + contarItensABB(raiz->esq) + contarItensABB(raiz->dir); // soma 1 com os filhos dos dois lados
    }
}


// funções da fila (atendimento veterinário)
// prepara a fila para uso deixando os ponteiros zerados
void inicializarFila(FilaEspera *f) {
    f->inicio = NULL;                                       // começo da fila aponta para nada
    f->fim = NULL;                                          // fim da fila aponta para nada
}

// coloca um cão no final da fila de atendimento
void enfileirar(FilaEspera *f, char* nomeCao, char* motivo) {
    NoFila *novo = (NoFila*)malloc(sizeof(NoFila));         // cria espaço na memória para o atendimento
    strcpy(novo->nomeCao, nomeCao);                         // guarda o nome do cão
    strcpy(novo->motivo, motivo);                           // guarda o motivo da consulta
    novo->prox = NULL;                                      // como ele é o último da fila, não tem ninguém atrás dele

    if (f->fim == NULL) {                                   // se a fila estava totalmente vazia
        f->inicio = novo;                                   // ele passa a ser o primeiro da fila também
    } else {                                                // se já tinha gente na fila
        f->fim->prox = novo;                                // o antigo último agora aponta para esse novo cão
    }
    f->fim = novo;                                          // atualiza o ponteiro de fim para o novo cão
    printf(" Cão '%s' entrou na fila de espera.\n", nomeCao); // avisa na tela
}

// chama o primeiro cão da fila para ser atendido e tira ele da espera
void desenfileirar(FilaEspera *f) {
    if (f->inicio == NULL) {                                // verifica se não tem ninguém esperando
        printf("Fila de espera vazia!\n");                  // avisa que não há cães na fila
        return;                                             // sai da função
    }
    NoFila *temp = f->inicio;                               // guarda o primeiro da fila num ponteiro temporário
    printf(" Atendendo agora: %s (Motivo: %s)\n", temp->nomeCao, temp->motivo); // mostra quem foi chamado
    f->inicio = f->inicio->prox;                            // o segundo da fila vira o novo primeiro

    if (f->inicio == NULL) {                                // se a fila acabou de ficar vazia após chamar este cão
        f->fim = NULL;                                      // o ponteiro de fim também precisa virar null
    }
    free(temp);                                             // libera a memória do atendimento que já foi feito
}

// mostra todos os cães que estão aguardando na fila por ordem de chegada
void mostrarFila(FilaEspera *f) {
    NoFila *atual = f->inicio;                              // começa a leitura pelo primeiro da fila
    printf("\n FILA DE ESPERA VETERINÁRIA \n");       // cabeçalho na tela
    if (atual == NULL) {                                    // se não tiver ninguém
        printf("Nenhum cão aguardando atendimento.\n");     // avisa o usuário
        return;                                             // sai da função
    }
    int pos = 1;                                            // variável para numerar a posição na fila (1º, 2º...)
    while (atual != NULL) {                                 // enquanto não chegar ao final da fila
        printf("%d. Cão: %s | Motivo: %s\n", pos, atual->nomeCao, atual->motivo); // imprime os dados do cão
        pos = pos + 1;                                      // aumenta o número da posição
        atual = atual->prox;                                // passa para o próximo da fila
    }
}

// conta quantos cães estão esperando atendimento no momento
int contarFila(FilaEspera *f) {
    int cont = 0;                                           // começa o contador em zero
    NoFila *atual = f->inicio;                              // começa pelo início da fila
    while (atual != NULL) {                                 // percorre até o final
        cont = cont + 1;                                    // soma 1 para cada cão encontrado
        atual = atual->prox;                                // vai para o próximo
    }
    return cont;                                            // devolve o total contado
}


// funções da pilha (histórico / undo)
// registra uma ação nova no topo da pilha de histórico
void empilhar(NoPilha **topo, char* descricao) {
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));      // aloca memória para o registro do histórico
    strcpy(novo->descricao, descricao);                     // copia o texto do que foi feito
    novo->prox = *topo;                                     // faz o novo item apontar para o antigo topo da pilha
    *topo = novo;                                           // atualiza o topo para ser este novo item
}

// remove a última ação colocada na pilha (desfazer)
void desempilhar(NoPilha **topo) {
    if (*topo == NULL) {                                    // se a pilha estiver vazia
        printf("Nenhuma ação no histórico para desfazer.\n"); // avisa que não tem nada para remover
        return;                                             // sai da função
    }
    NoPilha *temp = *topo;                                  // guarda o item do topo para poder apagar
    printf("-> Ação desfeita/removida do log: %s\n", temp->descricao); // mostra qual ação foi desfeita
    *topo = temp->prox;                                     // o topo passa a ser o item que estava logo abaixo
    free(temp);                                             // libera a memória do item removido
}

// lista tod0 o histórico, do mais recente para o mais antigo
void mostrarPilha(NoPilha *topo) {
    printf("\n HISTÓRICO DE AÇÕES (DO MAIS RECENTE AO MAIS ANTIGO) \n");
    if (topo == NULL) {                                     // se não houve nenhuma ação ainda
        printf("Histórico vazio.\n");                 // informa na tela
        return;                                             // sai da função
    }
    NoPilha *atual = topo;                                  // começa pelo topo da pilha
    while (atual != NULL) {                                 // enquanto houver itens para baixo
        printf("- %s\n", atual->descricao);                 // imprime a descrição da ação
        atual = atual->prox;                                // desce para o próximo item da pilha
    }
}


// persistência de dados (arquivos txt)
// função auxiliar que percorre a árvore avl gravando cada cão no arquivo
void salvarAuxAVL(NoAVL *raiz, FILE *f) {
    if (raiz != NULL) {                                     // se o nó existe
        fprintf(f, "%d %s %s %d %d\n",
                raiz->id, raiz->nome, raiz->raca, raiz->idadeAnos, raiz->idadeMeses); // escreve os dados numa linha do arquivo
        salvarAuxAVL(raiz->esq, f);                         // faz o mesmo para os filhos da esquerda
        salvarAuxAVL(raiz->dir, f);                         // faz o mesmo para os filhos da direita
    }
}

// função auxiliar que percorre a árvore abb gravando cada item de estoque no arquivo
void salvarAuxABB(NoABB *raiz, FILE *f) {
    if (raiz != NULL) {                                     // se o nó existe
        fprintf(f, "%d %s %d\n", raiz->codigo, raiz->item, raiz->quantidade); // escreve código, nome e quantidade no arquivo
        salvarAuxABB(raiz->esq, f);                         // grava a subárvore esquerda
        salvarAuxABB(raiz->dir, f);                         // grava a subárvore direita
    }
}

// salva todos os cães e itens de estoque em arquivos de texto antes de fechar
void salvarDados(NoAVL *caes, NoABB *estoque) {
    FILE *fCaes = fopen("caes.txt", "w");                   // abre (ou cria) o arquivo caes.txt para escrita
    if (fCaes != NULL) {                                    // se conseguiu abrir o arquivo sem erro
        salvarAuxAVL(caes, fCaes);                          // chama a função que escreve todos os cães lá dentro
        fclose(fCaes);                                      // fecha o arquivo pra salvar de verdade no disco
    }

    FILE *fEstoque = fopen("estoque.txt", "w");             // abre (ou cria) o arquivo estoque.txt para escrita
    if (fEstoque != NULL) {                                 // se abriu tudo certo
        salvarAuxABB(estoque, fEstoque);                    // grava todos os itens da árvore abb de estoque
        fclose(fEstoque);                                   // fecha o arquivo
    }
    printf("Os dados foram salvos com sucesso em 'caes.txt' e 'estoque.txt'!\n"); // confirma para o usuário
}

// registra no final do arquivo .txt a data e hora exatas em que o usuário encerrou a interação no terminal
void registrarEncerramentoArquivos(void) {
    time_t agora = time(NULL);                              // obtém o horário atual do sistema
    struct tm *infoTempo = localtime(&agora);                 // converte para horário local
    char timestamp[64] = "indisponivel";                    // buffer para data e hora formatadas

    if (infoTempo != NULL) {                                // garante que a conversão foi bem sucedida
        strftime(timestamp, sizeof(timestamp), "%d/%m/%Y %H:%M:%S", infoTempo); // formata dd/mm/aaaa hh:mm:ss
    }

    FILE *fCaes = fopen("caes.txt", "a");                   // abre caes.txt em modo anexar ("a") para escrever no final
    if (fCaes != NULL) {                                    // se conseguiu abrir o arquivo
        fprintf(fCaes, "# Encerrado pelo cliente em: %s\n", timestamp); // escreve a data e hora exata no final
        fclose(fCaes);                                      // fecha o arquivo
    }

    FILE *fEstoque = fopen("estoque.txt", "a");             // abre o arquivo estoque.txt em modo anexar ("a") para escrever no final
    if (fEstoque != NULL) {                                 // se conseguiu abrir o arquivo
        fprintf(fEstoque, "# Encerrado pelo cliente em: %s\n", timestamp); // escreve a data e hora exata no final
        fclose(fEstoque);                                   // fecha o arquivo
    }
}

// lê os arquivos de texto quando abre o programa para recuperar os cadastros anteriores
void carregarDados(NoAVL **caes, NoABB **estoque) {
    FILE *fCaes = fopen("caes.txt", "r");                   // tenta abrir o arquivo de cães em modo leitura ("r")
    if (fCaes != NULL) {                                    // se o arquivo já existir no computador
        int id, anos, meses;
        char nome[50], raca[40];
        while (fscanf(fCaes, "%d %s %s %d %d", &id, nome, raca, &anos, &meses) == 5) { // lê linha por linha enquanto achar os 5 dados
            *caes = inserirAVL(*caes, id, nome, raca, anos, meses); // insere cada cão lido de volta na árvore avl
        }
        fclose(fCaes);                                      // fecha o arquivo após terminar a leitura
    }

    FILE *fEstoque = fopen("estoque.txt", "r");             // tenta abrir o arquivo de estoque para leitura
    if (fEstoque != NULL) {                                 // se o arquivo existir
        int codigo, qtd;                                    // variáveis para código e quantidade
        char item[50];                                      // variável para o nome do produto
        while (fscanf(fEstoque, "%d %s %d", &codigo, item, &qtd) == 3) { // lê cada linha do arquivo
            *estoque = inserirABB(*estoque, codigo, item, qtd); // coloca o produto de volta na árvore abb
        }
        fclose(fEstoque);                                   // fecha o arquivo de estoque
    }
}