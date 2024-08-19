#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    // Abrir o arquivo bible.txt
    int fd = open("bible.txt", O_RDWR);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo bible.txt");
        exit(EXIT_FAILURE);
    }

    // Obter o tamanho do arquivo
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Erro ao obter informações do arquivo");
        close(fd);
        exit(EXIT_FAILURE);
    }
    size_t file_size = st.st_size;

    // Mapear o arquivo na memória
    char *memory = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (memory == MAP_FAILED) {
        perror("Erro ao mapear o arquivo na memória");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Exemplo: caso queira Escrever uma string no início da memória mapeada
    //const char *new_content = "Texto novo inserido na memória mapeada.\n";
    //memcpy(memory, new_content, strlen(new_content));

    // Imprimir o endereço de memória e o conteúdo (primeiros 1000 caracteres)
    printf("Endereço de memória virtual: %p\n", (void*)memory);
    printf("Conteúdo na memória (primeiros 1000 caracteres):\n%.1000s\n", memory);

    // Desmapear a memória e fechar o arquivo
    if (munmap(memory, file_size) == -1) {
        perror("Erro ao desmapear a memória");
    }
    close(fd);

    return 0;
}
