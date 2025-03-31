# Relatório de Análise de Chamadas de Sistema e Desempenho

## Introdução

Este relatório apresenta a análise detalhada do programa `modulo_1_exemplo_5.c`, que demonstra a criação e sincronização de processos utilizando as chamadas de sistema `fork()`, `waitpid()` e `exit()`. O programa ilustra a comunicação entre processos pai e filho, incluindo a coleta do status de término do processo filho. A análise foi realizada utilizando as ferramentas `strace` e `time` para monitorar chamadas de sistema e métricas de desempenho.

## Descrição do Programa

O programa `modulo_1_exemplo_5` executa as seguintes operações:

1. **Criação de Processo Filho:**

   - Utiliza `fork()` para criar um novo processo.
   - Em caso de falha, imprime uma mensagem de erro e termina.

2. **Processo Filho:**
   - Imprime seu PID (Process ID).
   - Termina com status 42 usando `exit(42)`.

3. **Processo Pai:**
   - Aguarda o término do processo filho usando `waitpid()`.
   - Verifica o status de término do filho usando `WIFEXITED` e `WEXITSTATUS`.
   - Termina com status 0.

## Análise das Chamadas de Sistema

A ferramenta `strace` foi utilizada para monitorar as chamadas de sistema invocadas pelo programa. A opção `-T` foi empregada para exibir o tempo gasto em cada chamada. A seguir, descrevemos as principais chamadas identificadas:

1. **`clone`**: Equivalente moderno de `fork()`, usado para criar o processo filho.
2. **`getpid`**: Obtém o PID do processo atual.
3. **`wait4`**: Versão moderna de `waitpid()`, usada para aguardar o término do filho.
4. **`exit_group`**: Termina todos os threads do processo (equivalente a `exit()` para o programa principal).
5. **`write`**: Usada para imprimir mensagens na saída padrão.

_Observação:_ O programa não utiliza chamadas de sistema para operações de E/S em arquivos, focando exclusivamente no gerenciamento de memória. As chamadas `brk` são as mais relevantes, pois refletem as operações de alocação e liberação de memória no heap.

## Métricas de Desempenho

A ferramenta `time` foi utilizada para obter as estatísticas de uso de recursos durante a execução do programa. As métricas coletadas foram:

- **Tempo Total de Execução (real):** 0m0.003s
- **Tempo em Modo Usuário (user):** 0m0.001s
- **Tempo em Modo Kernel (sys):** 0m0.002s

_Observação:_ O tempo total de execução foi extremamente rápido (3 ms). A maior parte do tempo foi gasto em modo kernel (operações de criação e sincronização de processos). O programa não é intensivo em CPU, pois o tempo em modo usuário foi mínimo.

## Classificação: CPU-bound ou I/O-bound

Com base nas métricas, o programa pode ser classificado como CPU-bound leve, pois:
   - O tempo em modo kernel (sys) domina a execução, devido às operações de gerenciamento de processos.
   - Não há operações significativas de E/S, apenas impressões na saída padrão.

## Conclusão

O programa `modulo_1_exemplo_5.c` demonstra conceitos fundamentais de criação e sincronização de processos em sistemas Unix. Principais pontos:

   - Uso de `fork()` (implementado como `clone`) para criar processos.
   - Sincronização entre processos usando `waitpid()`.
   - Comunicação de status entre processos via valor de retorno de `exit()`.

A análise com `strace` e `time` mostrou que o programa é eficiente e rápido, com operações concentradas no gerenciamento de processos.

## Guia de Interpretação dos Outputs

Para interpretar os outputs gerados pelas ferramentas `strace` e `time`, considere:

- **`strace`**:
   - Foque nas chamadas `clone`, `wait4` e `exit_group` para entender o gerenciamento de processos.
   - As chamadas `write` correspondem às impressões na saída padrão.
   - O valor retornado por `wait4` mostra o status de término do filho.

- **`time `**:
   - O tempo em modo kernel (`sys`) reflete o custo das operações de criação e sincronização de processos.
   - O tempo total (`real`) é mínimo, indicando que o programa é leve.