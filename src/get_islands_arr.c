#include "pathfinder.h"
#include <stdio.h>

char **get_islands_arr(int fd, int i_count, int graph[i_count][i_count])
{
    int i = 0, j = 0, k = 0, line_in = 1;
    int bridges_sum = 0;
    char **islands = (char **) malloc((i_count + 1) * sizeof(char **));
    islands[i_count] = NULL;
    char *line = mx_strnew(MAX_LINE_LENGTH);

    while(mx_read_line(&line, MAX_LINE_LENGTH, '\n', fd) > 0)
    {
        line_in++;

        int c_count = mx_count_substr(line, ",");
        
        if (c_count != 1)
        {
            mx_printstr("error: line [");
            mx_printint(line_in);
            mx_printstr("] is not valid");
            return NULL;
        }

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

        bridges_sum += bridge_length;

        if (bridges_sum > INT_MAX || bridges_sum < 0)
        {
            mx_printstr("sum of bridges lengths is too big");
            return NULL;
        }

        int h_count = mx_count_substr(bridge[0], "-");

        if (h_count != 1)
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

        if (k >= i_count || j >= i_count)
        {
            mx_printstr("error: invalid number of islands");
            return NULL;
        }

        if (graph[k][j] != INT_MAX)
        {
            mx_printstr("error: duplicate bridges");
            return NULL;
        }

        graph[k][j] = bridge_length;
        graph[j][k] = bridge_length;
    }

    return islands;
}
