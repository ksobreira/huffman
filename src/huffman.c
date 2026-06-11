#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"

Node* create_node(unsigned char c, int freq)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if( new_node == NULL)
    {
        perror("Erro ao alocar meória para o nó");
        return NULL;
    }

    new_node->c = c;
    new_node->freq = freq;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

bool is_leaf(Node *node)
{
    return (node->left == NULL && node->right == NULL);
}

void serialize_huffman_tree(Node *node, FILE *file)
{
    if(node == NULL)
    {
        return;
    }

    if(is_leaf(node))
    {
        unsigned char leaf_node_mark = 1;
        fwrite(&leaf_node_mark, sizeof(unsigned char), 1, file);
        fwrite(&(node->c), sizeof(unsigned char), 1, file);
    }
    else
    {
        unsigned char leaf_node_mark = 0;
        fwrite(&leaf_node_mark, sizeof(unsigned char), 1, file);
        serialize_huffman_tree(node->left, file);
        serialize_huffman_tree(node->right, file);
    }

}

Node* deserialize_huffman_tree(FILE *file)
{
    unsigned char mark;
    fread(&mark, sizeof(unsigned char), 1, file);

    if(mark == 1)
    {
        unsigned char read_char;
        fread(&read_char, sizeof(unsigned char), 1, file);

        Node *new_node = create_node(read_char, 0);
        return new_node;
    }
    else 
    {
        Node *new_node = create_node(0, 0);
        new_node->left = deserialize_huffman_tree(file);
        new_node->right = deserialize_huffman_tree(file);
        return new_node;
    }
}

void free_tree(Node *node)
{
    if(node == NULL)
    {
        return;
    }

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void print_huffman_tree(Node *node)
{
    if(node == NULL)
    {
        return;
    }

    printf("--- Arvore de Huffman ---\n");
    print_tree_util_(node, 0);
    printf("\n-------------------------\n");
}

void print_tree_util_ (Node *node, int offset)
{
    if(node == NULL)
    {
        return;
    }    

    offset += OFFSET_INCREMENT;

    print_tree_util_(node->right, offset);

    printf("\n");
    for(int i = OFFSET_INCREMENT; i < offset; i++)
    {
        printf("  ");
    }

    if(is_leaf(node))
    {
        printf("'%c'(f:%d)\n", node->c, node->freq);
    }
    else if (node->c == ' ')
    {
        printf("' '(f:%d)\n", node->freq);
    }
    else
    {
        printf("'*'(f:%d)\n", node->freq);
    }

    print_tree_util_(node->left, offset);
}