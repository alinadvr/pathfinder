#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <stdbool.h>
#include <stdio.h>
#include "libmx.h"

#define INT_MAX 2147483647
#define MAX_LINE_LENGTH 10000

int main (int argc, char *argv[]);
char **get_islands_arr(int fd, int i_count, int graph[i_count][i_count]);
void floyd_warshall(int i_count, int dist[i_count][i_count], int path[i_count][i_count]);
void print_solution(int i_count, int dist[i_count][i_count], int path[i_count][i_count], int graph[i_count][i_count], char *islands[i_count]);

#endif
