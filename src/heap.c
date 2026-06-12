#include <stdlib.h>
#include "huffman.h"

MinHeap *create_heap(int capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->data     = malloc(sizeof(Node *) * capacity);
    heap->size     = 0;
    heap->capacity = capacity;
    return heap;
}

static void swap(Node **a, Node **b) {
    Node *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify_up(MinHeap *heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent]->freq > heap->data[i]->freq) {
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        } else {
            break;
        }
    }
}

static void heapify_down(MinHeap *heap, int i) {
    while (1) {
        int left  = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left  < heap->size && heap->data[left]->freq  < heap->data[smallest]->freq)
            smallest = left;
        if (right < heap->size && heap->data[right]->freq < heap->data[smallest]->freq)
            smallest = right;

        if (smallest == i) break;

        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }
}

void heap_insert(MinHeap *heap, Node *node) {
    heap->data[heap->size++] = node;
    heapify_up(heap, heap->size - 1);
}

Node *heap_extract_min(MinHeap *heap) {
    Node *min = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify_down(heap, 0);
    return min;
}

void free_heap(MinHeap *heap) {
    free(heap->data);
    free(heap);
}