#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VALUES 200 
#define WORDS  4

int char_included(char  c, char * number) {

    for (size_t i = 0; number[i] != '\0'; i++)
        if (number[i] == c)
            return 1;

    return 0;
    
}

int included(char * number1, char * number2) {

    for (size_t i = 0; number1[i] != '\0'; i++)
        if (!char_included(number1[i], number2))
            return 0;

    if (number1[0] == '\0')
        return 0;

    return 1;
    
}

char * difference(char * number1, char * number2) {
    char *intersection = malloc(sizeof(char)*strlen(number1));
    size_t j = 0;

    for (size_t i = 0; number1[i] != '\0'; i++)
        if (!char_included(number1[i], number2))
            intersection[j++] = number1[i];

    intersection[j] = '\0';

    return intersection; 
}

int get_digit(char *seven_segments, char digits[10][8]) {

    for (size_t i = 0; i < 10; i++) 
        if (included(seven_segments, digits[i]) && included(digits[i], seven_segments)){
            return i;
        }

    return -1;
}

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input8", "r");
    char lines[VALUES * 4][8] = {{'\0'}}, input[VALUES * 10][8], seek[82], digits[10][8] = {{'\0'}};
    size_t index = 0;
    long long number = 0;

    for(size_t i = 0; i < VALUES; i++) {
        fgets(seek, 62, fi); 
        fscanf(fi,"%*[|]");
        //printf("%s", seek);

        strcpy(input[i*10], strtok(seek, " "));
        printf("%s ", input[i*10]);

        for (int k = 1; k < 10; k++) {
            strcpy(input[i*10+k], strtok(NULL, " "));
            printf("%s ", input[i*10+k]);
        }

        printf("| ");

        for (size_t j = 0; j < WORDS - 1; j++) {
            fscanf(fi,"%s", lines[index++]);
            printf("%s ", lines[index-1]);
        }

        fscanf(fi,"%s\n", lines[index++]);
        printf("%s\n", lines[index-1]);
    }


    //digits
    for (size_t line = 0; line < VALUES; line++) {

       for (size_t k = 0; k < 4; k++)
        
           for (size_t i = 0; i < 10; i++) {
               
               switch (strlen(input[line*10+i])) {
                   
               case 2:
                   strcpy(digits[1], input[line*10+i]);
                   break;
                   
               case 3:
                   strcpy(digits[7], input[line*10+i]);
                   break;
                   
               case 4:
                   strcpy(digits[4], input[line*10+i]);
                   break;
                   
               case 5:
                   if(digits[5][0] != '\0' && digits[6][0] != '\0' && digits[2][0] == '\0') {
                       if (included(difference(digits[6], digits[5]), input[line*10+i])) {
                           strcpy(digits[2], input[line*10+i]);
                           break;
                       }
                   }
                   
                   if (digits[7][0] != '\0' && digits[3][0] == '\0')
                       if (included(digits[7], input[line*10+i])) {
                           strcpy(digits[3], input[line*10+i]);
                           break;
                       }
                   
                   if (digits[9][0] != '\0' && digits[1][0] != '\0' && digits[5][0] == '\0')
                       if (included(difference(digits[9], input[line*10+i]), digits[1])) {
                           strcpy(digits[5], input[line*10+i]);
                           break;
                       }
                   
                   break;
                   
               case 6:
                   if (digits[4][0] != '\0' && digits[9][0] == '\0') {
                       if (included(digits[4], input[line*10+i])) {
                           strcpy(digits[9], input[line*10+i]);
                           break;
                       }
                   }
                   
                   if (digits[6][0] != '\0' && digits[5][0] != '\0' && digits[0][0] == '\0') {
                       if (included(difference(digits[6], digits[5]), input[line*10+i]) &&
                           !included(digits[6], input[line*10+i])) {
                           strcpy(digits[0], input[line*10+i]);
                           break;
                       }
                   }
                   
                   if (digits[1][0] != '\0' && digits[8][0] != '\0' && digits[6][0] == '\0') {
                       if (included(difference(digits[8], input[line*10+i]), digits[1])) {
                           strcpy(digits[6], input[line*10+i]);
                           break;
                       }
                   }
                   
                   break;
                   
               case 7:
                   strcpy(digits[8], input[line*10+i]);
                   break;
               }
           }

        number += get_digit(lines[line*4], digits)*1000 +
                  get_digit(lines[line*4+1], digits)*100 +
                  get_digit(lines[line*4+2], digits)*10 +
                  get_digit(lines[line*4+3], digits);

        memset(digits, '\0', 80);
    }

    printf("the sum of all outputs is: %llu \n", number);

    return 0;
}
