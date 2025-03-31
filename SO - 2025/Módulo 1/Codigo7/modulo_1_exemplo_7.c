#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

void print_file_info(const char* filename) {
    struct stat file_stat;
    
    // obter informações do arquivo usando stat()
    if (stat(filename, &file_stat) == -1) {
        perror("stat falhou");
        return;
    }

    // mostrar informacoes
    printf("\nInformações do arquivo: %s\n", filename);
    printf("--------------------------------\n");
    printf("Tipo e permissões:   %o\n", file_stat.st_mode & 07777);
    printf("Tamanho:             %ld bytes\n", (long)file_stat.st_size);
    printf("Número de links:     %ld\n", (long)file_stat.st_nlink);
    printf("Dono (UID):          %d\n", file_stat.st_uid);
    printf("Grupo (GID):         %d\n", file_stat.st_gid);
    
    // exibicao de timestamps
    printf("Último acesso:       %s", ctime(&file_stat.st_atime));
    printf("Última modificação:  %s", ctime(&file_stat.st_mtime));
    printf("Última alteração:    %s", ctime(&file_stat.st_ctime));
}

int main(int argc, char *argv[]) {
    print_file_info("/etc/os-release");

    return EXIT_SUCCESS;
}