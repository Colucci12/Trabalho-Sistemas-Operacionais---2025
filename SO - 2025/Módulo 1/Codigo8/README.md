# Relatório de Análise de Chamadas de Sistema e Desempenho

## Introdução
Este relatório apresenta a análise detalhada das chamadas de sistema e das métricas de desempenho do programa `modulo_1_exemplo_8`, desenvolvido a partir do código-fonte `modulo_1_exemplo_8.c`. Utilizando as ferramentas `strace` e `time`, foram obtidas estatísticas relacionadas ao uso de chamadas de sistema, tempos de execução e outras métricas relevantes.

## Descrição do Programa
O programa `modulo_1_exemplo_8` executa as seguintes operações:

### Criação de Processo Filho:
- Utiliza a chamada `fork` para criar um processo filho.
- O processo filho executa o comando `ls -l` através da chamada `execl`.
- O processo pai aguarda a conclusão do filho utilizando `wait`.

## Análise das Chamadas de Sistema
A ferramenta `strace` foi utilizada para monitorar as chamadas de sistema invocadas pelo programa. A opção `-T` foi empregada para exibir o tempo gasto em cada chamada. A seguir, descrevemos as principais chamadas identificadas:

- **execve**: Inicia a execução do programa `modulo_1_exemplo_8`.
- **brk**: Ajusta o limite superior do segmento de dados do processo.
- **mmap**: Mapeia arquivos ou dispositivos na memória virtual do processo.
- **openat**: Abre arquivos necessários para execução do programa.
- **fork**: Cria um novo processo (filho).
- **wait4**: Aguarda a terminação do processo filho.
- **execl**: Substitui o processo filho pelo comando `ls -l`.
- **exit_group**: Finaliza a execução do processo.

Observação: Algumas chamadas de sistema, como `brk` e `mmap`, são utilizadas para gerenciamento de memória, enquanto `fork`, `wait4` e `execl` são empregadas no controle de processos.

## Métricas de Desempenho
A ferramenta `time` foi utilizada para obter as estatísticas de uso de recursos durante a execução do programa. As métricas coletadas foram:

- **Tempo Total de Execução (real)**: 0m0,003s
- **Tempo em Modo Usuário (user)**: 0m0,001s
- **Tempo em Modo Kernel (sys)**: 0m0,002s

Observação: O tempo total de execução foi de apenas 3 milissegundos, com 1 milissegundo gasto em modo usuário e 2 milissegundos em modo kernel. O tempo reduzido se deve à natureza simples do programa, que apenas cria um processo filho e executa um comando externo.

## Classificação: CPU-bound ou I/O-bound
Com base nas métricas obtidas, o programa `modulo_1_exemplo_8` pode ser classificado como **I/O-bound**. Isso se deve ao fato de que a maior parte do tempo de execução foi consumida na chamada `execl`, que envolve operações de entrada e saída ao carregar e executar o comando `ls -l`.

## Conclusão
O programa `modulo_1_exemplo_8` realiza operações básicas de manipulação de processos, executando um comando externo por meio da chamada `execl`. O uso das ferramentas `strace` e `time` permitiu identificar as chamadas de sistema envolvidas e avaliar o desempenho do programa. Essa análise auxilia na compreensão da interação entre o programa e o sistema operacional.

## Guia de Interpretação dos Outputs
Para interpretar os outputs gerados pelas ferramentas `strace` e `time`, considere:

- **`strace`**: Exibe todas as chamadas de sistema invocadas pelo programa `modulo_1_exemplo_8`, juntamente com o tempo gasto em cada uma. Útil para identificar quais operações consomem mais tempo.
- **`time`**: Fornece estatísticas sobre o tempo total de execução, tempo em modo usuário, tempo em modo kernel e outras métricas. Auxilia na determinação se o programa é CPU-bound ou I/O-bound.

Ao analisar os outputs, observe:

- **Chamadas de Sistema Frequentes ou Demoradas**: Identifique quais chamadas são mais frequentes ou consomem mais tempo, pois podem ser alvos para otimização.
- **Distribuição dos Tempos**: Compare os tempos em modo usuário e modo kernel para entender onde o programa passa a maior parte do tempo de execução.
- **Trocas de Contexto**: Um número elevado de trocas de contexto pode indicar ineficiências na gestão de processos ou threads.