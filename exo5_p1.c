#include <stdio.h>

#define VALUES 500

typedef struct {int x; int y;} point;
typedef struct {point p1; point p2;} segment;

int max(int x, int y) {
    if (x > y)
        return x;

    return y;
}

int min(int x, int y) {
    if (x > y)
        return y;

    return x;
}

int horizontal(segment s){
    return s.p1.y == s.p2.y;
}

int vertical(segment s){
    return s.p1.x == s.p2.x;
}

void print_array(segment segments[]){

    for (int i = 0; i < VALUES; i++)
        printf("%d,%d -> %d,%d\n", segments[i].p1.x, segments[i].p1.y,
                                       segments[i].p2.x, segments[i].p2.y);
}

void print_plane(int plane[][1000]) {
    printf("[\n ");

    for (int i = 0; i < 1000; i++) {
        printf("[");

        for (int j = 0; j < 1000; j++)
            printf(" %d ", plane[i][j]);

        printf("]\n");
    }

    printf("]");
}

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input5", "r");
    segment segments[VALUES];
    int plane[1000][1000] = {0};
    int collision_points = 0;

    for(int i = 0; i < VALUES ; i++)
        fscanf(fi, "%d,%d -> %d,%d\n", &segments[i].p1.x, &segments[i].p1.y, &segments[i].p2.x, &segments[i].p2.y); 

    for (int i = 0; i < VALUES; i++)
        if (vertical(segments[i]))

            for (int j = min(segments[i].p1.y, segments[i].p2.y); j <= max(segments[i].p1.y, segments[i].p2.y); j++)
                plane[j][segments[i].p1.x]++;

        else if (horizontal(segments[i]))

            for (int j = min(segments[i].p1.x, segments[i].p2.x); j <= max(segments[i].p1.x, segments[i].p2.x); j++)
                plane[segments[i].p1.y][j]++;

    for (size_t i = 0; i < 1000; i++)

            for (size_t j = 0; j < 1000; j++)
                collision_points += (plane[i][j] > 1);

    printf("the number of collisions is: %d\n", collision_points);

    return 0;
}
