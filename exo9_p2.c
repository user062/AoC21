#include <stdio.h>
#include <stdlib.h>

#define LINES  100
#define COLS 100

typedef struct {int x; int y;} location;

location locations[LINES*COLS];

int basins[LINES*COLS], basin_count = -1, locations_number = -1;

int in_basins(int x, int y) {

   for (int i = 0; i <= locations_number; i++)
       if (locations[i].x == x && locations[i].y == y)
           return 1;

   return 0;
}

void add_to_basins(int x, int y) {
    location l = {x, y};
    locations[++locations_number] = l;
}

int get_basin_point(int locations[][COLS], int x, int y) {

    if (in_basins(x, y))
        return 0;

    int up = 0, down = 0, left = 0, right = 0;

    add_to_basins(x, y);

    if (x < LINES - 1 && locations[x+1][y] != 9)
        down = get_basin_point(locations, x+1, y); 

    if (x > 0  && locations[x-1][y] != 9)
        up = get_basin_point(locations, x-1, y); 

    if (y > 0  && locations[x][y-1] != 9)
        left = get_basin_point(locations, x, y-1); 

    if (y < COLS - 1 && locations[x][y+1] != 9)
        right = get_basin_point(locations, x, y+1); 

    return 1+up+down+left+right;
}

void find_all_low_points(int matrix[][COLS]) {
    int up, down, left, right;

    for (int i = 0; i < LINES ; i++)

        for (int j = 0 ; j < COLS ; j++) {

            if (j == 0)
                left = matrix[i][j] + 1;
            else
                left = matrix[i][j-1];

            if (j == COLS - 1)
                right = matrix[i][j] + 1;
            else
                right = matrix[i][j+1];

            if (i == 0)
                up = matrix[i][j] + 1;
            else
                up = matrix[i-1][j];

            if (i == LINES - 1)
                down = matrix[i][j] + 1;
            else
                down = matrix[i+1][j];

            if (matrix[i][j] < up &&
                matrix[i][j] < down &&
                matrix[i][j] < right &&
                matrix[i][j] < left)
                basins[++basin_count] = get_basin_point(matrix, i, j);
        }
}

int compare(const void *a, const void *b) {
    if (*(int*)a < *(int*)b)
        return 1;

    if (*(int*)a > *(int*)b)
        return -1;

    return 0;
}

int main(int argc, char *argv[])
{
    int matrix[LINES][COLS];

    FILE *fp = fopen("input9", "r");

    for (int i = 0; i < LINES; i++) {

        for (int j = 0; j < COLS; j++)
            matrix[i][j] = fgetc(fp) - '0'; // to convert the from char to int

        fgetc(fp);
    }

    find_all_low_points(matrix);

    qsort(basins, basin_count+1, sizeof(int), &compare);

    printf("largest 3 basins: %d\n", basins[0]*basins[1]*basins[2]);

    return 0;
}
