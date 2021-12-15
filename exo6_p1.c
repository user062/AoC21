#include <stdio.h>

#define VALUES 300
#define DAYS 80 

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input6", "r");
    int fish[1228800] = {0};
    long old_total = 0, total = VALUES;

    for(int i = 0; i < VALUES - 1; i++)
        fscanf(fi, "%d,", &fish[i]); 

    fscanf(fi, "%d\n", &fish[VALUES - 1]); 

    for (size_t i = 0; i < DAYS; i++) {
        old_total = total;

        for (long j = 0; j < old_total; j++)
            if (fish[j] > 0)
                fish[j]--;

            else {
                fish[j] = 6;
                fish[total++] = 8;
            }
    }

    printf("the number of fish is: %ld \n", total);
    return 0;
}
