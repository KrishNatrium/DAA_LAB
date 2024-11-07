#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int u, v, w;
} Edge;

typedef struct
{
    int *parent, *rank;
    int n;
} DisjointSet;

// Function to create a disjoint set
DisjointSet *createDisjointSet(int n)
{
    DisjointSet *ds = (DisjointSet *)malloc(sizeof(DisjointSet));
    ds->n = n;
    ds->parent = (int *)malloc(n * sizeof(int));
    ds->rank = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }

    return ds;
}

// Find function with path compression
int find(DisjointSet *ds, int u)
{
    if (ds->parent[u] != u)
    {
        ds->parent[u] = find(ds, ds->parent[u]);
    }
    return ds->parent[u];
}

// Union function with union by rank
void unionSets(DisjointSet *ds, int u, int v)
{
    int rootU = find(ds, u);
    int rootV = find(ds, v);

    if (rootU != rootV)
    {
        if (ds->rank[rootU] > ds->rank[rootV])
        {
            ds->parent[rootV] = rootU;
        }
        else if (ds->rank[rootU] < ds->rank[rootV])
        {
            ds->parent[rootU] = rootV;
        }
        else
        {
            ds->parent[rootV] = rootU;
            ds->rank[rootU]++;
        }
    }
}

// Comparison function for sorting edges
int compareEdges(const void *a, const void *b)
{
    Edge *edge1 = (Edge *)a;
    Edge *edge2 = (Edge *)b;
    return edge1->w - edge2->w;
}

// Kruskal's algorithm
void kruskal(int n, int m, Edge edges[])
{
    DisjointSet *ds = createDisjointSet(n);
    qsort(edges, m, sizeof(Edge), compareEdges);

    int mstCost = 0;
    printf("Edge Cost\n");

    for (int i = 0; i < m; i++)
    {
        int u = edges[i].u - 1; // Adjust to 0-based index
        int v = edges[i].v - 1; // Adjust to 0-based index

        if (find(ds, u) != find(ds, v))
        {
            unionSets(ds, u, v);
            printf("%d--%d %d\n", edges[i].u, edges[i].v, edges[i].w);
            mstCost += edges[i].w;
        }
    }

    printf("Total Weight of the Spanning Tree: %d\n", mstCost);

    // Free the memory
    free(ds->parent);
    free(ds->rank);
    free(ds);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Edge edges[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    kruskal(n, m, edges);

    return 0;
}
