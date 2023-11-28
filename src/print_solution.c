#include "pathfinder.h"

void print_solution(int i_count, int dist[i_count][i_count], int path[i_count][i_count], int graph[i_count][i_count], char *islands[i_count])
{
    int printed[i_count][i_count];

    for (int i = 0; i < i_count; i++)
    {
        for (int j = 0; j < i_count; j++)
        {
            printed[i][j] = 0;
        }
    }

    for (int src = 0; src < i_count; src++)
    {
        for (int dest = 0; dest < i_count; dest++)
        {
            if (src != dest && printed[dest][src] != 1)
            {
                printed[src][dest] = 1;
                mx_printstr("========================================\n");
                mx_printstr("Path: ");
                mx_printstr(islands[src]);
                mx_printstr(" -> ");
                mx_printstr(islands[dest]);
                mx_printchar('\n');

                mx_printstr("Route: ");
                int intermediate = path[src][src];
                while (intermediate != dest) {
                    mx_printstr(islands[intermediate]);
                    mx_printstr(" -> ");
                    intermediate = path[intermediate][dest];
                }
                mx_printstr(islands[dest]);

                mx_printstr("\nDistance: ");
                intermediate = path[src][src];
                while (intermediate != dest) {
                    mx_printint(graph[intermediate][path[intermediate][dest]]);
                    intermediate = path[intermediate][dest];
                    if (intermediate != dest) mx_printstr(" + ");
                }
                if (graph[path[src][src]][path[path[src][src]][dest]] != dist[src][dest]) {
                    mx_printstr(" = ");
                    mx_printint(dist[src][dest]);
                }

                mx_printstr("\n========================================\n");
            }
        }
    }
}
