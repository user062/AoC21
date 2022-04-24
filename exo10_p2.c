#include <stdio.h>
#include <stdlib.h>

#define LINES 106
#define COLS 110

typedef enum {round, square, curly, angle} type; //names taken from wiki

int compare(const void *a, const void *b) {
    if (*(long*)a > *(long*)b)
        return 1;

    if (*(long*)a < *(long*)b)
        return -1;

    return 0;
}

int main(int argc, char *argv[])
{
    char matrix[LINES][COLS], stack[COLS];

    FILE *fp = fopen("input10", "r");

    char c;

    for (int i = 0; i < LINES; i++) {

        for (int j = 0; j < COLS; j++) {
            c = fgetc(fp);

            if (c == '\n') {
                matrix[i][j] = '\0';
                break;
            }

            matrix[i][j] = c;
        }
    }

    int mismatch = 0, current = -1, score_index = -1;
    long score = 0, scores[LINES] = {0};

    for (int i = 0; i < LINES; i++) {

        mismatch = 0;
        current = -1;
        score = 0;

        for (int j = 0; matrix[i][j] != '\0'; j++) {

            switch(matrix[i][j]) {

            case '}':

                if (stack[current--] != '{') {
                    mismatch = 1;
                }

                break;

            case ')':

                if (stack[current--] != '(') {
                    mismatch = 1;
                };

                break;

            case ']':

                if (stack[current--] != '[') {
                    mismatch = 1;
                };

                break;

            case '>':

                if (stack[current--] != '<') {
                    mismatch = 1;
                };

                break;

            default:
                stack[++current] = matrix[i][j];
            }

            if (mismatch)
                break;
        }

        if (!mismatch) {
            stack[current+1] ='\0';

            for (int k = current ; k >= 0; k--) {
                score *= 5;
                
                switch(stack[k]) {
                case '[': score += 2; break;
                case '(': score += 1; break;
                case '{': score += 3; break;
                case '<': score += 4; break;
                }
            }
            
            scores[++score_index] = score;
        }
    }

    qsort(scores, score_index+1, sizeof(long), &compare);

    printf("middle score is: %ld\n", scores[score_index/2]);


    return 0;
}
