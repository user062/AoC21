#include <stdio.h>

#define LINES 100 
#define COLS 100

int total_height = 0;

int find_all_low_points(int matrix[][COLS]) {
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
                total_height += matrix[i][j] + 1;
        }

    return total_height;
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

    printf("total risk: %d\n", find_all_low_points(matrix));

    return 0;
}
