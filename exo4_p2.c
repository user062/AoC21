#include <stdio.h>
#include <math.h>

#define MATRICES_NUMBER 100
#define ROWS 5
#define COLS 5
#define VALUES 100

typedef struct {int num; int selected;} bingo_num;
typedef bingo_num matrices[MATRICES_NUMBER][ROWS][COLS];

int selected_row(bingo_num matrix[ROWS][COLS], int row) {

    for (size_t i = 0; i < COLS; i++)
        if (!matrix[row][i].selected)
            return 0;

    return 1;
}

int selected_column(bingo_num matrix[ROWS][COLS], int col) {

    for (size_t i = 0; i < ROWS; i++)
        if (!matrix[i][col].selected)
            return 0;

    return 1;
}

int select_number(bingo_num matrix[ROWS][COLS], int picked_num) {
    
    for (size_t i = 0; i < COLS; i++)

        for (size_t j = 0; j < ROWS; j++)
            if (matrix[j][i].num == picked_num){
                matrix[j][i].selected = 1;
                return 1;
            }

    return 0;
}

int calculate_winning_matrix_value(bingo_num matrix[ROWS][COLS]) {
    int sum = 0;

    for (size_t i = 0; i < COLS; i++)

        for (size_t j = 0; j < ROWS; j++)
            if (!matrix[j][i].selected)
                sum += matrix[j][i].num;

    return sum;
}

int check_if_winning_matrix(bingo_num matrix[ROWS][COLS]) {

    for (size_t i = 0; i < ROWS; i++)
        if (selected_row(matrix, i) || selected_column(matrix, i))
            return 1;

    return 0;
}

void read_matrix_from_file(FILE *fi, matrices list, int index) {

    for (size_t i = 0 ; i < ROWS; i++){

        for (size_t j = 0; j < COLS - 1; j++) {
            fscanf(fi, "%d ", &list[index][i][j].num);
            list[index][i][j].selected = 0;
        }

        fscanf(fi, "%d\n", &(list[index][i][COLS - 1].num));
        list[index][i][COLS - 1].selected = 0;
    

    }
}

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input4", "r");
    int winning_value, vals[VALUES], winners[MATRICES_NUMBER] = {0};
    matrices bingos;
    

    for(int i = 0; i < VALUES - 1; fscanf(fi, "%d,", &vals[i++])); 
    fscanf(fi, "%d\n", &vals[VALUES-1]);

    for (size_t i = 0; i < MATRICES_NUMBER; i++)
        read_matrix_from_file(fi, bingos, i);

    for (size_t i = 0; i < VALUES; i++)

        for (size_t j = 0; j < MATRICES_NUMBER; j++)
            if(!winners[j] && select_number(bingos[j], vals[i]))
                if (check_if_winning_matrix(bingos[j])){
                    winners[j] = 1;
                    winning_value = calculate_winning_matrix_value(bingos[j]) * vals[i];
                }

    printf("the last winning value is: %d\n", winning_value);
    return 0;
}
