#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input2", "r");

    char cmd[7];
    int arg, hor = 0, depth = 0, aim = 0;

    while(fscanf(fi, "%s %d", cmd, &arg) == 2) {
        if (!strcmp(cmd, "forward")) {
            hor += arg;
            depth += aim * arg;
        }
        else if (!strcmp(cmd, "down"))
            aim += arg;
        else
            aim -= arg;
    } 
    
    printf("the final position is: %d\n", hor * depth);
    return 0;
}
