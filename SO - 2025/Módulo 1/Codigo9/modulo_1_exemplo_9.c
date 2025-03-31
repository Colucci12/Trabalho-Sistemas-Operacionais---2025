#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buf[20];
    
    if (pipe(fd) == -1) {
        perror("pipe falhou");
        return 1;
    }
    
    if (fork() == 0) {
        // fechamento de leitura no filho
        close(fd[0]);
        write(fd[1], "Hello pipe!", 12);
        close(fd[1]);
    } else {
        // fechamento de escrita no pai
        close(fd[1]);
        read(fd[0], buf, sizeof(buf));
        printf("Mensagem recebida: %s\n", buf);
        close(fd[0]);
    }
    
    return 0;
}