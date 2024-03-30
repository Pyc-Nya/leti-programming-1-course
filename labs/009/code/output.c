#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "user.h"
#include "profession.h"
#include "gui.h"
#include "utils.h"
#include "output.h"

#define MAXLEN 256

void printMenu() {
    printShortLine();
    printf("|           Choose an option           |\n");
    printf("|--------------------------------------|\n");
    printf("| 0. Exit                              |\n");
    printf("| 1. Print all users                   |\n");
    printf("| 2. Print all professions             |\n");
    printf("| 3. Print full user data              |\n");
    printf("| 4. Add new profession                |\n");
    printf("| 5. Add new user                      |\n");
    printf("| 6. Update user data                  |\n");
    printf("| 7. Filter users                      |\n");
    printf("| 8. Sort users                        |\n");
    printf("| 9. Delete profession before id       |\n");
    printf("| 10. Delete user                      |\n");
    printf("| 11. Clear user list                  |\n");
    printf("| 12. Clear profession list            |\n");
    printShortLine();
    printf("Option: ");
}

void printProfessionHeader() {
    printShortLine();
    printf("| ID |            Name                 |\n");
    printf("|----|---------------------------------|\n");
}

void printAllProfessions(ProfessionHead* head) {
    Profession *q;

    printProfessionHeader();
    q = head->first;
    while (q != NULL) {
        printProfession(q);
        q = q->next;
    }
    printShortLine();
}

void printUserHeader() {
    printLongLine();
    printf("| ID |       Full Name        | Age |    Profession    | Friends Rating | Public Rating | Friends count |      Friends IDs      |\n");
    printf("|----|------------------------|-----|------------------|----------------|---------------|---------------|-----------------------|\n");
}


void printAllUsers(UserHead* uHead) {
    User *q;

    printUserHeader();
    q = uHead->first;
    while (q != NULL) {
        printUser(q);
        q = q->next;
    }
    printLongLine();
}

void printLongLine() {
    printf("=================================================================================================================================\n");
}

void printShortLine() {
    printf("========================================\n");
}

void printOptionHeader(const char* optionDescription) {
    printShortLine();
    printf("| Option: %-28s |\n", optionDescription);
    printShortLine();
    printf("\n");
}

void pressEnterToContinue() {
    printf("\nPress ENTER to continue ");
    getchar();
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

void printUser(User *user) {
    char friendsIds[MAXLEN] = "";
    char idStr[10];
    int i;
    char profession[MAXLEN] = "undefined";
    char trimmedFullName[23], trimmedProfession[17], trimmedFriendsIds[30];

    if (user->profession != NULL) {
        trimForDisplay(profession, user->profession->name, sizeof(profession));
    }

    for (i = 0; i < user->friendsCount; i++) {
        sprintf(idStr, "%d", user->friendsId[i]);
        strcat(friendsIds, idStr);
        if (i < user->friendsCount - 1) {
            strcat(friendsIds, ", ");
        }
    }

    trimForDisplay(trimmedFullName, user->fullName, 22);
    trimForDisplay(trimmedProfession, profession, 16);
    trimForDisplay(trimmedFriendsIds, friendsIds, 21);

    printf("| %-2d | %-22s | %-3d | %-16s | %-14.1f | %-13.1f | %-13d | %21s |\n",
           user->id, trimmedFullName, user->age, trimmedProfession, user->friendsRating, user->publicRating, user->friendsCount, trimmedFriendsIds);
}

void printProfession(Profession *profession) {
    char trimmedProfessionName[32];
    trimForDisplay(trimmedProfessionName, profession->name, 31);
    printf("| %-2d | %-31s |\n", profession->id, trimmedProfessionName);
}

