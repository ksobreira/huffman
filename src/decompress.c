#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void decompress(const char *input_filename) {
    FILE *in = fopen(input_filename, "rb");
    if (!in) { perror("Erro ao abrir arquivo"); return; }

    /* 1. Deserializa a árvore do cabeçalho */
    Node *root = deserialize_huffman_tree(in);

    /* 2. Lê o total de bits */
    long bit_total = 0;
    fread(&bit_total, sizeof(long), 1, in);

    /* 3. Monta nome do arquivo de saída */
    char out_filename[512];
    snprintf(out_filename, sizeof(out_filename), "descompactado_%s", input_filename);
    char *dot = strrchr(out_filename, '.');
    if (dot) strcpy(dot, ".txt");

    FILE *out = fopen(out_filename, "wb");
    if (!out) { perror("Erro ao criar arquivo"); return; }

    /* 4. Decodifica os bits percorrendo a árvore */
    Node *current = root;
    long bits_read = 0;
    int ch;

    while ((ch = fgetc(in)) != EOF) {
        for (int i = 7; i >= 0 && bits_read < bit_total; i--) {
            int bit = (ch >> i) & 1;
            bits_read++;
            current = bit ? current->right : current->left;

            if (is_leaf(current)) {
                fputc(current->c, out);
                current = root;
            }
        }
    }

    fclose(in);
    fclose(out);
    free_tree(root);

    printf("Descompactado: %s\n", out_filename);
}