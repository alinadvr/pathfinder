#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_ISLAND_NAME 50
#define MAX_BRIDGES 100

typedef struct {
    char island1[MAX_ISLAND_NAME];
    char island2[MAX_ISLAND_NAME];
    int length;
} Bridge;

typedef struct {
    char **path;
    int *distances;
    int size;
} Route;

int findIslandIndex(char *island, char **islands, int numIslands) {
    for (int i = 0; i < numIslands; i++) {
        if (strcmp(island, islands[i]) == 0) {
            return i;
        }
    }
    return -1; // Island not found
}

int **initializeGraph(int numIslands, int defaultValue) {
    int **graph = (int **)malloc(numIslands * sizeof(int *));
    for (int i = 0; i < numIslands; i++) {
        graph[i] = (int *)malloc(numIslands * sizeof(int));
        for (int j = 0; j < numIslands; j++) {
            graph[i][j] = (i == j) ? 0 : defaultValue; // Diagonal elements are 0, others default to INT_MAX
        }
    }
    return graph;
}

void populateGraph(int **graph, Bridge *bridges, int numBridges) {
    for (int i = 0; i < numBridges; i++) {
        int from = findIslandIndex(bridges[i].island1); // Function to find index of island in the graph
        int to = findIslandIndex(bridges[i].island2);
        int length = bridges[i].length;
        if (from != -1 && to != -1) {
            graph[from][to] = length;
            graph[to][from] = length; // Assuming bi-directional connections
        }
    }
}

int parseInput(const char *filename, Bridge **bridges, int *numIslands) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "error: file %s does not exist\n", filename);
        return 0;
    }

    if (fscanf(file, "%d", numIslands) != 1 || *numIslands <= 0) {
        fprintf(stderr, "error: line 1 is not valid\n");
        fclose(file);
        return 0;
    }

    *bridges = (Bridge *) malloc(sizeof(Bridge) * MAX_BRIDGES);

    int index = 0;
    while (fscanf(file, "%49[^-]-%49[^,],%d", (*bridges)[index].island1, (*bridges)[index].island2,
                  &(*bridges)[index].length) == 3) {
        if ((*bridges)[index].length <= 0) {
            fprintf(stderr, "error: line %d is not valid\n", index + 2);
            fclose(file);
            return 0;
        }

        for (int i = 0; i < index; i++) {
            if ((strcmp((*bridges)[i].island1, (*bridges)[index].island1) == 0 &&
                 strcmp((*bridges)[i].island2, (*bridges)[index].island2) == 0) ||
                (strcmp((*bridges)[i].island1, (*bridges)[index].island2) == 0 &&
                 strcmp((*bridges)[i].island2, (*bridges)[index].island1) == 0)) {
                fprintf(stderr, "error: duplicate bridges\n");
                fclose(file);
                return 0;
            }
        }

        index++;
    }

    fclose(file);
    return 1;
}

Route createRoute(int size) {
    Route newRoute;
    newRoute.path = (char **) malloc(sizeof(char *) * size);
    newRoute.distances = (int *) malloc(sizeof(int) * size);
    newRoute.size = size;
    for (int i = 0; i < size; i++) {
        newRoute.path[i] = NULL;
        newRoute.distances[i] = 0;
    }
    return newRoute;
}

void addRoute(Route *route, const char *island, int distance) {
    route->path[route->size] = strdup(island);
    route->distances[route->size] = distance;
    route->size++;
}

void printRoute(Route route) {
    printf("========================================\n");
    printf("Path: %s -> %s\n", route.path[0], route.path[route.size - 2]);
    printf("Route: %s", route.path[0]);
    int sum = 0;
    for (int i = 1; i < route.size; i++) {
        printf(" -> %s", route.path[i]);
        sum += route.distances[i - 1];
    }
    printf("\nDistance: ");
    for (int i = 0; i < route.size - 1; i++) {
        printf("%d + ", route.distances[i]);
    }
    printf("%d = %d\n", route.distances[route.size - 2], sum + route.distances[route.size - 2]);
    printf("========================================\n");
}

void findPaths(int **graph, Bridge *bridges, int numIslands, int from, int to, Route route, int *visited) {
    visited[from] = 1;

    addRoute(&route, bridges[from].island1, graph[from][to]);

    if (from == to) {
        printRoute(route);
    } else {
        for (int i = 0; i < numIslands; i++) {
            if (graph[from][i] != INT_MAX && !visited[i]) {
                Route newRoute = createRoute(route.size + 1);
                memcpy(newRoute.path, route.path, sizeof(char *) * route.size);
                memcpy(newRoute.distances, route.distances, sizeof(int) * (route.size - 1));
                newRoute.path[route.size - 1] = strdup(bridges[from].island1); // Update path with current island
                findPaths(graph, bridges, numIslands, i, to, newRoute, visited);
            }
        }
    }

    visited[from] = 0;
    free(route.path[route.size - 1]);
    route.size--;
}

int main(int argc, char *argv[]) {

    Bridge *bridges;
    int numIslands;

    if (!parseInput("../hard", &bridges, &numIslands)) {
        return EXIT_FAILURE;
    }

    char **islands = (char **)malloc(numIslands * sizeof(char *));
    for (int i = 0; i < numIslands; i++) {
        islands[i] = (char *)malloc(MAX_ISLAND_NAME * sizeof(char));
        // Copy island names to the islands array
        strcpy(islands[i], bridges[i].island1);
    }

    int **graph = initializeGraph(numIslands, INT_MAX);
    populateGraph(graph, bridges, numBridges, islands, numIslands);
    //display graph

    for (int i = 0; i < numIslands; i++) {
        for (int j = 0; j < numIslands; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }


//    for (int i = 0; i < numIslands; i++) {
//        for (int j = i + 1; j < numIslands; j++) {
//            if (graph[i][j] != INT_MAX) {
//                int *visited = (int *) calloc(numIslands, sizeof(int));
//                Route route = createRoute(1);
//                findPaths(graph, bridges, numIslands, i, j, route, visited);
//                free(visited);
//            }
//        }
//    }

    for (int i = 0; i < numIslands; i++) {
        free(graph[i]);
    }
    free(graph);
    free(bridges);

    return EXIT_SUCCESS;
}
