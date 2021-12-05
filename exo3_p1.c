#include <stdio.h>
#include <math.h>

int filter_by_bit_criteria(char** report) {
    
    int common_bit = 0;

    for (int i = 0; i < 12; i++) {
        common_bit = 0;

        for (int j = 0; j < 1000; j++)
            if (report[j][i] == '1')
                common_bit++;
    }
}

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input3", "r");

    char report[1000][12];
    int report_filtered[1000];
    int common_bit = 0, gamma_rate = 0, epsilon_rate = 0, i = 0, k = -1;

    while(fscanf(fi, "%s", report[i++]) == 1);    

    for (int j = 0; j < 1000; j++)
        if (report[j][0] == '1')
            common_bit++;

    common_bit = common_bit > 1000/2;

    for (int j = 0; j < 1000; j++)
        if (report[j][0] == common_bit)
            report_filtered[++k] = j;

    while (k > 1) {
        
        for (int i = 1; i < 12; i++) 
            for (int j = 0; j < 1000; j++)
                if (report[j][i] == '1')
                    common_bit++;
        common_bit = common_bit > 1000/2;

        for (int j = 0; j < 1000; j++)
            if (report[j][i] != common_bit)
                for (int i = 0; i ; increment) {

                }
                report_filtered[++k] = j;
        
    }

    printf("the power consumption is: %d\n", gamma_rate * epsilon_rate);
    return 0;
}
