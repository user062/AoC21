#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RULES_NBR 100

typedef struct {const char *mol; char added_char;} rule;

char polymer[1000000000] = {0};
rule rules[RULES_NBR];
char polymer_elements[26];

unsigned long max_min_diff() {
    
    char x, most_occured = polymer_elements[0], least_occured = polymer_elements[0];
    unsigned long global_max_counter = 0, global_min_counter = strlen(polymer), local_counter = 0;

    for (size_t c = 0; c < strlen(polymer_elements); c++) {
        x = polymer_elements[c];
        local_counter = 0;

        for (size_t i = 0; i < strlen(polymer); i++)
            if (x == polymer[i])
                local_counter++;

        if (local_counter > global_max_counter) {
            global_max_counter = local_counter;
            most_occured = x;
        }

        if (local_counter < global_min_counter) {
            global_min_counter = local_counter;
            least_occured = x;
        }
    }

    printf("most occured : %c (%lu) - least occured %c (%lu) = %lu\n", most_occured, global_max_counter, least_occured, global_min_counter, global_max_counter - global_min_counter);

    return global_max_counter - global_min_counter;
}

void transform_polymer(int steps) {
    char rule_[2] = {0};

    for (int i = 0; i < steps; i++) {

        printf("step %d\n", i+1);
        printf("strlen(polymer) %lu\n", strlen(polymer));

        for (size_t j = 0; j < strlen(polymer) - 1; j++) {
            rule_[0] = polymer[j];
            rule_[1] = polymer[j+1];

            for (int l = 0; l < RULES_NBR; l++)
                if (!strcmp(rule_, rules[l].mol)) {

                    for (size_t f = strlen(polymer); f > j + 1; f--)
                        polymer[f] = polymer[f-1];

                    polymer[j + 1] = rules[l].added_char;
                    j++;
                    break;
                }
        }
    }
}

void create_elements_list() {
    int counter = 0, already_exists;

   for (int i = 0; i < RULES_NBR; i++) {
       already_exists = 0;

       for (int j = 0; j < counter && !already_exists; j++)
           if (polymer_elements[j] == rules[i].added_char)
               already_exists = 1;

       if (!already_exists)
           polymer_elements[counter++] = rules[i].added_char;
   } 
}

int main(int argc, char *argv[])
{
    char buffer[11] = {0}, *c;

    FILE *fp = fopen("input14", "r");

    fgets(polymer, 22, fp);
    polymer[strcspn(polymer, "\n")] = '\0';

    fgets(buffer, 2, fp);

    for(int i = 0; i < RULES_NBR; i++) {
        fgets(buffer, 9, fp);
        buffer[strcspn(buffer, "\n")] = '\0';
        c = malloc(2*sizeof(char));
        strcpy(c, strtok(buffer, " -> "));
        rules[i] = (rule) {c, strtok(NULL, " -> ")[0]};
    }

    fclose(fp);

    create_elements_list();

    transform_polymer(10);

    max_min_diff();

    return 0;
}
