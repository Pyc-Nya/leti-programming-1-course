#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLEN 256

typedef struct professionStruct {
    int id;
    char name[MAXLEN];
    struct professionStruct* next;
    struct professionStruct* prev;
} Profession;

typedef struct professionHeadStruct {
    struct professionStruct* first;
    struct professionStruct* last;
    int count;
} ProfessionHead;

typedef struct userStruct {
    int id;
    char *fullName;
    int age;
    float friendsRating;
    float publicRating;
    int friendsCount;
    int friendsId[MAXLEN];
    struct professionStruct* profession;
    struct userStruct* next;
    struct userStruct* prev;
} User;

typedef struct userHeadStruct {
    struct userStruct* first;
    struct userStruct* last;
    int count;
} UserHead;

/** work with nodes */
ProfessionHead* makeProfessionHead();
UserHead* makeUserHead();
Profession* makeProfessionNode(char name[MAXLEN]);
User* makeUserNode(ProfessionHead* pHead, char** str);
void addProfessionNode(ProfessionHead* head, Profession* profession);
void addUserNode(UserHead* head, User* user);
void deleteProfessionById(ProfessionHead* head, UserHead* userHead, int id, int shouldLog);
void clearUserProfessionById(UserHead* head, int id);
void deleteProfession(ProfessionHead* head, UserHead* userHead);
void clearProfessionList(ProfessionHead* head, UserHead* userHead);
void freeProfessionList(ProfessionHead* head);
void freeUserStruct(User* user);
void freeUserList(UserHead* head);

/** utils */
void readProfessions(char filename[MAXLEN], ProfessionHead* head);
void readUsers(char filename[MAXLEN], UserHead* head, ProfessionHead* pHead);
void addProfession(ProfessionHead* head);
void nullString(char str[MAXLEN]);
void trim(char str[MAXLEN]);
char **split(char *str, int length, char sep);
void splitIntArray(User* user, char *str, char sep);
void fillIntArray(int arr[MAXLEN], int n);

/** output */
void printMenu();
void printProfessionHeader();
void printProfession(Profession *profession);
void printAllProfessions(ProfessionHead* my_head);
void printUserHeader();
void printAllUsers(UserHead* my_head);
void printUser(User* user);
void pressEnterToContinue();
void clearConsole();






int main() {
    UserHead* userHead = NULL;
    ProfessionHead* professionHead = NULL;
    char profFileName[MAXLEN];
    char userFileName[MAXLEN];

    int option;

    userHead = makeUserHead();
    professionHead = makeProfessionHead();

    strcpy(profFileName, "professions.csv");
    strcpy(userFileName, "users.csv");
    profFileName[MAXLEN - 1] = '\0';
    userFileName[MAXLEN - 1] = '\0';
    readProfessions(profFileName, professionHead);
    readUsers(userFileName, userHead, professionHead);

    do {
        clearConsole();
        printMenu();
        scanf("%d", &option);
        getchar();
        switch (option)
        {
        case 1:
            clearConsole();
            printAllUsers(userHead);
            pressEnterToContinue();
            break;
        case 2:
            clearConsole();
            printAllProfessions(professionHead);
            pressEnterToContinue();
            break;
        case 3:
            clearConsole();
            deleteProfession(professionHead, userHead);
            pressEnterToContinue();
            break;
        case 4:
            clearConsole();
            addProfession(professionHead);
            pressEnterToContinue();
            break;
        case 5:
            clearConsole();
            clearProfessionList(professionHead, userHead);
            pressEnterToContinue();
            break;
        case 6:
            clearConsole();
            break;
        default:
            break;
        }

    } while (option != 6);

    freeProfessionList(professionHead);
    freeUserList(userHead);

    return 0;
}






ProfessionHead* makeProfessionHead() {
    ProfessionHead* head = NULL;
    head = (ProfessionHead*)malloc(sizeof(ProfessionHead));
    if (head != NULL) {
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
    }
    return head;
}

UserHead* makeUserHead() {
    UserHead* head = NULL;
    head = (UserHead*)malloc(sizeof(UserHead));
    if (head != NULL) {
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
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
        profession->prev = NULL;
    }

    return profession;
}

User* makeUserNode(ProfessionHead* pHead, char** str) {
    User* user = NULL;
    Profession* q = NULL;

    user = (User*)malloc(sizeof(User));

    if (user != NULL) {
        user->fullName = str[0];
        user->age = atoi(str[1]);
        free(str[1]);
        user->profession = NULL;
        q = pHead->first;
        while (q != NULL && strcmp(q->name, str[2]) != 0) {
            q = q->next;
        }
        if (q != NULL) {
            user->profession = q;
        }
        free(str[2]);
        user->friendsRating = atof(str[3]);
        free(str[3]);
        user->publicRating = atof(str[4]);
        free(str[4]);
        user->friendsCount = atoi(str[5]);
        free(str[5]);

        splitIntArray(user, str[6], ',');
        free(str[6]);

        free(str);

        user->next = NULL;
        user->prev = NULL;
    }

    return user;
}

void addProfessionNode(ProfessionHead* head, Profession* profession) {
    head->count++;

    if (head->first == NULL) {                  /* list is empty */
        head->first = profession;               /* first element is profession */
        head->last = profession;                /* last element is profession */
        profession->id = head->count;

    } else  {                                   /* list has only one element */
        profession->prev = head->last;          /* profession's previous element is last element */
        head->last->next = profession;          /* profession becomes element after last element */
        head->last = profession;                /* profession becomes last element */
        profession->id = head->count;
    }
}

void addUserNode(UserHead* head, User* user) {
    head->count++;

    if (head->first == NULL) {
        head->first = user;
        head->last = user;
        user->id = head->count;

    } else  {
        user->prev = head->last;
        head->last->next = user;
        head->last = user;
        user->id = head->count;
    }
}

void deleteProfessionById(ProfessionHead* head, UserHead* userHead, int id, int shouldLog) {
    Profession* q = NULL;
    int isFound = 0;
    q = head->first;

    while (q != NULL && !isFound) {
        if (q->id == id) {

            if (q->prev != NULL) {
                q->prev->next = q->next;
            } else {
                head->first = q->next;
            }
            if (q->next != NULL) {
                q->next->prev = q->prev;
            } else {
                head->last = q->prev;
            }

            clearUserProfessionById(userHead, id);

            if (shouldLog) {
                printf("\nProfession with id %d:\n", id);
                printProfessionHeader();
                printProfession(q);
                printf("========================================\n");
                printf("\nSuccess: profession with id %d has been removed!\n", id);
            }
            free(q);
            head->count--;
            isFound = 1;
        } else {
            q = q->next;
        }
    }
}

void clearUserProfessionById(UserHead* head, int id) {
    User* q = NULL;
    q = head->first;

    while (q != NULL) {
        if (q->profession != NULL && q->profession->id == id) {
            q->profession = NULL;
        } else {
            q = q->next;
        }
    }
}

void deleteProfession(ProfessionHead* head, UserHead* userHead) {
    int id, i, isFound = 0;
    int idList[MAXLEN];
    Profession* q = NULL;

    q = head->first;
    if (q != NULL) {
        fillIntArray(idList, 0);
        i = 0;
        while (q != NULL) {
            idList[i++] = q->id;
            q = q->next;
        }

        printf("List of all professions:\n");
        printAllProfessions(head);

        printf("\nEnter profession id to delete profession before it (or 0 to return to menu): ");
        scanf("%d", &id);
        getchar();

        if (id > 0) {
            for (i = 0; i < MAXLEN && idList[i] != 0; i++) {
                if (idList[i] == id - 1) {
                    deleteProfessionById(head, userHead, id - 1, 1);
                    isFound = 1;
                    i = MAXLEN;
                }
            }
            if (!isFound) {
                printf("\nThere is no profession with id %d\n", id - 1);
            }
        }
    } else {
        printf("There are no professions in the list\n");
    }
}

void clearProfessionList(ProfessionHead* head, UserHead* userHead) {
    Profession *q, *q1;
    q = head->first;
    if (q == NULL) {
        printf("There are no profession in the list\n");
    } else {
        while (q != NULL) {
            q1 = q->next;
            deleteProfessionById(head, userHead, q->id, 0);
            q = q1;
        }
        head->first = NULL;
        head->last = NULL;
        head->count = 0;
        printf("Cleared!\n");
    }
}

void freeProfessionList(ProfessionHead* head) {
    Profession *q, *q1;
    q = head->first;
    while (q != NULL) {
        q1 = q->next;
        free(q);
        q = q1;
    }
    free(head);
}

void freeUserStruct(User* user) {
    if (user != NULL) {
        free(user->fullName);
        user->fullName = NULL;

        free(user);
    }
}

void freeUserList(UserHead* head) {
    User *q, *q1;
    /* there are two pointers here because we need to remember
    the next value of the structure we are going to free */
    q = head->first;
    while (q != NULL) {
        q1 = q->next;
        freeUserStruct(q);
        q = q1;
    }
    free(head);
}














void readProfessions(char filename[MAXLEN], ProfessionHead* head) {
    FILE* file;
    Profession* profession;
    int n, count, i;
    char temp[MAXLEN];

    profession = NULL;
    n = count = 0;
    file = fopen(filename, "r");

    if (file != NULL) {
        while ((fgets(temp, MAXLEN, file)) != NULL) n++;
        rewind(file);

        for (i = 0; i < n; i++) {
            nullString(temp);
            fgets(temp, MAXLEN, file);
            trim(temp);
            profession = makeProfessionNode(temp);
            if (profession != NULL) {
                addProfessionNode(head, profession);
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

void readUsers(char filename[MAXLEN], UserHead* head, ProfessionHead* pHead) {
    FILE* file;
    User* user;
    int n, count, i, slen;
    char** splitArray;
    char temp[MAXLEN];

    user = NULL;
    n = count = 0;
    file = fopen(filename, "r");

    if (file != NULL) {
        while ((fgets(temp, MAXLEN, file)) != NULL) n++;
        rewind(file);

        for (i = 0; i < n; i++, count++) {
            nullString(temp);
            fgets(temp, MAXLEN, file);
            slen = strlen(temp);
            trim(temp);
            splitArray = split(temp, slen, ';');
            if (splitArray != NULL) {
                user = makeUserNode(pHead, splitArray);
                if (user != NULL) {
                    addUserNode(head, user);
                }
            }
        }
        fclose(file);
    } else {
        perror("Failed to open file");
    }

    if (count != n) {
        perror("Failed to read from file");
        freeUserList(head);
    }
}

void addProfession(ProfessionHead* head) {
    char temp[MAXLEN];
    Profession* profession = NULL;

    printf("Enter profession name: ");
    scanf("%s", temp);
    getchar();
    profession = makeProfessionNode(temp);
    if (profession != NULL) {
        addProfessionNode(head, profession);
        printf("\nSuccess: profession added\n");
    } else {
        printf("\nFailed: memory error\n");
    }
}

void nullString(char str[MAXLEN]) {
    int i;
    for (i = 0; i < MAXLEN; i++) {
        str[i] = '\0';
    }
}

void trim(char str[MAXLEN]) {
    int i, flag = 0;
    str[MAXLEN - 1] = '\0';
    for (i = 0; str[i] != '\0' && !flag; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            flag = 1;
        }
    }
}

char **split(char *str, int length, char sep) {
    int count = 0;
    int i = 0;
    int start = 0;
    int j = 0;
    int wordLen = 0;
    char **result = NULL;
    char *newStr = NULL;
    int allocError = 0;

    for (i = 0; i < length; i++) {
        if (str[i] == sep) count++;
    }
    count++;

    result = malloc(count * sizeof(char *));
    if (result == NULL) {
        perror("Memory allocation failed");
    } else {
        for (i = 0; i < length; i++) {
            if (str[i] == ';' || str[i] == '\0') {
                wordLen = i - start;
                newStr = malloc((wordLen + 1) * sizeof(char));
                if (newStr == NULL) {
                    perror("Memory allocation failed");
                    allocError = 1;
                    i = length;
                } else {
                    strncpy(newStr, str + start, wordLen);
                    newStr[wordLen] = '\0';
                    result[j++] = newStr;
                    start = i + 1;
                }
            }
        }

        if (allocError) {
            for (i = 0; i < j; i++) {
                free(result[i]);
            }
            free(result);
            result = NULL;
        }
    }

    return result;
}

void splitIntArray(User* user, char *str, char sep) {
    int count = 0, cnt = 0;
    int start = 0;
    int i, len, flag, n;
    char tempStr[MAXLEN];

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == sep) cnt++;
    }
    cnt++;

    for (i = 0; i < user->friendsCount; i++) {
        user->friendsId[i] = 0;
    }

    flag = 1;

    for (i = 0; str[i] != '\0' && flag; i++) {
        if (str[i] == ',' || str[i + 1] == '\0') {
            len = (str[i] == ',') ? (i - start) : (i - start + 1);
            strncpy(tempStr, str + start, len);
            tempStr[len] = '\0';

            n = atoi(tempStr);

            user->friendsId[count++] = n;

            start = i + 1;
        }
    }

    if (!flag) {
        puts("It seems that among friends there is a user ID that is not in the database -> setting 0 friends automatically");
        user->friendsCount = 0;
    }

    if (count < user->friendsCount) {
        printf("It seems that the number of entered IDs does not correspond to the specified number of friends -> updating friends count: %d\n", count);
        user->friendsCount = count;
    }
}

void fillIntArray(int arr[MAXLEN], int n) {
    int i;
    for (i = 0; i < MAXLEN; i++) {
        arr[i] = n;
    }
}













void printMenu() {
    printf("======================================\n");
    printf("|          Choose an option          |\n");
    printf("|------------------------------------|\n");
    printf("| 1. Print all users                 |\n");
    printf("| 2. Print all professions           |\n");
    printf("| 3. Delete profession before id     |\n");
    printf("| 4. Add new profession              |\n");
    printf("| 5. Clear profession list           |\n");
    printf("| 6. Exit                            |\n");
    printf("======================================\n");
    printf("Option: ");
}

void printProfessionHeader() {
    printf("========================================\n");
    printf("| ID |            Name                 |\n");
    printf("|----|---------------------------------|\n");
}

void printProfession(Profession *profession) {
    printf("| %-2d | %-31s |\n", profession->id, profession->name);
}

void printAllProfessions(ProfessionHead* head) {
    Profession *q;

    printProfessionHeader();
    q = head->first;
    while (q != NULL) {
        printProfession(q);
        q = q->next;
    }
    printf("========================================\n");
}

void printUserHeader() {
    printf("==================================================================================================================\n");
    printf("| ID |       Full Name        | Age |    Profession    | Friends | Public Rating |          Friends IDs          |\n");
    printf("|----|------------------------|-----|------------------|---------|---------------|-------------------------------|\n");
}

void printUser(User *user) {
    int i;
    char friendsIds[MAXLEN] = "";
    char idStr[10];
    char temp[MAXLEN] = "None";
    if (user->profession != NULL) {
        strcpy(temp, user->profession->name);
    }

    for (i = 0; i < user->friendsCount; i++) {
        sprintf(idStr, "%d", user->friendsId[i]);
        strcat(friendsIds, idStr);
        if (i < user->friendsCount - 1) {
            strcat(friendsIds, ", ");
        }
    }

    printf("| %-2d | %-22s | %-3d | %-16s | %-7.1f | %-13.1f | %29s |\n",
           user->id, user->fullName, user->age, temp, user->friendsRating, user->publicRating, friendsIds);
}

void printAllUsers(UserHead* my_head) {
    User *q;

    printUserHeader();
    q = my_head->first;
    while (q != NULL) {
        printUser(q);
        q = q->next;
    }
    printf("==================================================================================================================\n");
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
