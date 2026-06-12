#include <stdio.h>
#include <stdbool.h>

#define OFFSET_INCREMENT 10

typedef struct Node
{
    unsigned char c;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

// Min-Heap
typedef struct {
    Node **data;
    int    size;
    int    capacity;
} MinHeap;


Node* create_node(unsigned char c, int freq);

bool is_leaf(Node *node);

void serialize_huffman_tree(Node *node, FILE *file);

Node* deserialize_huffman_tree(FILE *file);

void free_tree(Node *node);

void print_huffman_tree(Node *node);

void print_tree_util_ (Node *node, int offset);

// Min Heap
MinHeap *create_heap(int capacity);
void     heap_insert(MinHeap *heap, Node *node);
Node    *heap_extract_min(MinHeap *heap);
void     free_heap(MinHeap *heap);