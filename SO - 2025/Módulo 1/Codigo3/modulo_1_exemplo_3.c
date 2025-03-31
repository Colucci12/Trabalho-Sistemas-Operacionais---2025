#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

void print_memory_status(void *current_brk, void *initial_brk) {
    printf("--------------------------------\n");
    printf("endereco atual do break: %p\n", current_brk);
    printf("diferenca para o break inicial: %ld bytes\n", 
           (intptr_t)current_brk - (intptr_t)initial_brk);
}

int main() {
    void *initial_brk = sbrk(0);
    void *current_brk;
    int *num = NULL;

    printf("Break inicial: %p\n", initial_brk);

    // alocando 4096 bytes
    current_brk = (char *)initial_brk + 4096;
    if (brk(current_brk) == -1) {
        perror("brk falhou");
        return 1;
    }
    print_memory_status(sbrk(0), initial_brk);

    // usando a memória alocada (primeiros 4 bytes para um int)
    num = (int *)initial_brk;
    *num = 42;
    printf("Inteiro alocado: %d (endereco: %p)\n", *num, (void *)num);

    // alocando mais 8192 bytes
    current_brk = (char *)sbrk(0) + 8192;
    if (brk(current_brk) == -1) {
        perror("brk falhou");
        return 1;
    }
    print_memory_status(sbrk(0), initial_brk);

    // imprimindo valor antes de qualquer liberação
    printf("Valor do inteiro: %d\n", *num);

    // reduzindo o heap apenas até após o inteiro
    current_brk = (char *)initial_brk + sizeof(int);
    if (brk(current_brk) == -1) {
        perror("brk (reducao parcial) falhou");
        return 1;
    }

    printf("\nHeap reduzido\n");
    
    print_memory_status(sbrk(0), initial_brk);

    return 0;
}