#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_process() {
    printf("Processo filho (PID: %d) iniciado\n", getpid());
    
    printf("Filho: encerrando...\n");
    
    printf("Filho: terminando com status 42\n");
    // chamada de sistema exit() com status 42
    exit(42);
}

void parent_process(pid_t pid) {
    printf("Processo pai (PID: %d) aguardando filho (PID: %d)...\n", getpid(), pid);
    
    int status;
    // espera pelo filho
    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status)) {
        printf("Pai: filho terminou com status %d\n", WEXITSTATUS(status));
    } else {
        printf("Pai: filho terminou anormalmente\n");
    }
    
    printf("Pai: terminando com status 0\n");
    // chamada de sistema exit() com status 0
    exit(0);
}

int main() {    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork falhou");
        return EXIT_FAILURE;
    }
    
    if (pid == 0) {
        child_process();
    } else {
        parent_process(pid);
    }
    
    // nunca vai chegar nessa parte do codigo, pois é feita a chamada exit()
    printf("Esta mensagem nunca aparecerá\n");
    return 0;
}