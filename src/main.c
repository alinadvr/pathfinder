#include "pathfinder.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        mx_printstr("error: invalid number of command-line arguments\n");
        return 1;
    }

    char *file_name = argv[1];
    int fd = open(file_name, O_RDONLY);

    if (fd == -1)
    {
        mx_printstr("error: file ");
        mx_printstr(file_name);
        mx_printstr(" does not exist\n");
        close(fd);
        return 1;
    }

    int size = file_size(file_name);

    if (size < 1)
    {
        mx_printstr("error: file ");
        mx_printstr(file_name);
        mx_printstr(" is empty\n");
        close(fd);
        return 1;
    }

    char *line_ptr = mx_strnew(1);
    mx_read_line(&line_ptr, 1, '\n', fd);
    int i_count = mx_atoi(line_ptr);

    if (i_count < 1)
    {
        mx_printstr("error: line 1 is not valid\n");
        close(fd);
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

    close(fd);

    if (islands == NULL)
        return 1;

    int dist[i_count][i_count];
    int path[i_count][i_count];

    for (int i = 0; i < i_count; i++) {
        for (int j = 0; j < i_count; j++) {
            dist[i][j] = graph[i][j];
            path[i][j] = j;
        }
    }

    floyd_warshall(i_count, dist, path);

    print_solution(i_count, dist, path, graph, islands);

    return 0;
}
