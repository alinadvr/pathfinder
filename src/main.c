#include "pathfinder.h"

#define INT_MAX 2147483647
 
void printPath(int parent[], char **islands, int i, int j) {
    if (i == j)
        printf("%s ", islands[i]);
    else if (parent[j] == -1)
        printf("No path exists");
    else
    {
        printPath(parent, islands, i, parent[j]);
        printf("%s ", islands[j]);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        mx_printstr("error: invalid number of command-line arguments");
        return 1;
    }

    char *file_name = argv[1];
    int fd = open(file_name, O_RDONLY);

    if (fd == -1)
    {
        mx_printstr("error: file [");
        mx_printstr(file_name);
        mx_printstr("] does not exist");
        return 1;
    }

    int size = file_size(file_name);

    if (size < 1)
    {
        mx_printstr("error: file [");
        mx_printstr(file_name);
        mx_printstr("] is empty");
        return 1;
    }

    char *line_ptr = mx_strnew(1);
    mx_read_line(&line_ptr, 1, '\n', fd);
    int i_count = mx_atoi(line_ptr);

    if (i_count < 1)
    {
        mx_printstr("error: line 1 is not valid");
        return 1;
    }

    int graph[i_count][i_count];
    for (int i = 0; i < i_count; i++)
    {
        for (int j = 0; j < i_count; j++)
        {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INT_MAX;
        }
    }

    char **islands = get_islands_arr(fd, i_count, graph);

    if (islands == NULL)
        return 1;

    for (int i = 0; i < i_count; i++)
    {
        for (int j = 0; j < i_count; j++)
        {
            if (graph[i][j] == INT_MAX) printf("INF ");
            else printf("%d ", graph[i][j]);
        }

        printf("\n");
    }
printf("\n\n");
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

    // for (int i = 0; i < i_count; i++)
    // {
    //     for (int j = 0; j < i_count; j++)
    //     {
    //         printf("%d ", graph[i][j]);
    //     }

    //     printf("\n");
    // }

    // Print shortest graphances and paths between all pairs of vertices
    for (int i = 0; i < i_count; i++)
    {
        for (int j = 0; j < i_count; j++)
        {

            if (i == j) continue;
            printf("The Shortest graphance between %s and %s is ", islands[i], islands[j]);
            if (graph[i][j] == INT_MAX)
                printf("INF");
            else
                printf("%d ", graph[i][j]);

            printf("and the shortest path is:- ");
            printPath(parent[i], islands, i, j);
            printf("\n");
        }
    }

    int closed = -1;
    while (closed == -1)
        closed = close(fd);

//     int result[i_count][i_count];
//     for (int i = 0; i < i_count; i++) {
//         for (int j = 0; j < i_count; j++)
//             result[i][j] = INT_MAX;
//     }

//     printPaths(i_count, result, islands);

    return 0;
}
