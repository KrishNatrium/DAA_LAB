#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
struct SYMBOL
{
    char alphabet;
    int frequency;
};

struct Node
{
    struct SYMBOL symbol;
    struct Node *left, *right;
};

struct MinHeap
{
    int size;
    struct Node *heap[MAX];
};

struct Node *createNode(struct SYMBOL symbol)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->symbol = symbol;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void swap(struct Node **a, struct Node **b)
{
    struct Node *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap *minHeap, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < minHeap->size && minHeap->heap[left]->symbol.frequency < minHeap->heap[smallest]->symbol.frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->heap[right]->symbol.frequency < minHeap->heap[smallest]->symbol.frequency)
        smallest = right;

    if (smallest != i)
    {
        swap(&minHeap->heap[i], &minHeap->heap[smallest]);
        minHeapify(minHeap, smallest);
    }
}

struct Node *extractMin(struct MinHeap *minHeap)
{
    if (minHeap->size <= 0)
        return NULL;
    if (minHeap->size == 1)
    {
        minHeap->size--;
        return minHeap->heap[0];
    }

    struct Node *root = minHeap->heap[0];
    minHeap->heap[0] = minHeap->heap[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void insertMinHeap(struct MinHeap *minHeap, struct Node *node)
{
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->heap[i] = node;

    while (i && minHeap->heap[i]->symbol.frequency < minHeap->heap[(i - 1) / 2]->symbol.frequency)
    {
        swap(&minHeap->heap[i], &minHeap->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct Node *buildHuffmanTree(struct SYMBOL symbols[], int n)
{
    struct MinHeap minHeap;
    minHeap.size = 0;

    for (int i = 0; i < n; i++)
    {
        struct Node *newNode = createNode(symbols[i]);
        insertMinHeap(&minHeap, newNode);
    }

    while (minHeap.size > 1)
    {
        struct Node *left = extractMin(&minHeap);
        struct Node *right = extractMin(&minHeap);

        struct SYMBOL internalSymbol;
        internalSymbol.frequency = left->symbol.frequency + right->symbol.frequency;
        internalSymbol.alphabet = '$';

        struct Node *internalNode = createNode(internalSymbol);
        internalNode->left = left;
        internalNode->right = right;

        insertMinHeap(&minHeap, internalNode);
    }

    return extractMin(&minHeap);
}

void inorderTraversal(struct Node *root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    if (root->symbol.alphabet != '$')
        printf("%c ", root->symbol.alphabet);
    inorderTraversal(root->right);
}

int main()
{
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    struct SYMBOL symbols[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &symbols[i].alphabet);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &symbols[i].frequency);
    }

    struct Node *root = buildHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
