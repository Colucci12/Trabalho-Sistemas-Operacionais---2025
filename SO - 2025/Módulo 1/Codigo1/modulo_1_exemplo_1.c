#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    pid_t pid;
    int fd;

    // Criar e abrir um arquivo para escrita
    fd = open("exemplo.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Escrever dados no arquivo
    if (write(fd, "Dados de exemplo\n", 17) == -1) {
        perror("Erro ao escrever no arquivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Criar um processo filho
    pid = fork();
    if (pid == -1) {
        perror("Erro ao criar o processo filho");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Código do processo filho
        printf("Processo filho (PID: %d)\n", getpid());
        // Fechar o arquivo no filho
        close(fd);
        exit(EXIT_SUCCESS);
    } else {
        // Código do processo pai
        printf("Processo pai (PID: %d), esperando o filho...\n", getpid());
        wait(NULL); // Espera o término do filho
        printf("Processo filho terminou.\n");
        // Fechar o arquivo no pai
        close(fd);
    }

    return 0;
}
