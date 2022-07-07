#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINES 100
#define COLS 100

typedef struct {int y1; int x1; int y2; int x2; int weight;} edge;

typedef edge matrix_entry[4];

typedef struct {int y; int x; int risk_level; int cost; int visited;} node;

node matrix[LINES][COLS] = {0};

matrix_entry graph[LINES][COLS] = {0};

void print_matrix() {

    for (int i = 0; i < LINES; i++) {
        printf("[");

        for (int j = 0; j < COLS - 1; j++)
           printf("{y:%d, x:%d, risk:%d, cost:%d}, ", matrix[i][j].y, matrix[i][j].x, matrix[i][j].risk_level, matrix[i][j].cost);

        printf("{y:%d, x:%d, risk:%d, cost:%d}]\n", matrix[i][COLS-1].y, matrix[i][COLS-1].x,
               matrix[i][COLS-1].risk_level, matrix[i][COLS-1].cost);
    }

    printf("\n");
}

void insert_in_position(edge current_edge, edge edges[], int nbr) {
    for (int i = 0; i < nbr; i++)
        if ((matrix[current_edge.y1][current_edge.x1].cost + current_edge.weight) <
            (matrix[edges[i].y1][edges[i].x1].cost + edges[i].weight)) {

            for (int j = nbr; j > i; j--)
                edges[j] = edges[j - 1];

            edges[i] = current_edge;
            return;
        }

    edges[nbr] = current_edge;
}

edge get_least_cost_edge(edge edges_to_visit[], int nbr) {
    edge least_cost_edge = edges_to_visit[0]; 

    for (int i = 0; i < nbr - 1; i++)
        edges_to_visit[i] = edges_to_visit[i+1];

    return least_cost_edge;
}

edge edges_to_visit[5*LINES*COLS];

int djikstra () {
    edge current_edge; 
    node current_node;
    int edges_to_visit_nbr = 0;

    matrix[0][0].visited = 1;
    matrix[0][0].cost = 0;

    insert_in_position(graph[0][0][1], edges_to_visit, edges_to_visit_nbr++);
    insert_in_position(graph[0][0][3], edges_to_visit, edges_to_visit_nbr++);

    while (matrix[LINES-1][COLS-1].visited == 0) {
        current_edge = get_least_cost_edge(edges_to_visit, edges_to_visit_nbr--);
        current_node = matrix[current_edge.y2][current_edge.x2];

        if (current_node.visited == 1)
            continue;

        matrix[current_edge.y2][current_edge.x2].visited = 1;
        matrix[current_edge.y2][current_edge.x2].cost = matrix[current_edge.y1][current_edge.x1].cost + current_edge.weight;

        for (int i = 0; i < 4; i++)
            if ((graph[current_node.y][current_node.x][i].weight != -1) &&
                (matrix[graph[current_node.y][current_node.x][i].y2][graph[current_node.y][current_node.x][i].x2].visited == 0))
                insert_in_position(graph[current_node.y][current_node.x][i], edges_to_visit, edges_to_visit_nbr++);
    }

    return matrix[LINES-1][COLS-1].cost;
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input15", "r");
    char c;

    for (int j = 0; j < LINES; j++) {

        for (int i = 0; i < COLS; i++) {
            c = fgetc(fp);
            matrix[j][i] = (node) {j, i, c - '0', -1, 0};
        }

        fgetc(fp);
    }

    for (int i = 0; i < COLS; i++)

        for (int j = 0; j < LINES; j++) {
            if (j-1 >= 0)
                graph[j][i][0] = (edge) {j, i, j-1, i,   matrix[j-1][i].risk_level};//up
            else
                graph[j][i][0] = (edge) {-1, -1, -1, -1, -1};

            if (j+1 < LINES)
                graph[j][i][1] = (edge) {j, i, j+1, i,   matrix[j+1][i].risk_level};//down
            else
                graph[j][i][1] = (edge) {-1, -1, -1, -1, -1};
                
            if (i-1 >= 0)
                graph[j][i][2] = (edge) {j, i, j,   i-1, matrix[j][i-1].risk_level};//left
            else
                graph[j][i][2] = (edge) {-1, -1, -1, -1, -1};

            if (i+1 < LINES)
                graph[j][i][3] = (edge) {j, i, j,   i+1, matrix[j][i+1].risk_level};//right
            else
                graph[j][i][3] = (edge) {-1, -1, -1, -1, -1};
        }
 
    printf("The lowest total risk of any path: %d\n", djikstra());

    return 0;
}
