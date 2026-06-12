#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso:\n");
        printf("  huffman --compactar arquivo.txt\n");
        printf("  huffman --descompactar arquivo.huff\n");
        return 1;
    }

    if (strcmp(argv[1], "--compactar") == 0) {
        compress(argv[2]);
    } else if (strcmp(argv[1], "--descompactar") == 0) {
        decompress(argv[2]);
    } else {
        printf("Opcao invalida: %s\n", argv[1]);
        return 1;
    }

    return 0;
}