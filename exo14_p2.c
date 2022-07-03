#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RULES_NBR 100 

typedef struct {const char *mol; char added_char; unsigned long long counter; unsigned long long occurences_next;} rule;

char polymer[30] = {0};
rule rules[RULES_NBR];
unsigned long long elements[90] = {0};

void print_rules() {

    for (int i = 0; i < RULES_NBR; i++)
        printf("{%s, %llu}\n", rules[i].mol, rules[i].counter);
}

void count_occurences() {

    for (int i = 0; i < RULES_NBR; i++) {
        elements[rules[i].mol[0]] += rules[i].counter;
        elements[rules[i].mol[1]] += rules[i].counter;
    }

}

void count(int steps) {
    char new_mol[3] = {0}, new_mol2[3] = {0};
    int existing_rules[RULES_NBR], count;

    for(int step = 0; step < steps; step++) {
        count = 0;

        for (int i = 0; i < RULES_NBR; i++) {
            if (rules[i].counter > 0) {
                existing_rules[count++] = i;
            }
        }

       for (int i = 0; i < count; i++) {
           new_mol[0]  = rules[existing_rules[i]].mol[0];
           new_mol[1]  = rules[existing_rules[i]].added_char;
           new_mol2[0] = rules[existing_rules[i]].added_char;
           new_mol2[1] = rules[existing_rules[i]].mol[1];
           
           for (int j = 0; j < RULES_NBR; j++)
               if (!strcmp(new_mol, rules[j].mol) || !strcmp(new_mol2, rules[j].mol)) {
                   rules[j].occurences_next += rules[existing_rules[i]].counter;
               }
       }

       for (int i = 0; i < RULES_NBR; i++) {
           rules[i].counter = rules[i].occurences_next;
           rules[i].occurences_next = 0;
       }

    }
}

int main(int argc, char *argv[])
{
    char buffer[25] = {0}, *c;

    FILE *fp = fopen("input14", "r");

    fgets(polymer, 29, fp);
    polymer[strcspn(polymer, "\n")] = '\0';

    fgets(buffer, 2, fp);

    for(int i = 0; i < RULES_NBR; i++) {
        fgets(buffer, 9, fp);
        buffer[strcspn(buffer, "\n")] = '\0';
        c = malloc(2*sizeof(char));
        strcpy(c, strtok(buffer, " -> "));
        rules[i] = (rule) {c, strtok(NULL, " -> ")[0], 0, 0};
    }

    fclose(fp);

    buffer[2] = '\0';
    printf("%s\n", polymer);
    
    for (int i = 0; i < strlen(polymer) - 1; i++) {
        buffer[0] = polymer[i];
        buffer[1] = polymer[i+1];

        for (int j = 0; j < RULES_NBR; j++) {
            if (!strcmp(rules[j].mol, buffer)) {
                rules[j].counter++;
                break;
                
            }
        }
    }

    count(40);

    count_occurences();

    for (int i = 0; i < 90; i++)
        if (elements[i] > 0)
            printf("%c: %llu\n", i, elements[i]);

    printf("V:%llu - C:%llu = %llu\n", elements['V']/2, 1+(elements['C']-1)/2, elements['V']/2 - (1+(elements['C']-1)/2));

    return 0;
}
