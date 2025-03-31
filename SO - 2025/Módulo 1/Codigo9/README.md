# Relatório de Análise de Chamadas de Sistema e Desempenho

## Introdução
Este relatório apresenta a análise detalhada das chamadas de sistema e das métricas de desempenho do programa `modulo_1_exemplo_9`, desenvolvido a partir do código-fonte `modulo_1_exemplo_9.c`. Utilizando as ferramentas `strace` e `time`, foram obtidas estatísticas relacionadas ao uso de chamadas de sistema, tempos de execução e outras métricas relevantes.

## Descrição do Programa
O programa `modulo_1_exemplo_9` executa as seguintes operações:

### Comunicação entre Processos via Pipe:
- Cria um pipe para comunicação entre processos.
- Um processo filho é criado utilizando `fork`.
- O processo filho escreve a mensagem "Hello pipe!" no pipe.
- O processo pai lê a mensagem enviada pelo filho e a exibe na saída padrão.

## Análise das Chamadas de Sistema
A ferramenta `strace` foi utilizada para monitorar as chamadas de sistema invocadas pelo programa. A seguir, descrevemos as principais chamadas identificadas:

- **execve**: Inicia a execução do programa `modulo_1_exemplo_9`.
- **brk**: Ajusta o limite superior do segmento de dados do processo.
- **mmap**: Mapeia arquivos ou dispositivos na memória virtual do processo.
- **openat**: Abre arquivos necessários para execução do programa.
- **pipe2**: Cria um canal de comunicação entre processos (pipe).
- **fork**: Cria um novo processo (filho).
- **write**: O processo filho escreve dados no pipe.
- **read**: O processo pai lê os dados enviados pelo filho através do pipe.
- **exit_group**: Finaliza a execução do processo.

Observação: As chamadas `pipe2`, `fork`, `write` e `read` são essenciais para a comunicação entre processos via pipe.

## Métricas de Desempenho
A ferramenta `time` foi utilizada para obter as estatísticas de uso de recursos durante a execução do programa. As métricas coletadas foram:

- **Tempo Total de Execução (real)**: 0m0,001s
- **Tempo em Modo Usuário (user)**: 0m0,000s
- **Tempo em Modo Kernel (sys)**: 0m0,001s

Observação: O tempo total de execução foi de apenas 1 milissegundo, com todo o tempo sendo gasto em modo kernel, indicando que a maior parte do processamento envolveu chamadas de sistema, como a manipulação do pipe.

## Classificação: CPU-bound ou I/O-bound
Com base nas métricas obtidas, o programa `modulo_1_exemplo_9` pode ser classificado como **I/O-bound**. Isso ocorre porque a principal operação do programa envolve a comunicação via pipe, que é uma operação de entrada e saída entre processos.

## Conclusão
O programa `modulo_1_exemplo_9` demonstra o uso de pipes para comunicação entre processos, onde um processo filho envia uma mensagem e o processo pai a recebe. O uso das ferramentas `strace` e `time` permitiu identificar as chamadas de sistema envolvidas e avaliar o desempenho do programa. Essa análise auxilia na compreensão da interação entre processos e o sistema operacional.

## Guia de Interpretação dos Outputs
Para interpretar os outputs gerados pelas ferramentas `strace` e `time`, considere:

- **`strace`**: Exibe todas as chamadas de sistema invocadas pelo programa `modulo_1_exemplo_9`, juntamente com o tempo gasto em cada uma. Útil para identificar quais operações consomem mais tempo.
- **`time`**: Fornece estatísticas sobre o tempo total de execução, tempo em modo usuário, tempo em modo kernel e outras métricas. Auxilia na determinação se o programa é CPU-bound ou I/O-bound.

Ao analisar os outputs, observe:

- **Chamadas de Sistema Frequentes ou Demoradas**: Identifique quais chamadas são mais frequentes ou consomem mais tempo, pois podem ser alvos para otimização.
- **Distribuição dos Tempos**: Compare os tempos em modo usuário e modo kernel para entender onde o programa passa a maior parte do tempo de execução.
- **Uso de Pipes**: Como o programa envolve comunicação entre processos, a análise do tempo gasto em `write` e `read` pode indicar possíveis otimizações para melhorar o desempenho.

