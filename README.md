# Manipulação de Memória Virtual em C

Este projeto demonstra como ler o conteúdo de um arquivo (`bible.txt`) e carregá-lo em uma página de memória virtual usando a linguagem C. O código inclui a alocação de memória virtual, leitura de arquivo e manipulação da memória.

## Pré-requisitos

Antes de executar o código, certifique-se de ter o seguinte:

- **Compilador GCC**: Necessário para compilar o código C.
- **Arquivo `bible.txt`**: O arquivo de texto `bible.txt` deve estar presente no mesmo diretório onde o código será executado.
- **Ambiente Unix/Linux**: O código foi projetado para sistemas operacionais baseados em Unix, como Linux ou macOS.

## Passos para Compilação e Execução

### Compile o Código

Abra um terminal e navegue até o diretório onde o arquivo memoria_virtual.c foi salvo. Compile o código usando o GCC:

    gcc -o memoria_virtual memoria_virtual.c

Isso gerará um executável chamado memoria_virtual.

### Execute o Programa

Após a compilação, execute o programa gerado:

    ./memoria_virtual


Se tudo estiver correto, o programa imprimirá o endereço de memória virtual onde o conteúdo do arquivo foi carregado, seguido pelos primeiros 1000 caracteres do conteúdo do arquivo bible.txt.

### Explicação do Código

O código pode ser dividido em várias etapas principais:

1. Abertura do Arquivo bible.txt

    O arquivo é aberto para leitura usando a função open. O descritor de arquivo (fd) é utilizado para operações subsequentes.

2. Obtenção do Tamanho do Arquivo

    A função fstat é utilizada para obter informações sobre o arquivo, incluindo seu tamanho (st.st_size).

3. Obtenção do Tamanho da Página de Memória

    O tamanho da página de memória do sistema é obtido através da função sysconf(_SC_PAGE_SIZE).

4. Alocação de Memória Virtual

    A função mmap é utilizada para alocar uma região de memória virtual que pode conter todo o conteúdo do arquivo.

5. Leitura do Arquivo para a Memória

    O conteúdo do arquivo bible.txt é lido e copiado diretamente para a memória virtual alocada.

6. Impressão do Conteúdo da Memória

    O código imprime o endereço da memória virtual e os primeiros 1000 caracteres do conteúdo do arquivo que foi carregado.

7. Liberação da Memória e Fechamento do Arquivo

    Após o uso, a memória alocada é liberada com munmap e o arquivo é fechado com close.

### Conclusão

Este código demonstra como carregar o conteúdo de um arquivo em uma página de memória virtual, uma técnica avançada de manipulação de memória em C. Seguindo as instruções acima, você pode executar o código e entender como ele funciona, além de adaptá-lo para outras necessidades.