#include "pathfinder.h"

void floyd_warshall(int i_count, int dist[i_count][i_count], int path[i_count][i_count])
{
    for (int k = 0; k < i_count; k++)
    {
        for (int i = 0; i < i_count; i++)
        {
            for (int j = 0; j < i_count; j++)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
}
