#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARCS 23
typedef const char *node;

typedef struct {node a; node b;} arc;

arc *arcs;

void print_nodes(node nodes[], int nbr) {
    if (nbr == 0)
        return;

    printf("{");

    for (int i = 0; i < nbr - 1; i++)
        printf("%s, ", nodes[i]);

    printf("%s}\n", nodes[nbr - 1]);
}

int get_neighbours(node a, node neighbours[]) {
    int k = 0;

    for (int i = 0; i < ARCS; i++) {
        if (!strcmp(arcs[i].a, a)) {
            neighbours[k++] = arcs[i].b;
        }
        else if (!strcmp(arcs[i].b, a)) {
            neighbours[k++] = arcs[i].a;
        }
    }

    return k;
}

int visited_twice(node path[], int path_length) {
    node visited[path_length];
    int duplicates = 0, k = 0;

    for (int i = 0; i < path_length; i++) {
        if(islower(path[i][0])) {

            for (int j = 0; j < k; j++) {
                if(!strcmp(path[i], visited[j]) &&
                   ((duplicates++ == 1) || !strcmp(visited[j], "end") || !strcmp(visited[j], "start")))
                    return 1;
            }
            visited[k++] = path[i] ;
        }
    }
    return 0;
}

int find_paths(node starting_point, node the_path[], int path_length) {

    if (visited_twice(the_path, path_length))
        return 0;
    
    if (!strcmp(starting_point, "end")) {
        print_nodes(the_path, path_length);
        return 1;}
    
    else {
        int paths = 0;
        node neighbours[ARCS*2];
        int nbr_neighbours = get_neighbours(starting_point, neighbours);
        
        for (int i = 0; i < nbr_neighbours; i++) {
            
            node new_path[path_length+1];
            
            for (int j = 0; j < path_length; j++)
                new_path[j] = the_path[j];
            
            new_path[path_length] = starting_point;
            paths += find_paths(neighbours[i], new_path, path_length + 1);
        }
        
        return paths;
        
    }
}


int main(int argc, char *argv[])
{
    char buffer[11];
    int i = 0;
    arcs = malloc(ARCS*sizeof(arc));
    char *c, *c2;

    FILE *fp = fopen("input12", "r");

    while(fgets(buffer, 11, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        c = malloc(6*sizeof(char));
        strcpy(c, strtok(buffer, "-"));
        c2 = malloc(6*sizeof(char));
        strcpy(c2, strtok(NULL, "-"));
        arcs[i++] = (arc) {c, c2};
    }

    fclose(fp);

    printf("paths with same small cave visited at most twice: %d\n", find_paths("start", NULL, 0));

    return 0;
}
