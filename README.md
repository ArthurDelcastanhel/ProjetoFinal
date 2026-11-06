# Sistema de Gestão para Abrigo de Adoção de Animais (ONG)

Repositório dedicado ao Projeto Final do semestre 2026/2 na disciplina de **Programação II (Estruturas de Dados)** do curso de **Engenharia de Telecomunicações** no **Instituto Federal de Santa Catarina (IFSC)**.

---

## 1. Descrição do Projeto
Sistema em linguagem **C (padrão C23)** desenvolvido para organizar e gerenciar as atividades operacionais de uma ONG / Abrigo de proteção e adoção de animais, aplicando estruturas de dados dinâmicas implementadas manualmente (Árvore AVL, Árvore Binária de Pesquisa, Fila, Pilha e Lista Duplamente Encadeada) com persistência em arquivos.

## 2. A Instituição Escolhida
- **Modalidade:** Instituição idealizada (Opção B) baseada no funcionamento de abrigos de proteção animal e projetos de adoção comunitária.
- **Atuação:** Resgate, acolhimento temporário, acompanhamento veterinário (vacinação e castração), triagem de interessados e encaminhamento responsável para adoção de cães e gatos.

## 3. Justificativa
Abrigos de animais frequentemente enfrentam gargalos na organização de cadastros quando operam com planilhas manuais ou anotações dispersas: perda de histórico de vacinação, dificuldade em localizar rapidamente o registro de um animal pelo código de identificação e falta de controle na ordem de chegada dos candidatos à adoção. Este sistema soluciona esses problemas associando cada demanda operacional à estrutura de dados mais adequada.

## 4. Fontes e Pesquisa
- Conceitos de modelagem de dados, alocação dinâmica de memória e ponteiros estudados nas disciplinas de Programação I e Programação II (IFSC).
- Levantamento de fluxos operacionais típicos de ONGs de proteção animal (triagem, fila de espera para adoção, prontuário veterinário e controle de animais disponíveis/adotados).

## 5. Funcionalidades Previstas
- [ ] **Gestão de Animais (CRUD):** Cadastro, busca rápida por ID, atualização de status/vacinas e remoção.
- [ ] **Gestão de Adotantes (CRUD):** Cadastro, busca e listagem em ordem alfabética.
- [ ] **Fila de Adoção:** Enfileiramento de solicitações e atendimento por ordem de chegada (FIFO).
- [ ] **Prontuário Veterinário:** Registro e navegação bidirecional (anterior/próximo) nos procedimentos e vacinas.
- [ ] **Histórico de Operações:** Consulta às últimas ações realizadas no sistema (LIFO).
- [ ] **Relatórios e Persistência:** Listagens ordenadas, estatísticas do abrigo e salvamento automático em arquivos CSV/TXT.

## 6. Estruturas de Dados Utilizadas

| Estrutura de Dados | Aplicação no Sistema | Justificativa da Escolha |
| :--- | :--- | :--- |
| **Árvore AVL** | Cadastro e busca de **Animais** por código (`id`) | Como os IDs dos animais tendem a ser inseridos em ordem crescente (`1, 2, 3...`), uma árvore comum degeneraria em lista linear $O(n)$. A AVL mantém o fator de balanceamento entre `-1` e `+1` via rotações, garantindo busca em $O(\log n)$. |
| **Árvore Binária de Pesquisa (ABP)** | Cadastro de **Adotantes** indexado pelo `nome` | Permite busca eficiente por nome e gera automaticamente a listagem em ordem alfabética através do percurso *em-ordem* (*in-order*). |
| **Fila Dinâmica (FIFO)** | **Fila de espera** para adoção e triagem | Garante justiça no atendimento das solicitações: o primeiro interessado a se inscrever é o primeiro a ser chamado (*First-In, First-Out*). |
| **Lista Duplamente Encadeada** | **Prontuário de vacinas e atendimentos** | Possibilita navegar tanto para o registro mais recente quanto retroceder para registros anteriores (`*anterior` e `*proximo`). |
| **Pilha Dinâmica (LIFO)** | **Histórico de operações** da sessão | Mantém no topo a ação mais recente executada pelo operador (*Last-In, First-Out*), facilitando auditoria rápida e reversão. |

## 7. Como Compilar e Executar
O projeto utiliza **CMake** com o padrão **C23**:

```bash
mkdir build
cd build
cmake ..
cmake --build .
./ProjetoFinal
```
*(Também pode ser aberto e executado diretamente no **CLion** como projeto `C Executable - C23`).*

## 8. Organização do Repositório
```text
ProjetoFinal/
├── CMakeLists.txt          # Configuração de build CMake (C23)
├── README.md               # Documentação do projeto
├── data/                   # Arquivos de persistência (.csv / .txt)
├── include/
│   ├── modelos.h           # Definição das structs das entidades (Animal, Adotante, etc.)
│   └── estruturas.h        # Definição dos nós das estruturas (AVL, ABP, Fila, Pilha, Lista Dupla)
└── src/
    └── main.c              # Ponto de entrada e menu principal
```

## 9. Dificuldades Encontradas e Aprendizado
*(Seção atualizada gradualmente ao longo do desenvolvimento dos módulos).*

## 10. Declaração de Uso de IA
Estruturação da organização inicial de diretórios, revisão de formatação do `README.md` e padronização do `CMakeLists.txt` com auxílio de assistente de IA.

## 11. Autoria
- **Aluno:** Arthur Delcastanhel da Silva
- **Curso:** Engenharia de Telecomunicações — IFSC
- **Disciplina:** Programação II (2026/2)
