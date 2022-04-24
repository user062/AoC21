#include <stdio.h>

#define LINES 106
#define COLS 110

typedef enum {round, square, curly, angle} type; //names taken from wiki

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

    int error_score = 0, mismatch = 0, current = -1;

    for (int i = 0; i < LINES; i++) {

        mismatch = 0;
        current = -1;

        for (int j = 0; matrix[i][j] != '\0'; j++) {

            switch(matrix[i][j]) {

            case '}':

                if (stack[current--] != '{') {
                    error_score += 1197;
                    mismatch = 1;
                }

                break;

            case ')':

                if (stack[current--] != '(') {
                    error_score += 3;
                    mismatch = 1;
                };

                break;

            case ']':

                if (stack[current--] != '[') {
                    error_score += 57;
                    mismatch = 1;
                };

                break;

            case '>':

                if (stack[current--] != '<') {
                    error_score += 25137;
                    mismatch = 1;
                };

                break;

            default:
                stack[++current] = matrix[i][j];
            }

            if (mismatch) {
                break;
            }
        }
    }

    printf("error count is: %d\n", error_score);


    return 0;
}
