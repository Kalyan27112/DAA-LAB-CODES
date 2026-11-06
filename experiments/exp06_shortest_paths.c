#include <limits.h>
#include <stdio.h>

#define MAX_VERTICES 100
#define MAX_EDGES 10000
#define INF (LLONG_MAX / 4)

typedef struct { int from, to; long long weight; } Edge;

static void print_distances(const char *label, const long long distance[], int n) {
    printf("%s: ", label);
    for (int i = 0; i < n; ++i) {
        if (distance[i] == INF) printf("INF ");
        else printf("%lld ", distance[i]);
    }
    putchar('\n');
}

int main(void) {
    int vertices, edge_count;
    printf("Vertices and edges: ");
    if (scanf("%d%d", &vertices, &edge_count) != 2 || vertices < 1 ||
        vertices > MAX_VERTICES || edge_count < 0 || edge_count > MAX_EDGES) return 1;

    Edge edges[MAX_EDGES];
    long long graph[MAX_VERTICES][MAX_VERTICES];
    for (int i = 0; i < vertices; ++i)
        for (int j = 0; j < vertices; ++j)
            graph[i][j] = i == j ? 0 : INF;

    int nonnegative = 1;
    puts("Enter directed edges as: from to weight (vertices are 0-based)");
    for (int i = 0; i < edge_count; ++i) {
        if (scanf("%d%d%lld", &edges[i].from, &edges[i].to, &edges[i].weight) != 3)
            return 1;
        if (edges[i].from < 0 || edges[i].from >= vertices ||
            edges[i].to < 0 || edges[i].to >= vertices) return 1;
        if (edges[i].weight < 0) nonnegative = 0;
        if (edges[i].weight < graph[edges[i].from][edges[i].to])
            graph[edges[i].from][edges[i].to] = edges[i].weight;
    }
    int source;
    printf("Source vertex: ");
    if (scanf("%d", &source) != 1 || source < 0 || source >= vertices) return 1;

    long long distance[MAX_VERTICES];
    if (nonnegative) {
        int visited[MAX_VERTICES] = {0};
        for (int i = 0; i < vertices; ++i) distance[i] = INF;
        distance[source] = 0;
        for (int step = 0; step < vertices; ++step) {
            int u = -1;
            for (int i = 0; i < vertices; ++i)
                if (!visited[i] && (u == -1 || distance[i] < distance[u])) u = i;
            if (u == -1 || distance[u] == INF) break;
            visited[u] = 1;
            for (int v = 0; v < vertices; ++v)
                if (graph[u][v] != INF && distance[v] > distance[u] + graph[u][v])
                    distance[v] = distance[u] + graph[u][v];
        }
        print_distances("Dijkstra distances", distance, vertices);
    } else {
        puts("Dijkstra skipped because the graph has a negative edge.");
    }

    for (int i = 0; i < vertices; ++i) distance[i] = INF;
    distance[source] = 0;
    for (int step = 1; step < vertices; ++step) {
        int changed = 0;
        for (int i = 0; i < edge_count; ++i) {
            Edge edge = edges[i];
            if (distance[edge.from] != INF &&
                distance[edge.to] > distance[edge.from] + edge.weight) {
                distance[edge.to] = distance[edge.from] + edge.weight;
                changed = 1;
            }
        }
        if (!changed) break;
    }
    for (int i = 0; i < edge_count; ++i) {
        Edge edge = edges[i];
        if (distance[edge.from] != INF &&
            distance[edge.to] > distance[edge.from] + edge.weight) {
            puts("Bellman-Ford detected a reachable negative-weight cycle.");
            return 0;
        }
    }
    print_distances("Bellman-Ford distances", distance, vertices);
    return 0;
}
