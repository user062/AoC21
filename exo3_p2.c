#include <stdio.h>
#include <math.h>

#define BITS_NUMBER 1000

int get_common_bit(char report[][12], int indexes[], size_t size, int bit) {
    
    int common_bit = 0;

    for (size_t j = 0; j < size; j++)
        if (report[indexes[j]][bit] == '1')
            common_bit++;

    return 2*common_bit >= size;
}

int filter_by_common_bit(char original_report[][12], int report[], size_t size,
                          int common_bit, int filter_bit) {
    size_t counter = 0, i = 0;
    char common_bit_c;

    if (common_bit)
        common_bit_c = '1';
    else
        common_bit_c = '0';

    while (counter++ < size)
        if (original_report[report[i]][filter_bit] != common_bit_c) 
            for (size_t j = i; j < size - 1; j++)
                report[j] = report[j+1];
        else
            i++;

    return i;
}

int bin_to_dec(char bin_num[], size_t size){
    int number = 0;

    for (size_t i = 0 ; i < size; i++){
        if (bin_num[i] == '1')
            number += exp2(size - i - 1);
    }
    return number;
}

int main(int argc, char *argv[])
{
    FILE *fi  = fopen("input3", "r");

    char report[BITS_NUMBER][12];
    int oxygen_values, co2_values, common_bit_oxygen = 0, common_bit_co2 = 0, oxygen_rating = 0, co2_rating = 0, i = 0, filtered_report_common[BITS_NUMBER], filtered_report_uncommon[BITS_NUMBER];

    while(fscanf(fi, "%s\n", report[i++]) == 1);    

    for (size_t i = 0; i < BITS_NUMBER; i++) {
        filtered_report_common[i] = i;
        filtered_report_uncommon[i] = i;
    }

    common_bit_oxygen = get_common_bit(report, filtered_report_common, BITS_NUMBER, 0);
    common_bit_co2 = common_bit_oxygen;
    oxygen_values = filter_by_common_bit(report, filtered_report_common, BITS_NUMBER, common_bit_oxygen, 0);

    i = 1;

    while (oxygen_values > 1) {
        common_bit_oxygen = get_common_bit(report, filtered_report_common, oxygen_values, i);
        oxygen_values = filter_by_common_bit(report, filtered_report_common, oxygen_values, common_bit_oxygen, i);
        i++;
    }

    i = 1;

    co2_values = filter_by_common_bit(report, filtered_report_uncommon, BITS_NUMBER, !common_bit_co2, 0);

    while (co2_values > 1) {
        common_bit_co2 = get_common_bit(report, filtered_report_uncommon, co2_values, i);
        co2_values = filter_by_common_bit(report, filtered_report_uncommon, co2_values, !common_bit_co2, i);
        i++;
    }
    oxygen_rating = bin_to_dec(report[filtered_report_common[0]], 12) ;
    co2_rating = bin_to_dec(report[filtered_report_uncommon[0]], 12);

    printf("the life support rating is: %d\n", oxygen_rating * co2_rating);
    return 0;
}
