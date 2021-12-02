#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input1", "r");

    int a, b, c, prev_sum, count = 0;

    fscanf(fi, "%d", &a);
    fscanf(fi, "%d", &b);
    fscanf(fi, "%d", &c);
    prev_sum = a + b + c;

    while(fscanf(fi, "%d", &c) == 1) {
        if ((a + b + c) > prev_sum)
            count++;
        prev_sum = a + b + c;
        a = b;
        b = c;
    } 
    
    printf("the number of increases is: %d\n", count);
    return 0;
}
