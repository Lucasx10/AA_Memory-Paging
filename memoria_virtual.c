#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    // Abrir o arquivo bible.txt
    int fd = open("bible.txt", O_RDONLY);
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

    // Obter o tamanho da página de memória
    size_t page_size = sysconf(_SC_PAGE_SIZE);

    // Alocar páginas de memória suficientes para o conteúdo do arquivo
    size_t num_pages = (file_size + page_size - 1) / page_size; // arredondar para cima
    char *memory = mmap(NULL, num_pages * page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (memory == MAP_FAILED) {
        perror("Erro ao alocar memória");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Ler o conteúdo do arquivo e escrever na memória alocada
    ssize_t bytes_read = read(fd, memory, file_size);
    if (bytes_read == -1) {
        perror("Erro ao ler o arquivo");
        munmap(memory, num_pages * page_size);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Imprimir o endereço de memória e o conteúdo (primeiros 1000 caracteres para evitar muito texto)
    printf("Endereço de memória virtual: %p\n", (void*)memory);
    printf("Conteúdo na memória (primeiros 1000 caracteres):\n%.1000s\n", memory);

    // Limpar
    munmap(memory, num_pages * page_size);
    close(fd);

    return 0;
}
