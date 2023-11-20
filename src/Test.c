#include <stdio.h>
#define INF 1000000000 // Infinity
#define V 4

void printPath(int parent[], int i, int j) {
    if (i == j)
        printf("%d ", i);
    else if (parent[j] == -1)
        printf("No path exists");
    else
    {
        printPath(parent, i, parent[j]);
        printf("%d ", j);
    }
}

int main()
{
    // V represent number of vertices
    int dist[V][V] = {{0, 12, 5,INF },
                      {12, 0, INF, 3},
                      {5, INF, INF, 2},
                      {INF, 3, 2, 0}};
    // Represent the graph using adjacency matrix

    // Apply the Floyd Warshall algorithm to find the shortest paths
    int parent[V][V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] != INF && i != j)
                parent[i][j] = i;
            else
                parent[i][j] = -1;
        }
    }
    // update the path and distance using the k vertex range from 0 to V-1.
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    // Print shortest distances and paths between all pairs of vertices
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("The Shortest distance between %d and %d is ", i, j);
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);


            printf("and the shortest path is:- ");
            printPath(parent[i], i, j);
            printf("\n");
        }
    }

    return 0;
}

