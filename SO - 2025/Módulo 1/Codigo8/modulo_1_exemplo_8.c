#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    // criacao de novo processo utilizando fork
    pid_t pid = fork();
    
    if (pid == 0) {
        printf("Processo filho vai executar 'ls -l'\n");
        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec falhou");
        return 1;
    } else {
        wait(NULL);
        printf("Processo filho terminou\n");
    }
    
    return 0;
}