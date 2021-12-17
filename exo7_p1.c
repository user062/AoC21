#include <stdio.h>
#include <stdlib.h>

#define VALUES 1000

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input7", "r");
    int positions[VALUES], old_fuel, fuel = 0;

    for(int i = 0; i < VALUES - 1; i++)
        fscanf(fi, "%d,", &positions[i]); 

    fscanf(fi, "%d\n", &positions[VALUES - 1]); 


    for (int j = 0; j < VALUES; j++)
        fuel += abs(positions[j] - 0);

    old_fuel = fuel;
    fuel = 0;

    for (int i = 1 ; i < VALUES; i++) {
    
        for (int j = 0; (j < VALUES) && (fuel <= old_fuel); j++)
            fuel += abs(positions[j] - i);

        if (fuel < old_fuel)
            old_fuel = fuel;

        fuel = 0;
    }

    printf("the total fuel cost is: %d \n", old_fuel);
    return 0;
}
