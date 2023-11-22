#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <stdbool.h>
#include <stdio.h>
#include "libmx.h"

int main (int argc, char *argv[]);
char **get_islands_arr(int fd, int i_count, int graph[i_count][i_count]);

#endif
