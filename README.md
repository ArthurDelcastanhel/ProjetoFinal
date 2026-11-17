# Sistema de Gestão para Canil

## Descrição do projeto
Sistema em linguagem C para gestão de abrigos de animais, controlando cadastros, filas de atendimento, estoque e histórico de ações.

## Instituição escolhida
* **Instituição:** Fictícia (Não obtive um retorno positivo (consentimento) da ONG desejada.)
* **Atuação:** Resgate, reabilitação e controle de cães abandonados e adoções.

## Justificativa
Necessidade de facilitar o atendimento veterinário e organizar o cadastro de animais para evitar perdas de registros.

## Fontes de pesquisas realizadas
* Artigo de Simone Nascimento destacando o excesso de animais abandonados nos abrigos para animais:
(https://www.rampasuerj.com.br/post/ongs-passam-por-sobrecarga-com-excesso-de-animais-abandonados)
* 

## Funcionalidades do sistema
* Cadastro, listagem e busca de cães.
* Fila de espera para atendimento veterinário.
* Histórico de ações com suporte a desfazer.
* Persistência simples de dados em arquivo texto.

## Estruturas de dados utilizadas

| Estrutura                   | Onde foi aplicada | Justificativa                                                                       |
|:----------------------------|:------------------|:------------------------------------------------------------------------------------|
| **Árvore AVL**              | Cadastro de Cães  | Garante buscas rápidas $O(\log n)$ e mantém o balanceamento automático.             |
| **Árvore De Busca Binária** | Estoque           | Organiza os itens ordenados por código de forma hierárquica.                        |
| **Fila Dinâmica**           | Atendimento       | Garante um atendimento por ordem FIFO (primeiro a entrar, primeiro a ser atendido). |
| **Pilha**                   | Histórico         | Garante a ordem LIFO para desfazer a última operação realizada.            |

## Como compilar e executar
No terminal:
```bash
gcc main.c canil.c -o sistema_canil
./sistema_canil
```

## Estrutura do Projeto

O código foi estrutura aplicando boas práticas de um projeto acadêmico, respeitando os escopos de responsabilidade:

```text
TrabalhoPRG/
├── CMakeLists.txt      # Arquivo de configuração para o sistema de compilação
├── README.md           # Documentação do projeto
└── src/
    ├── canil.c    # Implementação lógica das funções das estruturas de dados.
    ├── canil.h    # Arquivo cabelho para declarar as funções e structs do projeto.
    └── main.c                    # Menu de interação e interface do usuário (interação via terminal)
```

## Autoria
* Nome: Arthur Delcastanhel da Silva
* Curso e Instituição: Engenharia de Telecomunicações - IFSC
* Disciplina: Programação II