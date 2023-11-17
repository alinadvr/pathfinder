#include <stdbool.h>
#include <stdio.h>
#include "pathfinder.h"

#define INT_MAX 2147483647
#define MAX_LENGTH 10000
// // A utility function to find the vertex with minimum
// // distance value, from the set of vertices not yet included
// // in shortest path tree

int minDistance(int dist[], bool sptSet[], int i_count)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < i_count; v++){
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }
 
    return min_index;
}
 
// A utility function to print the constructed distance
// array
// void printSolution(int dist[], int i_count)
// {
//     printf("Vertex \t\t Distance from Source\n");
//     for (int i = 0; i < i_count; i++)
//         printf("%d \t\t\t\t %d\n", i, dist[i]);
// }

void printPaths(int i_count, int result[][i_count], char **islands) {
    for (int i = 0; i < i_count; i++) {
        for (int j = i + 1; j < i_count; j++) {
            char *start = islands[i];
            char *end = islands[j];
            int dist = result[i][j];

            char path[1000]; // Assuming a max path length of 1000 characters
            sprintf(path, "%s -> %s", start, end);

            printf("========================================\n");
            printf("Path: %s\n", path);

            if (dist == INT_MAX) {
                printf("Route: No path found\n");
                printf("Distance: No path found\n");
            } else {
                printf("Route: %s", start);

                // Store the shortest path indices
                int shortestPath[i_count];
                shortestPath[0] = i;
                shortestPath[1] = j;
                int pathLength = 2;

                // Find intermediate points for shortest paths
                for (int k = 0; k < i_count; k++) {
                    if (k != i && k != j) {
                        if (result[i][k] + result[k][j] < dist) {
                            // Found a shorter path, update distance and path
                            dist = result[i][k] + result[k][j];
                            shortestPath[0] = i;
                            shortestPath[1] = k;
                            shortestPath[2] = j;
                            pathLength = 3;
                        }
                    }
                }

                // Print the shortest path route and distance
                for (int k = 1; k < pathLength; k++) {
                    printf(" -> %s", islands[shortestPath[k]]);
                }

                printf("\nDistance: ");
                for (int k = 0; k < pathLength - 1; k++) {
                    printf("%d", result[shortestPath[k]][shortestPath[k + 1]]);
                    if (k != pathLength - 2) {
                        printf(" + ");
                    }
                }
                printf(" = %d\n", dist);
            }

            printf("========================================\n");
        }
    }
}



void printSolution(int i_count, int dist[][i_count]) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < i_count; i++) {
        for (int j = 0; j < i_count; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}
 
// // Function that implements Dijkstra's single source
// // shortest path algorithm for a graph represented using
// // adjacency matrix representation
void dijkstra(int i_count,int graph[][i_count], int dist[i_count][i_count], int src)
{
//  int dist[i_count][i_count];
    bool sptSet[i_count];

    for (int i = 0; i < i_count; i++) {
    //     for (int j = 0; j < i_count; j++)
    //         dist[i][j] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src][src] = 0;

    for (int count = 0; count < i_count - 1; count++) {
        int u = minDistance(dist[src], sptSet, i_count);

        sptSet[u] = true;

        for (int v = 0; v < i_count; v++) {
            if (!sptSet[v] && graph[u][v] && dist[src][u] != INT_MAX &&
                dist[src][u] + graph[u][v] < dist[src][v])
                dist[src][v] = dist[src][u] + graph[u][v];
        }
    }

    // printSolution(i_count, dist);
    }

int mx_atoi(char *str)
{
 int res = 0; // Initialize result

 // Iterate through all characters of input string and
 // update result
 for (int i = 0; str[i] != '\0'; ++i) {
     if (str[i]> '9' || str[i]<'0')
         return -1;
     res = res*10 + str[i] - '0';
 }

 // return result.
 return res;
}


int index_of(char **arr, char *str) {
    for (int i = 0; arr[i] != NULL; i++) {
        if (mx_strcmp(arr[i], str) == 0) {
            return i;
        }
    }
    return -1;
}

 
// driver's code
int main(void)
{
    int fd = open("hard", O_RDONLY);
    char *lineptr = mx_strnew(1);

    mx_read_line(&lineptr, 1, '\n', fd);
    mx_printstr(lineptr);
    mx_printchar('\n');
    int i_count = mx_atoi(lineptr);
    int i = 0;
    int j = 0;
    int k = 0;
    char *islands[i_count];
    for (int i = 0; i < i_count; i++) {
        islands[i] = NULL;
    }
    int graph[i_count][i_count];

    for (int i = 0; i < i_count; i++) {
        for (int j = 0; j < i_count; j++) {
            graph[i][j] = 0;

        }
    }



    char *line = mx_strnew(MAX_LENGTH);
    while(mx_read_line(&line, MAX_LENGTH, '\n', fd) > 0) {
        
mx_printstr(line);
mx_printchar(' ');
        char **bridge = mx_strsplit(line, ',');
        int bridge_length = mx_atoi(bridge[1]);
        char** current_island = mx_strsplit(bridge[0], '-');
        mx_printstr(current_island[0]);
        mx_printchar(' ');
        int island_index_1 = index_of(islands, current_island[0]);
        mx_printint(island_index_1);
        mx_printchar(' ');
        if(island_index_1 == -1) {
            islands[i] = current_island[0];
            k = i;
            i++;
        } else {
            k = island_index_1;
        }
        int island_index_2 = index_of(islands, current_island[1]);
        if(island_index_2 == -1) {
            islands[i] = current_island[1];
            j = i;
            i++;
        } else {
            j = island_index_2;
        }
        
        mx_printint(i);
        mx_printchar(' ');
        mx_printint(j);
        mx_printchar(' ');
        mx_printint(k);

        graph[k][j] = bridge_length;
        graph[j][k] = bridge_length;
        mx_printchar('\n');
    }
    for (int i = 0; i < i_count; i++) {
        for (int j = 0; j < i_count; j++) {
            mx_printint(graph[i][j]);
        }
    }
    /* Let us create the example graph discussed above */
    // int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
    //                     { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
    //                     { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
    //                     { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
    //                     { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
    //                     { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
    //                     { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
    //                     { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
    //                     { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
 
    int result[i_count][i_count];
    for (int i = 0; i < i_count; i++) {
        for (int j = 0; j < i_count; j++)
            result[i][j] = INT_MAX;
    }
    // Function call
    for (int i = 0; i < i_count; i++) {
        dijkstra(i_count, graph, result, i);
    }

// mx_printstr("RESULT\n");
//     for(int i = 0; i < i_count; i++) {
//         for(int j = 0; j < i_count; j++) {
//             mx_printint(result[i][j]);
//             mx_printchar(' ');
//         }
//         mx_printchar('\n');
//     }

    printPaths(i_count, result, islands);

    close(fd);
    
    return 0;
}

