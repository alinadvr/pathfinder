#include "pathfinder.h"

#define INT_MAX 1000
#define i_count 4
 
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
    int graph[i_count][i_count] = {{0, 12, 5,INT_MAX },
                      {12, 0, INT_MAX, 3},
                      {5, INT_MAX, INT_MAX, 2},
                      {INT_MAX, 3, 2, 0}};

    int parent[i_count][i_count];
    for (int i = 0; i < i_count; i++)
    {
        for (int j = 0; j < i_count; j++)
        {
            if (graph[i][j] != INT_MAX && i != j)
                parent[i][j] = i;
            else
                parent[i][j] = -1;
        }
    }

    // update the path and graphance using the k vertex range from 0 to i_count-1.
    for (int k = 0; k < i_count; k++)
    {
        for (int i = 0; i < i_count; i++)
        {
            for (int j = 0; j < i_count; j++)
            {
                if (graph[i][j] > graph[i][k] + graph[k][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    for (int i = 0; i < i_count; i++)
    {
        for (int j = 0; j < i_count; j++)
        {
            printf("%d ", parent[i][j]);
        }

        printf("\n");
    }

    // Print shortest graphances and paths between all pairs of vertices
    for (int i = 0; i < i_count; i++)
    {
        for (int j = 0; j < i_count; j++)
        {

            if (i == j) continue;
            printf("The Shortest graphance between %d and %d is ", i, j);
            if (graph[i][j] == INT_MAX)
                printf("INT_MAX");
            else
                printf("%d ", graph[i][j]);

            printf("and the shortest path is:- ");
            printPath(parent[i], i, j);
            printf("\n");
        }
    }

}
