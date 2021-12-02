#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input1", "r");

    int a, b, count = 0;

    fscanf(fi, "%d", &a);

    while(fscanf(fi, "%d", &b) == 1) {
        if (b > a)
            count++;
        a = b;
    } 
    
    printf("the number of increases is: %d\n", count);
    return 0;
}
