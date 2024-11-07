//Given an undirected weighted connected graph G(V, E) and starring vertex ‘s’. Maintain a Min-Priority Queue ‘Q’ from the vertex set V and apply Prim’s algorithmn to
//● Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’.
//● Display total cost of the minimum spanning tree T.

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100


int minKey(int key[], bool mstSet[], int n) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    
    return min_index;
}

void printMST(int parent[], int graph[MAX][MAX], int n) {
    int totalCost = 0;
    int mst[MAX][MAX] = {0};  

    printf("Cost Adjacency Matrix of the Minimum Spanning Tree (MST):\n");
    for (int i = 1; i < n; i++) {
        mst[i][parent[i]] = mst[parent[i]][i] = graph[i][parent[i]];
        totalCost += graph[i][parent[i]];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mst[i][j]);
        }
        printf("\n");
    }

    printf("\nTotal cost of the Minimum Spanning Tree: %d\n", totalCost);
}

void primMST(int graph[MAX][MAX], int n) {
    int parent[MAX];   
    int key[MAX];      
    bool mstSet[MAX];  

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;  

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);  
        mstSet[u] = true; 

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, n);
}

int main() {
    int n; 
    int graph[MAX][MAX];
    
    FILE *file = fopen("inUnAdjMat.dat", "r");
    
    if (file == NULL) {
        printf("Error in opening the file.\n");
        return 1;
    }

    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(file, "%d", &graph[i][j]);
    
    fclose(file);

    primMST(graph, n);

    return 0;
}

