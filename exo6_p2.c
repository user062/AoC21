#include <stdio.h>
#include <stdlib.h>

#define VALUES 300

int calculate_fish_for_104_days(int age) {
    int *fish = malloc(sizeof(int)*16384);
    long old_total = 1, total = 1;
    fish[0] = age;

    for (size_t i = 0; i < 104; i++) {
        old_total = total;

        for (long j = 0; j < old_total; j++)
            if (fish[j] > 0)
                fish[j]--;

            else {
                fish[j] = 6;
                fish[total++] = 8;
            }
    }

    free(fish);

    return total;
    
}

static int fish[629145600] = {0};

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input6", "r");
    long long old_total = 0, total = VALUES, fish_for_104_days[9] = {0};

    for(int i = 0; i < VALUES - 1; i++)
        fscanf(fi, "%d,", &fish[i]); 

    fscanf(fi, "%d\n", &fish[VALUES - 1]); 

    for (size_t i = 0; i < 152; i++) {
        old_total = total;

        for (long j = 0; j < old_total; j++)
            if (fish[j] > 0)
                fish[j]--;

            else {
                fish[j] = 6;
                fish[total++] = 8;
            }
    }

    old_total = total;

    for (size_t i = 0; i <= 8; i++)
        fish_for_104_days[i] = calculate_fish_for_104_days(i) - 1;

    for (long long j = 0; j < old_total; j++) {
        total += fish_for_104_days[fish[j]];
    } 

    printf("the number of fish is: %lld \n", total);
    return 0;
}
