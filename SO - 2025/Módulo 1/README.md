# README - Execução e Análise dos Scripts

Este módulo, como orietado contém os scripts desenvolvidos para a análise de processos CPU-bound e I/O-bound utilizando as ferramentas `strace` e `time`. A seguir, apresentamos um guia passo a passo para executar os programas e coletar as estatísticas necessárias.

## Requisitos

Antes de executar os scripts, verifique se as ferramentas `strace` e `time` estão instaladas em seu sistema Linux. Caso não estejam, instale-as com o seguinte comando:

```bash
sudo apt update && sudo apt install strace time
```

## Compilação dos Programas

Os programas devem ser compilados antes da execução. Para compilar os códigos-fonte, utilize o GCC e esteja dentro do repositório com os códigos ".c":

```bash
gcc -o modulo_1_exemplo_1 modulo_1_exemplo_1.c

gcc -o modulo_1_exemplo_2 modulo_1_exemplo_2.c

gcc -o modulo_1_exemplo_3 modulo_1_exemplo_3.c

gcc -o modulo_1_exemplo_4 modulo_1_exemplo_4.c

gcc -o modulo_1_exemplo_5 modulo_1_exemplo_5.c
```

## Execução com `strace`

A ferramenta `strace` será utilizada para capturar todas as chamadas de sistema executadas pelos programas. Execute os seguintes comandos para analisar cada programa:

```bash
strace ./modulo_1_exemplo_1

strace ./modulo_1_exemplo_2

strace ./modulo_1_exemplo_3

strace ./modulo_1_exemplo_4

strace ./modulo_1_exemplo_5
```

## Execução com `time`

Para medir o tempo de execução e outras estatísticas, utilize o seguinte comando:

```bash
time ./modulo_1_exemplo_1

time ./modulo_1_exemplo_2

time ./modulo_1_exemplo_3

time ./modulo_1_exemplo_4

time ./modulo_1_exemplo_5
```
