#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;

void signal_handler(int sig) {
    if (sig == SIGSEGV) {
        printf("erro: tentativa de escrita em memória protegida detectada!\n");
        longjmp(env, 1);
    }
}

int main() {
    const size_t size = 4096;
    char *mem;

    // manipulador de sinal para capturar falhas de segmentação (segmentation fault)
    signal(SIGSEGV, signal_handler);

    // alocando a memória com mmap
    mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap falhou");
        return EXIT_FAILURE;
    }

    printf("memória alocada em: %p\n", mem);

    // escrevendo na memória
    sprintf(mem, "dados iniciais");
    printf("conteúdo inicial: %s\n", mem);

    // removendo a permissão de escrita
    if (mprotect(mem, size, PROT_READ) == -1) {
        perror("mprotect (PROT_READ) falhou");
        munmap(mem, size);
        return EXIT_FAILURE;
    }
    printf("permissões alteradas: SOMENTE LEITURA\n");

    // tentando escrever na memória protegida
    if (setjmp(env) == 0) {
        printf("tentando escrever na memória protegida...\n");
        sprintf(mem, "Tentativa de escrita");
    } else {
        printf("execução continuada após falha de segmentação.\n");
    }

    // retaurando as permissoes
    if (mprotect(mem, size, PROT_READ | PROT_WRITE) == -1) {
        perror("mprotect (PROT_READ | PROT_WRITE) falhou");
        munmap(mem, size);
        return EXIT_FAILURE;
    }

    // escrevendo uma ultima vez na memoria
    sprintf(mem, "dados finais");
    printf("conteúdo final: %s\n", mem);

    // limpando e quitando
    munmap(mem, size);
    return EXIT_SUCCESS;
}
