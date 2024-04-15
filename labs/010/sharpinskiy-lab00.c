#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 256
#define OPTION_1 "Print all profession"
#define OPTION_2 "Select profession and reverse list"

typedef struct professionStruct {
    int id;
    char name[MAXLEN];
    struct professionStruct* next;
} Profession;

typedef struct professionHeadStruct {
    Profession* first;
    Profession* last;
    int count;
} ProfessionHead;

void appOption(ProfessionHead* pHead, int option);
void appGUI(ProfessionHead* pHead);
void reverseListGUI(ProfessionHead* pHead);

ProfessionHead* makeProfessionHead();
Profession* makeProfessionNode(char name[MAXLEN]);
void pushBackProfessionNode(ProfessionHead* head, Profession* profession);
void freeProfessionList(ProfessionHead* head);
void readProfessions(char* filename, ProfessionHead* head);
void pushFrontProfessionNode(ProfessionHead* head, Profession* profession);
ProfessionHead* makeReversedListWithNoID(ProfessionHead* head, int id);
Profession* findProfessionById(ProfessionHead* head, int id);

void trim(char str[MAXLEN]);
void clearStdin();

void printMenu();
void printProfessionHeader();
void printAllProfessions(ProfessionHead* head);
void printOptionHeader(const char* optionDescription);
void pressEnterToContinue();
void clearConsole();
void trimForDisplay(char *output, const char *input, int maxLength);
void printProfession(Profession *profession);
void printShortLine();

int main() {
    ProfessionHead* pHead = NULL;

    pHead = makeProfessionHead();

    if (pHead != NULL) {
        appGUI(pHead);
        freeProfessionList(pHead);
    } else {
        perror("Memory allocation failed");
    }

    return 0;
}

void appGUI(ProfessionHead* pHead) {
    int option;

    readProfessions("professions.csv", pHead);

    do {
        clearConsole();
        printMenu();
        scanf("%d", &option);
        clearStdin();
        if (option != 0) {
            appOption(pHead, option);
        } else {
            clearConsole();
        }
    } while (option != 0 && option != 2);
}

void appOption(ProfessionHead* professionHead, int option) {
    clearConsole();
    switch (option) {
        case 1:
            printOptionHeader(OPTION_1);
            printAllProfessions(professionHead);
            break;
        case 2:
            printOptionHeader(OPTION_2);
            reverseListGUI(professionHead);
            break;
        default:
            clearConsole();
            printf("\nFailed: invalid option\n");
            break;
    }
    pressEnterToContinue();
}

void reverseListGUI(ProfessionHead* pHead) {
    ProfessionHead* newPhead = NULL;
    Profession* profession = NULL;
    int id;

    if (pHead->first != NULL) {
        printAllProfessions(pHead);
        printf("Choose profession id (after this, this element will be removed from the list,\n");
        printf("and a new list will be created with the order of elements reversed)\n\n");
        printf("ID: ");
        scanf("%d", &id);
        clearStdin();
        profession = findProfessionById(pHead, id);
        if (profession == NULL) {
            printf("\nFailed: there is no profession with id %d\n", id);
        } else {
            printf("\nProfession with id %d:\n", id);
            printProfessionHeader();
            printProfession(profession);
            printShortLine();
            printf("\nReversed list:\n");
            newPhead = makeReversedListWithNoID(pHead, id);
            if (newPhead != NULL) {
                printAllProfessions(newPhead);
                freeProfessionList(newPhead);
            } else {
                printf("\nFailed: memory allocation failed\n");
            }
        }
    }
}

ProfessionHead* makeProfessionHead() {
    ProfessionHead* head = NULL;

    head = (ProfessionHead*)malloc(sizeof(ProfessionHead));
    if (head != NULL) {
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
    } else {
        perror("Memory allocation failed");
    }

    return head;
}

Profession* makeProfessionNode(char name[MAXLEN]) {
    Profession* profession = NULL;

    profession = (Profession*)malloc(sizeof(Profession));

    if (profession != NULL) {
        profession->id = 0;
        strcpy(profession->name, name);
        profession->next = NULL;
    }

    return profession;
}

void pushBackProfessionNode(ProfessionHead* head, Profession* profession) {
    head->count++;

    if (head->first == NULL) {
        head->first = profession;
        head->last = profession;
        profession->id = 1;
    } else {
        profession->id = head->last->id + 1;
        head->last->next = profession;
        head->last = profession;
    }
    profession->next = head->first;
}

void freeProfessionList(ProfessionHead* head) {
    Profession *temp1, *temp2;
    int i;

    temp1 = head->first;
    for (i = 0; i < head->count; i++) {
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }

    free(head);
}

void readProfessions(char* filename, ProfessionHead* head) {
    FILE* file;
    Profession* profession;
    int n, count, i;
    char temp[MAXLEN] ={0};

    profession = NULL;
    n = count = 0;
    file = fopen(filename, "r");

    if (file != NULL) {
        while ((fgets(temp, MAXLEN, file)) != NULL) n++;
        rewind(file);

        for (i = 0; i < n; i++) {
            fgets(temp, MAXLEN, file);
            trim(temp);
            profession = makeProfessionNode(temp);
            if (profession != NULL) {
                pushBackProfessionNode(head, profession);
                count++;
            }
        }
        fclose(file);
    } else {
        perror("Failed to open file");
    }

    if (count != n) {
        perror("Failed to read from file");
        freeProfessionList(head);
    }
}

void pushFrontProfessionNode(ProfessionHead* head, Profession* profession) {
    head->count++;

    if (head->first == NULL) {
        head->first = profession;
        head->last = profession;
        profession->id = 1;
    } else {
        profession->id = head->first->id + 1;
        profession->next = head->first;
        head->first = profession;
    }
}

ProfessionHead* makeReversedListWithNoID(ProfessionHead* head, int id) {
    ProfessionHead* newHead = NULL;
    Profession* current = head->first;
    Profession* newNode;
    int i;

    newHead = makeProfessionHead();

    if (newHead != NULL && current != NULL) {
        for (i = 0; i < head->count; i++) {
            if (current->id != id) {
                newNode = makeProfessionNode(current->name);
                if (newNode != NULL) {
                    pushFrontProfessionNode(newHead, newNode);
                    current = current->next;
                } else {
                    i = head->count;
                }
            } else {
                current = current->next;
            }
        }
    }

    return newHead;
}

Profession* findProfessionById(ProfessionHead* head, int id) {
    Profession* temp = NULL;
    int i, isFound = 0;

    if (id > 0 && id <= head->count) {
        temp = head->first;
        for (i = 0; i < head->count && !isFound; i++) {
            if (temp->id == id) {
                isFound = 1;
            } else {
                temp = temp->next;
            }
        }
        if (!isFound) {
            temp = NULL;
        }
    }

    return temp;
}

void trim(char str[MAXLEN]) {
    int i, flag = 0;
    str[MAXLEN - 1] = '\0';
    for (i = 0; str[i] != '\0' && !flag; i++) {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            flag = 1;
        }
    }
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void printMenu() {
    printShortLine();
    printf("|                  Choose an option                |\n");
    printf("|--------------------------------------------------|\n");
    printf("| 0. Exit                                          |\n");
    printf("| 1. Print all professions                         |\n");
    printf("| 2. Select profession and reverse list            |\n");
    printShortLine();
    printf("Option: ");
}

void printProfessionHeader() {
    printShortLine();
    printf("| ID |                  Name                       |\n");
    printf("|----|---------------------------------------------|\n");
}

void printAllProfessions(ProfessionHead* head) {
    Profession *q;
    int i;

    printProfessionHeader();
    q = head->first;
    for (i = 0; i < head->count; i++) {
        printProfession(q);
        q = q->next;
    }
    printShortLine();
}

void printProfession(Profession *profession) {
    char trimmedProfessionName[32];
    trimForDisplay(trimmedProfessionName, profession->name, 31);
    printf("| %-2d | %-43s |\n", profession->id, trimmedProfessionName);
}

void printShortLine() {
    printf("====================================================\n");
}

void printOptionHeader(const char* optionDescription) {
    printShortLine();
    printf("| Option: %-40s |\n", optionDescription);
    printShortLine();
    printf("\n");
}

void pressEnterToContinue() {
    printf("\nPress ENTER to continue ");
    clearStdin();
    clearConsole();
}

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void trimForDisplay(char *output, const char *input, int maxLength) {
    if (strlen(input) > maxLength) {
        strncpy(output, input, maxLength - 3);
        output[maxLength - 3] = '\0';
        strcat(output, "...");
    } else {
        strcpy(output, input);
    }
}
