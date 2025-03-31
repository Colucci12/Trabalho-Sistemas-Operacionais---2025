#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // abrindo o arquivo /etc/os-release para leitura (infos do sistema)
    fd = open("/etc/os-release", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    // fazendo a leitura do arquivo
    printf("Lendo conteudo do arquivo...\n\n");
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Adiciona terminador nulo
        printf("%s", buffer);
    }

    // verificacao caso haja erros de leitura
    if (bytes_read == -1) {
        perror("Erro na leitura");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // close no arquivo e quit do programa
    close(fd);
    printf("\n\nLeitura concluída com sucesso!\n");
    return EXIT_SUCCESS;
}