# Relatório de Análise de Chamadas de Sistema e Desempenho

## Introdução

Este relatório apresenta a análise detalhada do programa `modulo_1_exemplo_3.c`, que demonstra o uso das chamadas de sistema `brk` e `sbrk` para gerenciamento manual de memória no heap. O relatório inclui uma descrição do programa, análise das chamadas de sistema, métricas de desempenho e classificação do comportamento do programa.

## Descrição do Programa

O programa `modulo_1_exemplo_3` executa as seguintes operações:

1. **Inicialização do Heap:**

   - Obtém o endereço inicial do break (`initial_brk`) usando `sbrk(0)`.

2. **Alocação de Memória:**
   - Aloca 4096 bytes no heap ajustando o break para `initial_brk + 4096`.
   - Utiliza os primeiros 4 bytes do espaço alocado para armazenar um inteiro (`42`).

3. **Expansão do Heap:**
   - Aloca mais 8192 bytes, aumentando o break para `current_brk + 8192`.

4. **Redução do Heap:**
   - Reduz o heap para liberar a maior parte da memória alocada, mantendo apenas os 4 bytes usados para o inteiro.

5. **Monitoramento:**
   - Imprime o status da memória após cada operação, mostrando o endereço atual do break e a diferença em bytes em relação ao break inicial.

## Análise das Chamadas de Sistema

A ferramenta `strace` foi utilizada para monitorar as chamadas de sistema invocadas pelo programa. A opção `-T` foi empregada para exibir o tempo gasto em cada chamada. A seguir, descrevemos as principais chamadas identificadas:

1. **`brk`**: Utilizada para ajustar o limite superior do segmento de dados (heap) do processo. O programa chama `brk` para alocar e liberar memória.
2. **`write`**: Usada para imprimir mensagens na saída padrão.
3. **`execve`**: Inicia a execução do programa.
4. **`mmap`**: Mapeia regiões de memória para uso pelo programa (gerenciamento interno da biblioteca C).
5. **`exit_group`**: Finaliza a execução do programa.

_Observação:_ O programa não utiliza chamadas de sistema para operações de E/S em arquivos, focando exclusivamente no gerenciamento de memória. As chamadas `brk` são as mais relevantes, pois refletem as operações de alocação e liberação de memória no heap.

## Métricas de Desempenho

A ferramenta `time` foi utilizada para obter as estatísticas de uso de recursos durante a execução do programa. As métricas coletadas foram:

- **Tempo Total de Execução (real):** 0m0.004s
- **Tempo em Modo Usuário (user):** 0m0.000s
- **Tempo em Modo Kernel (sys):** 0m0.004s

_Observação:_ O tempo total de execução foi extremamente rápido (4 milissegundos), com a maior parte do tempo gasto em modo kernel (operações de gerenciamento de memória). O tempo em modo usuário foi insignificante, indicando que o programa não realiza processamento intensivo.

## Classificação: CPU-bound ou I/O-bound

Com base nas métricas obtidas, o programa `modulo_1_exemplo_3.c` pode ser classificado como CPU-bound, pois o tempo de execução é dominado por operações de gerenciamento de memória (modo kernel), sem envolvimento significativo de E/S. No entanto, o programa é extremamente leve e não sobrecarrega a CPU.

## Conclusão

O programa `modulo_1_exemplo_3.c` demonstra o uso básico das chamadas `brk` e `sbrk` para gerenciamento manual de memória no heap. A análise com `strace` e `time` mostrou que o programa é eficiente e rápido, com operações concentradas no gerenciamento de memória. Essa abordagem é útil para entender os mecanismos de baixo nível de alocação de memória em sistemas Unix.

## Guia de Interpretação dos Outputs

Para interpretar os outputs gerados pelas ferramentas `strace` e `time`, considere:

- **`strace`**:
   - Foque nas chamadas `brk` para entender como o programa ajusta o heap.
   - As chamadas `write` correspondem às impressões na saída padrão.
   - Ignore chamadas relacionadas ao carregamento de bibliotecas (como `mmap`), pois são gerenciadas internamente pelo sistema.

- **`time `**:
   - O tempo em modo kernel (`sys`) reflete o custo das operações de gerenciamento de memória.
   - O tempo total (`real`) é mínimo, indicando que o programa é leve e rápido.