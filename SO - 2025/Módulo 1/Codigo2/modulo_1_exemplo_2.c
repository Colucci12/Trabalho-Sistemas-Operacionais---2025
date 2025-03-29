#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main() {
    pid_t pid;
    char *mem;

    // Alocar memória compartilhada
    mem = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("Erro ao mapear memória");
        exit(EXIT_FAILURE);
    }

    // Criar um processo filho
    pid = fork();
    if (pid == -1) {
        perror("Erro ao criar o processo filho");
        munmap(mem, 4096);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Código do processo filho
        printf("Processo filho (PID: %d)\n", getpid());
        // Escrever na memória compartilhada
        snprintf(mem, 4096, "Mensagem do filho");
        munmap(mem, 4096);
        exit(EXIT_SUCCESS);
    } else {
        // Código do processo pai
        printf("Processo pai (PID: %d), esperando o filho...\n", getpid());
        wait(NULL); // Espera o término do filho
        // Ler da memória compartilhada
        printf("Conteúdo da memória compartilhada: %s\n", mem);
        munmap(mem, 4096);
    }

    return 0;
}
