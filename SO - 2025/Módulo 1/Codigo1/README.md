# Relatório de Análise de Chamadas de Sistema e Desempenho

## Introdução

Este relatório apresenta a análise detalhada das chamadas de sistema e das métricas de desempenho do programa `modulo_1_exemplo_1`, desenvolvido a partir do código-fonte `modulo_1_exemplo_1.c`. Utilizando as ferramentas `strace` e `time`, foram obtidas estatísticas relacionadas ao uso de chamadas de sistema, tempos de execução e outras métricas relevantes.

## Descrição do Programa

O programa `modulo_1_exemplo_1` executa as seguintes operações:

1. **Criação e Escrita em Arquivo:**

   - Abre (ou cria, se inexistente) o arquivo `exemplo.txt` com permissões de escrita.
   - Escreve a string "Dados de exemplo\n" no arquivo.

2. **Criação de Processo Filho:**
   - Utiliza a chamada `fork` para criar um processo filho.
   - O processo pai aguarda a conclusão do filho utilizando `wait`.
   - O processo filho imprime uma mensagem e termina sua execução.

## Análise das Chamadas de Sistema

A ferramenta `strace` foi utilizada para monitorar as chamadas de sistema invocadas pelo programa. A opção `-T` foi empregada para exibir o tempo gasto em cada chamada. A seguir, descrevemos as principais chamadas identificadas:

1. **`execve`**: Inicia a execução do programa `modulo_1_exemplo_1`.
2. **`brk`**: Ajusta o limite superior do segmento de dados do processo.
3. **`mmap`**: Mapeia arquivos ou dispositivos na memória virtual do processo.
4. **`openat`**: Abre o arquivo especificado (`exemplo.txt`).
5. **`write`**: Escreve dados no descritor de arquivo.
6. **`fork`**: Cria um novo processo (filho).
7. **`getpid`**: Obtém o ID do processo atual.
8. **`wait4`**: Espera pela terminação de um processo filho.
9. **`close`**: Fecha o descritor de arquivo.
10. **`exit_group`**: Finaliza a execução do processo.

_Observação:_ Algumas chamadas de sistema, como `brk` e `mmap`, são utilizadas para gerenciamento de memória, enquanto `openat`, `write` e `close` estão relacionadas a operações de E/S em arquivos. As chamadas `fork` e `wait4` são empregadas no controle de processos.

## Métricas de Desempenho

A ferramenta `time` foi utilizada para obter as estatísticas de uso de recursos durante a execução do programa. As métricas coletadas foram:

- **Tempo Total de Execução (real):** 0m0.032s
- **Tempo em Modo Usuário (user):** 0m0.004s
- **Tempo em Modo Kernel (sys):** 0m0.018s
- **Trocas de Contexto Voluntárias:** 3
- **Trocas de Contexto Involuntárias:** 1

_Observação:_ O tempo total de execução foi de 32 milissegundos, com 4 milissegundos gastos em modo usuário e 18 milissegundos em modo kernel. As trocas de contexto voluntárias ocorrem quando um processo cede a CPU voluntariamente, enquanto as involuntárias acontecem quando o sistema operacional força a troca de contexto.

## Classificação: CPU-bound ou I/O-bound

Com base nas métricas obtidas, o programa `modulo_1_exemplo_1` pode ser classificado como **I/O-bound**. Isso se deve ao fato de que a maior parte do tempo de execução foi consumida em operações de E/S (modo kernel), como abertura e escrita em arquivos, além da criação e sincronização de processos. O tempo relativamente baixo em modo usuário indica que o programa não realiza intensivamente cálculos ou processamento de dados.

## Conclusão

O programa `modulo_1_exemplo_1` realiza operações básicas de E/S e manipulação de processos, com um comportamento predominantemente I/O-bound. As ferramentas `strace` e `time` foram fundamentais para identificar as chamadas de sistema utilizadas e avaliar o desempenho do programa. Essa análise permite compreender melhor a interação do programa com o sistema operacional e identificar possíveis áreas para otimização.

## Guia de Interpretação dos Outputs

Para interpretar os outputs gerados pelas ferramentas `strace` e `time`, considere:

- **`strace -T ./modulo_1_exemplo_1`**: Exibe todas as chamadas de sistema invocadas pelo programa `modulo_1_exemplo_1`, juntamente com o tempo gasto em cada uma. Útil para identificar quais operações consomem mais tempo.

- **`time ./modulo_1_exemplo_1`**: Fornece estatísticas sobre o tempo total de execução, tempo em modo usuário, tempo em modo kernel e outras métricas. Auxilia na determinação se o programa é CPU-bound ou I/O-bound.

Ao analisar os outputs, observe:

- **Chamadas de Sistema Frequentes ou Demoradas:** Identifique quais chamadas são mais frequentes ou consomem mais tempo, pois podem ser alvos para otimização.

- **Distribuição dos Tempos:** Compare os tempos em modo usuário e modo kernel para entender onde o programa passa a maior parte do tempo de execução.

- **Trocas de Contexto:** Um número elevado de trocas de contexto pode indicar ineficiências na gestão de processos ou threads.
