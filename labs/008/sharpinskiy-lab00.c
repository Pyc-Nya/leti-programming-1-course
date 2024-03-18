#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXLEN 256

typedef struct userStruct {
    int id;
    char *fullName;
    int age;
    char *profession;
    float friendsRating;
    float publicRating;
    int friendsCount;
    int friendsId[MAXLEN];
    struct userStruct* next;
} User;

typedef struct LHead {
    int last_id;
    int isFriendsSorted;
    struct userStruct* first;
    struct userStruct* last;
} Head;

char **simpleSplit(char *str, int length, char sep);
void simpleSplitInt(const char *str, char sep, int arr[]);
User* makeNode(char** str);
Head* makeHead();
void addUser(Head *head);
void addNode(Head* my_head, User* new_node);
void bubbleSortByField(Head *my_head, char* desc);
void swapNodes(User **prevNode, User *a, User *b);
void printHeader();
void outStruct(User *user);
void printAllUsers(Head* my_head);
void trim(char *str);
void clearConsole();
int startsWithIgnoreCase(const char *str, const char *prefix);
void deleteNode(Head *my_head, User *current_node);
User *selectId(Head *my_head, int n);
void pressEnterToContinue();
void freeList(Head* my_head);
void deleteById(Head* head);
void filterList(Head* head);
void clearList(Head* head);

int main() {
    Head* head = NULL;
    User* user = NULL;
    int slen, i, n, count, option;
    char sep;
    char temp[MAXLEN];
    char** splitArray;
    FILE* file;

    head = makeHead();
    n = 0;
    count = 0;
    file = fopen("index.csv", "r");
    if (file != NULL) {
        while ((fgets(temp, MAXLEN, file)) != NULL) n++;
        rewind(file);

        sep = ';';

        for (i = 0, count = 0; i < n; i++, count++) {
            fgets(temp, MAXLEN, file);
            slen = strlen(temp);
            temp[slen - 1] = '\0';

            splitArray = simpleSplit(temp, slen, sep);
            if (splitArray != NULL) {
                user = makeNode(splitArray);
                if (user != NULL) {
                    addNode(head, user);
                } else {
                    puts("Structure not allocated!");
                    i = n;
                }
            } else {
                puts("Error data reading!");
                i = n;
            }
        }
        fclose(file);
    } else {
        perror("Failed to open file");
        printf("\n");
    }

    if (count == n) {
        bubbleSortByField(head, "id");
        clearConsole();
        do {
            printf("Choose option and press ENTER:\n"
                   "1. Print all users\n"
                   "2. Sort users by friends count\n"
                   "3. Sort users by id\n"
                   "4. Add new user\n"
                   "5. Filter users by name or profession\n"
                   "6. Delete user before specified id\n"
                   "7. Clear list\n"
                   "8. Exit\n\n");
            printf("Option: ");
            scanf("%d", &option);
            getchar();
            switch (option) {
            case 1:
                clearConsole();
                printAllUsers(head);
                pressEnterToContinue();
                break;
            case 2:
                clearConsole();
                bubbleSortByField(head, "friends");
                printf("Sorted!\n");
                head->isFriendsSorted = 1;
                pressEnterToContinue();
                break;
            case 3:
                clearConsole();
                bubbleSortByField(head, "id");
                printf("Sorted!\n");
                head->isFriendsSorted = 0;
                pressEnterToContinue();
                break;
            case 4:
                clearConsole();
                addUser(head);
                pressEnterToContinue();
                break;
            case 5:
                clearConsole();
                filterList(head);
                pressEnterToContinue();
                break;
            case 6:
                clearConsole();
                if (head->first != NULL) {
                    deleteById(head);
                } else {
                    printf("The list is cleared and there is no users to remove!\n"
                           "You can add new users with command 4 in menu!\n");
                }
                pressEnterToContinue();
                break;
            case 7:
                clearConsole();
                if (head->first != NULL) {
                    clearList(head);
                    printf("The list is now cleared!\n");
                } else {
                    printf("The list is already empty!\n");
                }
                pressEnterToContinue();
            case 8:
                clearConsole();
                break;
            default:
                clearConsole();
                break;
            }
        } while (option != 8);

        freeList(head);
    } else puts("An error occurred while running the program!");

    return 0;
}

char **simpleSplit(char *str, int length, char sep) {
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
            if (str[i] == sep || str[i] == '\0') {
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

void simpleSplitInt(const char *str, char sep, int arr[]) {
    int count = 0;
    int start = 0;
    int i, len;
    char tempStr[MAXLEN];

    for (i = 0; i < MAXLEN; i++) {
        arr[i] = 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == sep || str[i + 1] == '\0') {
            len = (str[i] == sep) ? (i - start) : (i - start + 1);
            strncpy(tempStr, str + start, len);
            tempStr[len] = '\0';

            arr[count++] = atoi(tempStr);

            start = i + 1;
        }
    }
}

void printHeader() {
    printf("%-3s %-20s %-5s %-15s %-15s %-15s %-15s %-20s\n",
           "ID", "Full Name", "Age", "Profession", "Friends Rating", "Public Rating", "Friends Count", "Friends IDs");
}

void outStruct(User *user) {
    int i;
    printf("%-3d %-20s %-5d %-15s %-15.1f %-15.1f %-15d ",
           user->id, user->fullName, user->age, user->profession, user->friendsRating, user->publicRating, user->friendsCount);

    printf("[");
    for (i = 0; i < user->friendsCount; i++) {
        printf("%d", user->friendsId[i]);
        if (i < user->friendsCount - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void addUser(Head *head) {
    User *newUser;
    char tempStr[MAXLEN];
    int tempAge;
    float tempFriendsRating, tempPublicRating;
    int tempFriendsCount;

    newUser = malloc(sizeof(User));
    if (newUser == NULL) {
        perror("Memory allocation failed");
    } else {
        newUser->next = NULL;

        newUser->id = head->last_id + 1;

        printf("Enter full name: ");
        newUser->fullName = malloc(MAXLEN * sizeof(char));
        if (newUser->fullName == NULL || fgets(newUser->fullName, MAXLEN, stdin) == NULL) {
            perror("Failed to read full name or allocate memory");
            free(newUser);
        } else {
            trim(newUser->fullName);
            printf("Enter age: ");
            scanf("%d", &tempAge);
            getchar();
            newUser->age = tempAge > 0 ? tempAge : 10;

            printf("Enter profession: ");
            newUser->profession = malloc(MAXLEN * sizeof(char));
            if (newUser->profession == NULL || fgets(newUser->profession, MAXLEN, stdin) == NULL) {
                perror("Failed to read image filename or allocate memory");
                free(newUser->fullName);
                free(newUser);
            } else {
                trim(newUser->profession);
                printf("Enter friends rating (float number less than 5): ");
                if (scanf("%f", &tempFriendsRating) == 1 && tempFriendsRating <= 5) {
                    newUser->friendsRating = tempFriendsRating;
                } else {
                    newUser->friendsRating = 0;
                }
                getchar();

                printf("Enter public rating (float number less than 5): ");
                if (scanf("%f", &tempPublicRating) == 1 && tempPublicRating <= 5) {
                    newUser->publicRating = tempPublicRating;
                } else {
                    newUser->publicRating = 0;
                }
                getchar();

                printf("Enter friends count: ");
                if (scanf("%d", &tempFriendsCount) == 1 && tempFriendsCount <= MAXLEN && tempFriendsCount >= 0) {
                    newUser->friendsCount = tempFriendsCount;
                } else {
                    tempFriendsCount = 0;
                    newUser->friendsCount = 0;
                }
                getchar();

                if (tempFriendsCount > 0) {
                    printf("Enter friends IDs (example: 1,2,3,4) ");
                    scanf("%s", tempStr);
                    getchar();
                    simpleSplitInt(tempStr, ',', newUser->friendsId);
                }

                addNode(head, newUser);
                if (head->isFriendsSorted) {
                    bubbleSortByField(head, "friends");
                } else {
                    bubbleSortByField(head, "id");
                }

                printf("\nNew user successfully added!\n");

            }
        }
    }
}

void clearStruct(User *user) {
    if (user != NULL) {
        free(user->fullName);
        user->fullName = NULL;

        free(user->profession);
        user->profession = NULL;

        free(user);
    }
}

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void trim(char *str) {
    int i = 0;

    for (i = 0; i < MAXLEN; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            i = MAXLEN;
        }
    }
}

int startsWithIgnoreCase(const char *str, const char *prefix) {
    int isPrefix = 1;

    while (*str && *prefix && isPrefix) {
        if (tolower(*str) != tolower(*prefix)) {
            isPrefix = 0;
        }
        str++;
        prefix++;
    }
    if (*prefix != '\0') {
        isPrefix = 0;
    }

    return isPrefix;
}

User* makeNode(char** str) {
    User *user = NULL;
    user = (User*)malloc(sizeof(User));

    if (user != NULL) {
        user->id = atoi(str[0]);
        free(str[0]);
        user->fullName = str[1];
        user->age = atoi(str[2]);
        free(str[2]);
        user->profession = str[3];
        user->friendsRating = atof(str[4]);
        free(str[4]);
        user->publicRating = atof(str[5]);
        free(str[5]);
        user->friendsCount = atoi(str[6]);
        free(str[6]);

        simpleSplitInt(str[7], ',', user->friendsId);
        free(str[7]);

        free(str);

        user->next = NULL;
    }

    return user;
}

Head* makeHead() {
    Head* ph = NULL;
    ph = (Head*)malloc(sizeof(Head));
    if (ph != NULL) {
        ph->last_id = 0;
        ph->first = NULL;
        ph->last = NULL;
        ph->isFriendsSorted = 0;
    }
    return ph;
}

void addNode(Head* my_head, User* new_node) {
    User* q = NULL;

    if (my_head && new_node) {
        q = my_head->first;
        if (q == NULL) {
            my_head->last_id = 1;
            my_head->first = new_node;
            my_head->last = new_node;
        } else {
            my_head->last_id++;
            new_node->id = my_head->last_id;
            new_node->next = q;
            my_head->first = new_node;
        }
    }
}

void printAllUsers(Head* my_head) {
    User *q;
    printHeader();
    q = my_head->first;
    while (q != NULL) {
        outStruct(q);
        q = q->next;
    }
}

void freeList(Head* my_head) {
    User *q, *q1;
    /* there are two pointers here because we need to remember
    the next value of the structure we are going to clear */
    q = my_head->first;
    while (q != NULL) {
        q1 = q->next;
        clearStruct(q);
        q = q1;
    }
    free(my_head);
}

/**
 * Sorts a linked list of users either by their ID or by their friend count in ascending order.
 * This function implements a bubble sort algorithm that iterates through the list, comparing
 * adjacent nodes based on the specified field (`desc`). If `desc` is "id", nodes are sorted
 * by their ID in ascending order; if `desc` is anything else, nodes are sorted by their
 * friendsCount in descending order.
 *
 * The use of a double pointer (**ptr1) for node swapping is crucial here. It allows directly
 * modifying the pointer to the current node in the list (either the `first` field of the head
 * or the `next` field of a node). This direct manipulation eliminates the need for a separate
 * case to update the head of the list when the first two nodes are swapped and simplifies
 * swapping nodes in general by adjusting the pointer that points to the current node rather
 * than the node itself.
 *
 * @param my_head A pointer to the head of the list, which contains pointers to the first
 *                and last nodes of the list.
 * @param desc A string that specifies the field by which the list should be sorted:
 *             "id" for sorting by ID in ascending order, anything else for sorting by
 *             friendsCount in descending order.
 */
void bubbleSortByField(Head *my_head, char* desc) {
    int swapped;
    User **ptr1;
    User *lptr = NULL;

    if (my_head->first != NULL) {
        do {
            swapped = 0;
            ptr1 = &(my_head->first);

            while ((*ptr1)->next != lptr) {
                if ((strcmp(desc, "id") == 0) ?
                    (*ptr1)->id > (*ptr1)->next->id :
                    (*ptr1)->friendsCount < (*ptr1)->next->friendsCount) {
                    swapNodes(ptr1, *ptr1, (*ptr1)->next);
                    swapped = 1;
                }
                ptr1 = &((*ptr1)->next);
            }
            lptr = *ptr1;
        } while (swapped);

        lptr = my_head->first;
        while (lptr != NULL && lptr->next != NULL) {
            lptr = lptr->next;
        }
        my_head->last = lptr;
    }
}

/**
 * Swaps two adjacent nodes in a linked list.
 * This function updates the previous node's next pointer to point to the second node, effectively
 * swapping the two nodes in the list. It makes use of a double pointer to the previous node's next
 * field (**prevNode) to directly modify the link between nodes, facilitating the swap operation
 * without additional steps to handle special cases, such as swapping the head of the list.
 *
 * @param prevNode A double pointer to the previous node's next field, pointing to the first of
 *                 the two nodes to be swapped.
 * @param a A pointer to the first node to be swapped.
 * @param b A pointer to the second node to be swapped, immediately following the first.
 */
void swapNodes(User **prevNode, User *a, User *b) {
    (*prevNode) = b;
    a->next = b->next;
    b->next = a;
}

User *selectId(Head *my_head, int n) {
    User *q = NULL;
    int k, isFound;

    isFound = 0;
    q = my_head->first;
    k = my_head->last_id;

    if (((n - 1) > 0) && ((n - 1) <= k) && q != NULL) {
        do {
            if ((q->id) == (n - 1)) {
                isFound = 1;
            } else {
                q = q->next;
            }
        } while (q != NULL && !isFound);
    }

    if (!isFound) {
        q = NULL;
    }

    return q;
}

void deleteNode(Head *my_head, User *current_node) {
    User *q;
    int isFound = 0;

    if (current_node == my_head->first) {
        my_head->first = current_node->next;
        current_node->next = NULL;
        clearStruct(current_node);
    } else {
        q = my_head->first;
        while (q != NULL && !isFound) {
            if (q->next == current_node) {
                if(current_node == my_head->last) {
                    my_head->last = q;
                }
                q->next = current_node->next;
                current_node->next = NULL;
                clearStruct(current_node);
                isFound = 1;
            }
            else {
                q = q->next;
            }
        }
    }

    if (my_head->first != NULL) {
        my_head->last_id = my_head->last->id;
    } else {
        my_head->last_id = 0;
    }
}

void pressEnterToContinue() {
    printf("\nPress ENTER to continue ");
    getchar();
    clearConsole();
}

void deleteById(Head* head) {
    User* q;
    int id;

    bubbleSortByField(head, "id");
    q = head->first;

    printf("Enter the users id to remove the user BEFORE it\n"
           "(enter 0 if you don't want to do it)\n\n"
           "Here is list of ids:\n[");
    while (q != NULL) {
        printf("%d", q->id);
        if (q->next != NULL) {
            printf(", ");
        }
        q = q->next;
    }
    printf("]\n\n");
    printf("Example:\n"
           "id: 2 -> user with id 1 will be removed\n\n"
           "id: ");
    scanf("%d", &id);
    getchar();
    if (id != 0) {
        q = selectId(head, id);
        if (q != NULL) {
            deleteNode(head, q);
            printf("\nSuccess: user with id %d has been removed!\n", id - 1);
        } else {
            printf("Failed: there is no user with id %d.\n", id - 1);
        }
    }
    if (head->isFriendsSorted) {
        bubbleSortByField(head, "friends");
    }
}

void filterList(Head* head) {
    User* q = NULL;
    User* q1 = NULL;
    char ask;
    int j;
    char temp[MAXLEN];

    printf("You can sort users by either name or profession. Choose one option (1 or 2): ");
    scanf("%c", &ask);
    getchar();
    if (ask != '1' && ask != '2') {
        printf("invalid option");
    } else {
        clearConsole();
        if (ask == '1') {
            printf("Enter the user name: ");
        } else {
            printf("Enter the profession: ");
        }
        scanf("%s", temp);
        getchar();
        printf("\n");
        printHeader();
        j = 0;
        q = head->first;
        while (q != NULL) {
            if (startsWithIgnoreCase((ask == '2') ? q->profession : q->fullName, temp)) {
                outStruct(q);
                j++;
            }
            q1 = q->next;
            q = q1;
        }
        if (j == 0) {
            printf("\nNo user seems to match your input.\n");
        }
    }
}

void clearList(Head* head) {
    User* q;
    q = head->first;
    while (q != NULL) {
        deleteNode(head, q);
        q = q->next;
    }
}
