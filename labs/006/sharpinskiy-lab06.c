#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char Name[30];
    char TELE[30];
    char DATE[30];
} noteInterface;

void sort(noteInterface *BLOCKNOTE, int n);
int isValidMonth(char *s);

int main() {
    const char *fileName = "index.csv";
    int i;
    int n = 9;
    int count = 0;
    char userInput[50];
    char month[3];
    noteInterface BLOCKNOTE[9];

    FILE *file = fopen(fileName, "r");
    if (file != NULL) {
        for (i = 0; i < 9; i++) {
            if (fscanf(file, "%29[^,],%29[^,],%29[^,\n]\n", BLOCKNOTE[i].Name, BLOCKNOTE[i].TELE, BLOCKNOTE[i].DATE) != 3) {
                n = i;
                i = 9;
            }
        }
        fclose(file);

        sort(BLOCKNOTE, n);

        printf("All users, sorted by name:\n");
        printf("| %-3s | %-30s | %-30s | %-30s |\n", "No", "Name", "Phone Number", "Date of Birth");
        printf("----------------------------------------------------------------------------------------------------------\n");

        for (i = 0; i < n; i++) {
            printf("| %-3d | %-30s | %-30s | %-30s |\n", i + 1, BLOCKNOTE[i].Name, BLOCKNOTE[i].TELE, BLOCKNOTE[i].DATE);
        }

        printf("\nEnter the month number (01, 02, ..., 11, 12) to see users born this month: ");
        scanf("%s", userInput);

        if (isValidMonth(userInput)) {
            for (i = 0; i < n; i++) {
                strncpy(month, BLOCKNOTE[i].DATE + 5, 2);
                month[2] = '\0';
                if (strcmp(month, userInput) == 0) {
                    count++;
                    printf("| %-3d | %-30s | %-30s | %-30s |\n", i + 1, BLOCKNOTE[i].Name, BLOCKNOTE[i].TELE, BLOCKNOTE[i].DATE);
                }
            }
            if (count == 0) {
                printf("It seems that none of the users were born in this month");
            }
        } else {
            printf("invalid month number\n");
        }
    } else {
        perror("failed to open file");
    }

    return 0;
}


void sort(noteInterface *BLOCKNOTE, int n)  {
    noteInterface tmp;
    int i, j;

    for(i = 0; i < n; i++) {
        tmp = BLOCKNOTE[i];
        for (j = i - 1; (j >= 0) && (BLOCKNOTE[j].Name[0] > tmp.Name[0]); j--) {
           BLOCKNOTE[j+1] = BLOCKNOTE[j];
        }
        BLOCKNOTE[j+1] = tmp;
    }
}

int isValidMonth(char *s) {

    return ((strlen(s) == 2) &&
        (s[0] == '1' && '0' <= s[1] && s[1] <= '2') ||
        (s[0] == '0' && '1' <= s[1] && s[1] <= '9'));
}
