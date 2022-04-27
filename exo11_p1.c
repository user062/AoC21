#include <stdio.h>

#define LINES 10
#define COLS 10

typedef struct {int i; int j;} cords;

int increment_energy_level(int matrix[][COLS], int i_flashed, int j_flashed) {
    int flashes = 0;
    
    flashes++;
    
    if (i_flashed > 0 && matrix[i_flashed - 1][j_flashed] != 0) { // up
        matrix[i_flashed - 1][j_flashed]++;
        matrix[i_flashed - 1][j_flashed] %= 10;
        
        if (matrix[i_flashed - 1][j_flashed] == 0)
            flashes += increment_energy_level(matrix, i_flashed - 1, j_flashed);
    }
    
    if (i_flashed < LINES - 1 && matrix[i_flashed + 1][j_flashed] != 0) { // down
        matrix[i_flashed + 1][j_flashed]++;
        matrix[i_flashed + 1][j_flashed] %= 10;
        
        if (matrix[i_flashed + 1][j_flashed] == 0)
            flashes += increment_energy_level(matrix, i_flashed + 1, j_flashed);
    }
    
    if (j_flashed > 0 && matrix[i_flashed][j_flashed - 1] != 0) { // left
        matrix[i_flashed][j_flashed - 1]++;
        matrix[i_flashed][j_flashed - 1] %= 10;
        
        if (matrix[i_flashed][j_flashed - 1] == 0)
            flashes += increment_energy_level(matrix, i_flashed, j_flashed - 1);
    }
    
    if (j_flashed < COLS - 1 && matrix[i_flashed][j_flashed + 1] != 0) { // right
        matrix[i_flashed][j_flashed + 1]++;
        matrix[i_flashed][j_flashed + 1] %= 10;
        
        if (matrix[i_flashed][j_flashed + 1] == 0)
            flashes += increment_energy_level(matrix, i_flashed, j_flashed + 1);
    }
    
    if (i_flashed > 0 && j_flashed > 0 && matrix[i_flashed - 1][j_flashed - 1] != 0) { //upper left
        matrix[i_flashed - 1][j_flashed - 1]++;
        matrix[i_flashed - 1][j_flashed - 1] %= 10;
        
        if (matrix[i_flashed - 1][j_flashed - 1] == 0)
            flashes += increment_energy_level(matrix, i_flashed - 1, j_flashed - 1);
    }
    
    if (i_flashed > 0 && j_flashed < COLS - 1 && matrix[i_flashed - 1][j_flashed + 1] != 0) { // upper right
        matrix[i_flashed - 1][j_flashed + 1]++;
        matrix[i_flashed - 1][j_flashed + 1] %= 10;
        
        if (matrix[i_flashed - 1][j_flashed + 1] == 0)
            flashes += increment_energy_level(matrix, i_flashed - 1, j_flashed + 1);
    }
    
    if (i_flashed < LINES - 1 && j_flashed > 0 && matrix[i_flashed + 1][j_flashed - 1] != 0) { // lower left
        matrix[i_flashed + 1][j_flashed - 1]++;
        matrix[i_flashed + 1][j_flashed - 1] %= 10;
        
        if (matrix[i_flashed + 1][j_flashed - 1] == 0)
            flashes += increment_energy_level(matrix, i_flashed + 1, j_flashed - 1);
    }
    
    if (i_flashed < LINES - 1 && j_flashed < COLS - 1 && matrix[i_flashed + 1][j_flashed + 1] != 0) { // lower right
        matrix[i_flashed + 1][j_flashed + 1]++;
        matrix[i_flashed + 1][j_flashed + 1] %= 10;
        
        if (matrix[i_flashed + 1][j_flashed + 1] == 0)
            flashes += increment_energy_level(matrix, i_flashed + 1, j_flashed + 1);
    }
    
    return flashes;
}

void print_matrix(int matrix[][COLS]) {

    for (int i = 0; i < LINES; i++) {
        printf("[");

        for (int j = 0; j < COLS - 1; j++)
            printf("%d, ", matrix[i][j]);

        printf("%d]\n", matrix[i][COLS - 1]);
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    int matrix[LINES][COLS], number_of_zeros = -1;
    long flashes = 0;
    cords zeros[COLS*LINES];

    FILE *fp = fopen("input11", "r");


    for (int i = 0; i < LINES; i++) {

        for (int j = 0; j < COLS; j++)

            matrix[i][j] = fgetc(fp) - '0';
        fgetc(fp);
}
    for (int k = 0; k < 100; k++) {
        printf("step: %d\n", k);
        print_matrix(matrix);
        printf("\n");
        number_of_zeros = -1;

        for (int i = 0; i < LINES; i++)
            
            for (int j = 0; j < COLS; j++) {
                matrix[i][j]++;
                matrix[i][j] %= 10;

                if (matrix[i][j] == 0) {
                    cords i_j = {i, j};
                    zeros[++number_of_zeros] = i_j;
                }
            }
        
        for (int i = 0; i <= number_of_zeros; i++)
                    flashes += increment_energy_level(matrix, zeros[i].i, zeros[i].j);
    }

    printf("number of flahes: %ld\n", flashes);

    return 0;
}
