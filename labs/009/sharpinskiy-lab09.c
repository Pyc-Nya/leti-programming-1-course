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




/** program life cycle */
void app(ProfessionHead* pHead, UserHead* uHead);

/** work with nodes */
ProfessionHead* makeProfessionHead();
UserHead* makeUserHead();
Profession* makeProfessionNode(char name[MAXLEN]);
User* makeUserNode(ProfessionHead* pHead, char** str);
void addProfessionNode(ProfessionHead* head, Profession* profession);
void addUserNode(UserHead* head, User* user);
void deleteProfessionNode(ProfessionHead* pHead, UserHead* uHead, Profession* profession);
void clearUsersProfessionById(UserHead* head, int id);
void deleteProfession(ProfessionHead* head, UserHead* userHead);
void clearProfessionList(ProfessionHead* pHead, UserHead* uHead);
void freeProfessionList(ProfessionHead* head);
void freeUserStruct(User* user);
void freeUserList(UserHead* head);

/** utils */
void readProfessions(char* filename, ProfessionHead* head);
void readUsers(char* filename, UserHead* head, ProfessionHead* pHead);
User* findUserById(UserHead* head, int id);
Profession* findProfessionById(ProfessionHead* head, int id);
Profession* findProfessionByName(ProfessionHead* head, char name[MAXLEN]);
void specifyUserProfession(ProfessionHead* pHead, UserHead* uHead);
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
void printLongLine();
void printShortLine();
void printOptionHeader(const char* optionDescription);
void pressEnterToContinue();
void clearConsole();






int main() {
    UserHead* userHead = NULL;
    ProfessionHead* professionHead = NULL;

    userHead = makeUserHead();
    professionHead = makeProfessionHead();

    if (userHead != NULL && professionHead != NULL) {
        app(professionHead, userHead);
    } else {
        printf("Error: memory allocation error\n");
    }

    return 0;
}










void app(ProfessionHead* professionHead, UserHead* userHead) {
    int option;

    readProfessions("professions.csv", professionHead);
    readUsers("users.csv", userHead, professionHead);

    do {
        clearConsole();
        printMenu();
        scanf("%d", &option);
        getchar();
        switch (option) {
            case 1:
                clearConsole();
                printOptionHeader("Print all users");
                printAllUsers(userHead);
                pressEnterToContinue();
                break;
            case 2:
                clearConsole();
                printOptionHeader("Print all professions");
                printAllProfessions(professionHead);
                pressEnterToContinue();
                break;
            case 3:
                clearConsole();
                printOptionHeader("Delete profession before id");
                deleteProfession(professionHead, userHead);
                pressEnterToContinue();
                break;
            case 4:
                clearConsole();
                printOptionHeader("Add new profession");
                addProfession(professionHead);
                pressEnterToContinue();
                break;
            case 5:
                clearConsole();
                printOptionHeader("Clear profession list");
                clearProfessionList(professionHead, userHead);
                pressEnterToContinue();
                break;
            case 6:
                clearConsole();
                printOptionHeader("Specify user profession");
                specifyUserProfession(professionHead, userHead);
                pressEnterToContinue();
                break;
            case 7:
                clearConsole();
                break;
            default:
                break;
        }

    } while (option != 7);

    freeProfessionList(professionHead);
    freeUserList(userHead);
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

    user = (User*)malloc(sizeof(User));

    if (user != NULL) {
        user->fullName = str[0];
        user->age = atoi(str[1]);
        free(str[1]);
        user->profession = findProfessionByName(pHead, str[2]);
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
        profession->id = 1;

    } else  {                                   /* list has only one element */
        profession->id = head->last->id + 1;
        profession->prev = head->last;          /* profession's previous element is last element */
        head->last->next = profession;          /* profession becomes element after last element */
        head->last = profession;                /* profession becomes last element */
        }
}

void addUserNode(UserHead* head, User* user) {
    head->count++;

    if (head->first == NULL) {
        head->first = user;
        head->last = user;
        user->id = 1;

    } else  {
        user->id = head->last->id + 1;
        user->prev = head->last;
        head->last->next = user;
        head->last = user;
    }
    }

void deleteProfessionNode(ProfessionHead* pHead, UserHead* uHead, Profession* profession) {
    if (pHead->first == profession) {
        pHead->first = profession->next;
    }
    if (pHead->last == profession) {
        pHead->last = profession->prev;
    }
    if (profession->prev != NULL) {
        profession->prev->next = profession->next;
    }
    if (profession->next != NULL) {
        profession->next->prev = profession->prev;
    }
    clearUsersProfessionById(uHead, profession->id);
    free(profession);
    pHead->count--;
}

void clearUsersProfessionById(UserHead* head, int id) {
    User* q = NULL;

    q = head->first;
    while (q != NULL) {
        if (q->profession != NULL && q->profession->id == id) {
            q->profession = NULL;
        }
        q = q->next;
    }
}

void deleteProfession(ProfessionHead* pHead, UserHead* uHead) {
    int id;
    Profession* profession = NULL;

    if (pHead->first != NULL) {
        printAllProfessions(pHead);
        printf("\nEnter profession id to delete profession (or 0 to return to menu): ");
        scanf("%d", &id);
        getchar();
        id--;
        if (id > 0) {
            profession = findProfessionById(pHead, id);
            if (profession == NULL) {
                printf("\nFailed: there is no profession with id %d\n", id);
            } else {
                printf("\nProfession with id %d:\n", id);
                printProfessionHeader();
                printProfession(profession);
                printShortLine();
                deleteProfessionNode(pHead, uHead, profession);
                printf("\nSuccess: profession with id %d has been removed!\n", id);
            }
        } else if (id != 0) {
            printf("\nFailed: ID must be always positive\n");
        }
    } else {
        printf("The list of professions is empty\n");
        printf("You can add new profession in menu with option 4\n");
    }
}

void clearProfessionList(ProfessionHead* pHead, UserHead* uHead) {
    Profession *q, *q1;
    User* user;

    q = pHead->first;
    if (q == NULL) {
        printf("There are no profession in the list\n");
    } else {
        while (q != NULL) {
            q1 = q->next;
            free(q);
            q = q1;
        }
        user = uHead->first;
        while (user != NULL) {
            user->profession = NULL;
            user = user->next;
        }
        pHead->first = NULL;
        pHead->last = NULL;
        pHead->count = 0;
        printf("Success: list cleared!\n");
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














void readProfessions(char* filename, ProfessionHead* head) {
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

void readUsers(char* filename, UserHead* head, ProfessionHead* pHead) {
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

Profession* findProfessionByName(ProfessionHead* head, char name[MAXLEN]) {
    Profession* q = NULL;

    q = head->first;
    while (q != NULL && strcmp(q->name, name) != 0) {
        q = q->next;
    }

    return q;
}

Profession* findProfessionById(ProfessionHead* head, int id) {
    Profession* q = NULL;
    q = head->first;
    while (q != NULL && q->id != id) {
        q = q->next;
    }
    return q;
}

User* findUserById(UserHead* head, int id) {
    User* q = NULL;
    q = head->first;
    while (q != NULL && q->id != id) {
        q = q->next;
    }
    return q;
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
        printProfessionHeader();
        printProfession(profession);
        printShortLine();
    } else {
        printf("\nFailed: memory error\n");
    }
}

void specifyUserProfession(ProfessionHead* pHead, UserHead* uHead) {
    User* user;
    Profession* profession;
    int userId, professionId;

    if (pHead->first == NULL) {
        printf("The list of professions is empty\n");
        printf("You can add new profession in menu with option 4\n");
    } else {
        if (uHead->first == NULL) {
            printf("The list of users is empty\n");
        } else {
            printAllUsers(uHead);
            printf("Enter user id: ");
            scanf("%d", &userId);
            getchar();

            user = findUserById(uHead, userId);
            if (user != NULL) {
                printAllProfessions(pHead);
                printf("Enter profession id: ");
                scanf("%d", &professionId);
                getchar();
                profession = findProfessionById(pHead, professionId);
                if (profession != NULL) {
                    user->profession = profession;
                    printf("\nSuccess: profession specified\n");
                    printf("\nUpdated User: \n");
                    printUserHeader();
                    printUser(user);
                    printLongLine();
                } else {
                    printf("\nFailed: profession not found\n");
                }
            } else {
                printf("\nFailed: user not found\n");
            }
        }
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
    printShortLine();
    printf("|           Choose an option           |\n");
    printf("|--------------------------------------|\n");
    printf("| 1. Print all users                   |\n");
    printf("| 2. Print all professions             |\n");
    printf("| 3. Delete profession before id       |\n");
    printf("| 4. Add new profession                |\n");
    printf("| 5. Clear profession list             |\n");
    printf("| 6. Specify user profession           |\n");
    printf("| 7. Exit                              |\n");
    printShortLine();
    printf("Option: ");
}

void printProfessionHeader() {
    printShortLine();
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
    printShortLine();
}

void printUserHeader() {
    printLongLine();
    printf("| ID |       Full Name        | Age |    Profession    | Friends | Public Rating |          Friends IDs          |\n");
    printf("|----|------------------------|-----|------------------|---------|---------------|-------------------------------|\n");
}

void printUser(User *user) {
    int i;
    char friendsIds[MAXLEN] = "";
    char idStr[10];
    char temp[MAXLEN] = "undefined";
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
    printLongLine();
}

void printLongLine() {
    printf("==================================================================================================================\n");
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
