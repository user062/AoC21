#include <stdio.h>
#include <string.h>

#define VALUES 200 
#define WORDS  4

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input8", "r");
    char lines[VALUES * 4][8] = {{'\0'}}, seek[82];
    size_t index = 0, count = 0, len = 0;

    for(size_t i = 0; i < VALUES; i++) {
        fgets(seek, 62, fi); 
        fscanf(fi,"%*[|]");
        printf("%s", seek);

        for (size_t j = 0; j < WORDS - 1; j++) {
        fscanf(fi,"%s", lines[index++]);
        printf("%s ", lines[index-1]);
        }

        fscanf(fi,"%s\n", lines[index++]);
        printf("%s\n", lines[index-1]);
    }

    for (size_t i = 0; i < index; i++) {
        len = strlen(lines[i]);

        if( len == 2 || len  == 3 ||
            len == 4 || len == 7)
            count++;
}
    printf("the total number of unique digits is: %d \n", count);
    return 0;
}
