#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

void printPath(int previous[], int i) {
    if (previous[i] == -1) {
        printf("%d", i + 1);
        return;
    }
    printPath(previous, previous[i]);
    printf("->%d", i + 1);
}

void dijkstra(int graph[MAX][MAX], int n, int start_vertex) {
    int distance[MAX], visited[MAX], previous[MAX];

    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        visited[i] = 0;
        previous[i] = -1;
    }
    distance[start_vertex] = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_distance = INF, min_index;

        for (int v = 0; v < n; v++)
            if (!visited[v] && distance[v] <= min_distance)
                min_distance = distance[v], min_index = v;

        visited[min_index] = 1;

        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[min_index][v] && distance[min_index] != INF 
                && distance[min_index] + graph[min_index][v] < distance[v]) {
                distance[v] = distance[min_index] + graph[min_index][v];
                previous[v] = min_index;
            }
    }

    printf("Source Destination Cost Path\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d ", start_vertex + 1, i + 1, distance[i]);
        if (distance[i] != INF && i != start_vertex) {
            printPath(previous, i);
        } else {
            printf("-");
        }
        printf("\n");
    }
}

void read_graph(char *filename, int graph[MAX][MAX], int *n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int i = 0, j = 0;
    while (fscanf(file, "%d", &graph[i][j]) != EOF) {
        if (fgetc(file) == '\n') {
            i++;
            j = 0;
        } else {
            j++;
        }
    }
    *n = i + 1; 
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <source_vertex>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int start_vertex = atoi(argv[2]) - 1; 

    int graph[MAX][MAX], n;
    read_graph(filename, graph, &n);

    dijkstra(graph, n, start_vertex);

    return 0;
}

