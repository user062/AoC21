#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POINTS 791
#define LINES 895
#define COLS  1308

int matrix[LINES][COLS] = {0};

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input13", "r");
    int x, y, count = 0, new_x;
    char buffer[11];

    for (int i = 0; i < POINTS; i++) {
        fgets(buffer, 11, fp);
        buffer[strcspn(buffer, "\n")] = '\0';
        x = atoi(strtok(buffer, ","));
        y = atoi(strtok(NULL, ","));
        matrix[y][x] = 1;
    }

    for (int i = 655 + 1; i < COLS; i++)

        for (int j = 0; j < LINES; j++)
            if(matrix[j][i]) {
                new_x = i - 2*(i - 655);
                matrix[j][new_x] = matrix[j][i];
                matrix[j][i] = 0;
            }

    for (int i = 0; i < LINES; i++)

        for (int j = 0; j < COLS; j++)
            if (matrix[i][j])
                count++;

    printf("number of points after the first fold: %d\n", count);

    return 0;
}
