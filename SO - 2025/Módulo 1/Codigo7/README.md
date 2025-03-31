# Relatório de Análise de Chamadas de Sistema e Desempenho

## Introdução

Este relatório apresenta a análise detalhada do programa `modulo_1_exemplo_7.c`, que demonstra como obter e exibir informações detalhadas sobre um arquivo utilizando chamadas de sistema. O programa foca especificamente na análise do arquivo `/etc/os-release`, mostrando metadados como permissões, tamanho, timestamps e propriedade. A análise foi realizada utilizando as ferramentas `strace` e `time` para monitorar chamadas de sistema e métricas de desempenho.

## Descrição do Programa

O programa `modulo_1_exemplo_7` executa as seguintes operações:

1. **Obtenção de Metadados**
   - Utiliza a função `stat()` para coletar informações sobre o arquivo `/etc/os-release`.
   - Armazena os dados em uma estrutura `struct stat`.

2. **Exibindo de Informações**
   - Mostra detalhes do arquivo incluindo:
       - Tipo e permissões (em formato octal)
       - Tamanho em bytes
       - Número de links físicos
       - UID (Dono) e GID (Grupo)
       - Três timestamps importantes:
          - Último acesso (`st_atime`)
          - Última modificação de conteúdo (`st_mtime`)
          - Última alteração de metadados (`st_ctime`)

3. **Tratamento de Erros:**
   - Verifica erros na chamada `stat()` e exibe mensagens apropriadas usando `perror()`.

## Análise das Chamadas de Sistema

A ferramenta `strace` foi utilizada para monitorar as chamadas de sistema invocadas pelo programa. A opção `-T` foi empregada para exibir o tempo gasto em cada chamada. A seguir, descrevemos as principais chamadas identificadas:

1. **`newfstatat`**: Versão moderna de `stat()`, usada para obter informações do arquivo.
2. **`openat`**: Abre `/etc/localtime` para interpretar os timestamps.
3. **`write`**: Exibe os resultados na saída padrão.
4. **`fstat`**: Obtém informações sobre descritores de arquivo abertos.

## Métricas de Desempenho

A ferramenta `time` foi utilizada para obter as estatísticas de uso de recursos durante a execução do programa. As métricas coletadas foram:

- **Tempo Total de Execução (real):** 0m0.003s
- **Tempo em Modo Usuário (user):** 0m0.000s
- **Tempo em Modo Kernel (sys):** 0m0.003s

_Observação:_ O tempo total de execução foi extremamente rápido (3ms). Todo o tempo foi gasto em modo kernel (operações com arquivos e sistema). O tempo em modo usuário foi insignificante.

## Classificação: CPU-bound ou I/O-bound

Com base nas métricas, o programa pode ser classificado como I/O-bound, pois:
   - O tempo de execução é dominado por operações de acesso a arquivos
   - Não há processamento intensivo de dados
   - As chamadas de sistema relacionadas a arquivos (`newfstatat`, `openat`) são as mais demoradas

## Conclusão

O programa `modulo_1_exemplo_7.c` demonstra eficientemente:
   - Como obter e interpretar metadados de arquivos usando `stat()`
   - A formatação e exibição de informações do sistema de arquivos
   - O tratamento básico de erros em operações com arquivos

A análise mostrou que o programa é extremamente eficiente, com todo o tempo de execução dedicado a operações necessárias de I/O.

## Guia de Interpretação dos Outputs

Para interpretar os outputs gerados pelas ferramentas `strace` e `time`, considere:

- **`strace`**:
   - Foque em `newfstatat` para entender a coleta de metadados
   - As chamadas relacionadas a `/etc/localtime` são usadas para formatar timestamps
   - As sequências de `write` mostram a saída formatada do programa

- **`time `**:
   - O tempo em `sys` reflete as operações com arquivos
   - O tempo quase zero em `user` indica ausência de processamento intensivo