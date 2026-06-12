#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

#define MAX_SYMBOLS 256

static int freq[MAX_SYMBOLS];
static char *codes[MAX_SYMBOLS];
static char code_buf[MAX_SYMBOLS];

static void build_codes(Node *node, int depth) {
    if (is_leaf(node)) {
        code_buf[depth] = '\0';
        codes[node->c] = strdup(code_buf);
        return;
    }
    code_buf[depth] = '0';
    build_codes(node->left, depth + 1);
    code_buf[depth] = '1';
    build_codes(node->right, depth + 1);
}

void compress(const char *input_filename) {
    /* 1. Contar frequências */
    memset(freq, 0, sizeof(freq));
    FILE *in = fopen(input_filename, "rb");
    if (!in) { perror("Erro ao abrir arquivo"); return; }

    int ch;
    while ((ch = fgetc(in)) != EOF)
        freq[ch]++;
    fclose(in);

    /* 2. Construir min-heap e árvore */
    MinHeap *heap = create_heap(MAX_SYMBOLS);
    for (int i = 0; i < MAX_SYMBOLS; i++)
        if (freq[i] > 0)
            heap_insert(heap, create_node((unsigned char)i, freq[i]));

    while (heap->size > 1) {
        Node *left  = heap_extract_min(heap);
        Node *right = heap_extract_min(heap);
        Node *parent = create_node(0, left->freq + right->freq);
        parent->left  = left;
        parent->right = right;
        heap_insert(heap, parent);
    }

    Node *root = heap_extract_min(heap);
    free_heap(heap);

    /* 3. Gerar tabela de códigos */
    memset(codes, 0, sizeof(codes));
    build_codes(root, 0);

    /* 4. Montar nome do arquivo de saída */
    char out_filename[512];
    strncpy(out_filename, input_filename, sizeof(out_filename) - 6);
    char *dot = strrchr(out_filename, '.');
    if (dot) *dot = '\0';
    strcat(out_filename, ".huff");

    /* 5. Escrever arquivo compactado */
    FILE *out = fopen(out_filename, "wb");
    if (!out) { perror("Erro ao criar arquivo"); return; }

    /* Serializa a árvore no cabeçalho */
    serialize_huffman_tree(root, out);

    /* Escreve os bits */
    in = fopen(input_filename, "rb");
    unsigned char byte = 0;
    int bit_count = 0;
    long bit_total = 0;

    /* Reserva espaço para o total de bits (preenchido depois) */
    long bits_pos = ftell(out);
    fwrite(&bit_total, sizeof(long), 1, out);

    while ((ch = fgetc(in)) != EOF) {
        char *code = codes[ch];
        for (int i = 0; code[i]; i++) {
            byte = (byte << 1) | (code[i] == '1');
            bit_count++;
            bit_total++;
            if (bit_count == 8) {
                fwrite(&byte, 1, 1, out);
                byte = 0;
                bit_count = 0;
            }
        }
    }
    /* Padding do último byte */
    if (bit_count > 0) {
        byte <<= (8 - bit_count);
        fwrite(&byte, 1, 1, out);
    }

    /* Volta e grava o total de bits */
    fseek(out, bits_pos, SEEK_SET);
    fwrite(&bit_total, sizeof(long), 1, out);

    fclose(in);
    fclose(out);
    free_tree(root);
    for (int i = 0; i < MAX_SYMBOLS; i++)
        if (codes[i]) free(codes[i]);

    printf("Compactado: %s\n", out_filename);
}