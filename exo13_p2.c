#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POINTS 791
#define LINES 895
#define COLS  1308

typedef struct {char type; int pos;} fold;

int matrix[LINES][COLS] = {0};

void print_matrix(int matrix[][COLS], int end_line, int end_col) {

    for (int i = 0; i < end_line; i++) {
        printf("[");

        for (int j = 0; j < end_col - 1; j++)
            printf("%c", matrix[i][j]?'#':'.');

        printf("%c]\n", matrix[i][end_col - 1]?'#':'.');
    }

    printf("\n");
}

void fold_x_left(int matrix[][COLS], int pos, int end_line, int end_col) {
    int new_x;
    
    for (int i = pos + 1; i < end_col; i++)

        for (int j = 0; j < end_line; j++) {
            if(matrix[j][i]) {
                new_x = i - 2*(i - pos);
                matrix[j][new_x] = matrix[j][i];
                matrix[j][i] = 0;
            }
        }
}

void fold_y_up(int matrix[][COLS], int pos, int end_line, int end_col) {
    int new_y;

    for (int i = 0; i < end_col; i++)

        for (int j = pos + 1; j < end_line; j++) {
            if(matrix[j][i]) {
                new_y = j - 2*(j - pos);
                matrix[new_y][i] = matrix[j][i];
                matrix[j][i] = 0;
            }
        }
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen("input13", "r");
    int x, y, folds_nbr = 12, end_line = LINES, end_col = COLS;
    char buffer[11];
    fold folds[12];

    for (int i = 0; i < POINTS; i++) {
        fgets(buffer, 11, fp);
        buffer[strcspn(buffer, "\n")] = '\0';
        x = atoi(strtok(buffer, ","));
        y = atoi(strtok(NULL, ","));
        matrix[y][x] = 1;
    }

    folds[0]  = (fold) {'x', 655};
    folds[1]  = (fold) {'y', 447};
    folds[2]  = (fold) {'x', 327};
    folds[3]  = (fold) {'y', 223};
    folds[4]  = (fold) {'x', 163};
    folds[5]  = (fold) {'y', 111};
    folds[6]  = (fold) {'x', 81};
    folds[7]  = (fold) {'y', 55};
    folds[8]  = (fold) {'x', 40};
    folds[9]  = (fold) {'y', 27};
    folds[10] = (fold) {'y', 13};
    folds[11] = (fold) {'y', 6};

    for (int i = 0; i < folds_nbr ; i++) {
        if (folds[i].type == 'y') {
            fold_y_up(matrix, folds[i].pos, end_line, end_col);
            end_line = folds[i].pos;
        } 

        else {
            fold_x_left(matrix, folds[i].pos, end_line, end_col);
            end_col = folds[i].pos;
        }

    }

    print_matrix(matrix,end_line, end_col);

    return 0;
}
