#include "pathfinder.h"

#define MAX_LINE_LENGTH 10000

char **get_islands_arr(int fd, int i_count, int graph[i_count][i_count])
{
    int i = 0, j = 0, k = 0, line_in = 1;
    char **islands = (char **) malloc((i_count + 1) * sizeof(char **));
    islands[i_count] = NULL;
    char *line = mx_strnew(MAX_LINE_LENGTH);

    while(mx_read_line(&line, MAX_LINE_LENGTH, '\n', fd) > 0)
    {
        line_in++;
        char **bridge = mx_strsplit(line, ',');

        if (bridge == NULL || bridge[0] == NULL || bridge[1] == NULL)
        {
            mx_printstr("error: line [");
            mx_printint(line_in);
            mx_printstr("] is not valid");
            return NULL;
        }

        int bridge_length = mx_atoi(bridge[1]);

        if (bridge_length < 0)
        {
            mx_printstr("error: line [");
            mx_printint(line_in);
            mx_printstr("] is not valid");
            return NULL;
        }

        char **current_islands = mx_strsplit(bridge[0], '-');
        
        if (current_islands == NULL || current_islands[0] == NULL || current_islands[1] == NULL)
        {
            mx_printstr("error: line [");
            mx_printint(line_in);
            mx_printstr("] is not valid");
            return NULL;
        }

        int island_index_1 = index_of(islands, current_islands[0]);
        if (island_index_1 == -1)
        {
            islands[i] = current_islands[0];
            k = i;
            i++;
        }
        else
            k = island_index_1;

        int island_index_2 = index_of(islands, current_islands[1]);
        if (island_index_2 == -1)
        {
            islands[i] = current_islands[1];
            j = i;
            i++;
        }
        else
            j = island_index_2;
        
        graph[k][j] = bridge_length;
        graph[j][k] = bridge_length;
    }

    return islands;
}
