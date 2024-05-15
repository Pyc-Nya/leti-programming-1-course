#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "profession.h"
#include "gui.h"
#include "utils.h"
#include "output.h"


#define MAXLEN 256

UserHead* makeUserHead() {
    UserHead* head = NULL;

    head = (UserHead*)malloc(sizeof(UserHead));
    if (head != NULL) {
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
    } else {
        perror("Memory allocation failed");
        makeLog("ERROR", "makeUserHead", "Memory allocation failed (head)");
    }

    return head;
}

User* makeUserNode() {
    User* user = NULL;

    user = (User*)malloc(sizeof(User));
    if (user != NULL) {
        user->age = 0;
        user->friendsCount = 0;
        user->publicRating = 0;
        user->friendsRating = 0;
        user->id = 0;
        user->fullName = NULL;
        user->profession = NULL;
        user->friendsId = NULL;
        user->next = NULL;
        user->prev = NULL;
        user->id = 0;
    }

    return user;
}

void fillUserNode(ProfessionHead* pHead, UserHead* uHead, User* user, char** str) {

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

        if (user->friendsCount > 0) {
            user->friendsId = NULL;
            inputIntArray(uHead, user, str[6], ',', 0);
        } else {
            user->friendsId = NULL;
        }
        free(str[6]);

        free(str);

        user->next = NULL;
        user->prev = NULL;
    } else {
        perror("Memory allocation failed");
        makeLog("ERROR", "makeUserNode", "Memory allocation failed (user)");
    }
}

void pushBackUserNode(UserHead* head, User* user) {
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

void freeUserStruct(User* user) {
    if (user->fullName != NULL) {
        free(user->fullName);
        user->fullName = NULL;
    }

    if (user->friendsId != NULL) {
        free(user->friendsId);
        user->friendsId = NULL;
    }

    if (user->profession != NULL) {
        user->profession = NULL;
    }

    free(user);
}

void freeUserList(UserHead* head) {
    User *q = NULL, *q1 = NULL;
    /* char buffer[MAXLEN]; */
    
    q = head->first;
    /* makeLog("LIST FREE", "freeUserList", "start"); */
    while (q != NULL) {
        /* sprintf(buffer, "%p", q->next); */
        /* makeLog("attempt to get q->next", "freeUserList", buffer); */
        q1 = q->next;
        freeUserStruct(q);
        q = q1;
    }
    /* sprintf(buffer, "%p", head); */
    /* makeLog("attempt to free head", "freeUserList", buffer); */
    free(head);
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
        makeLog("FILE READ", "readUsers", filename);
        while ((fgets(temp, MAXLEN, file)) != NULL) n++;
        rewind(file);

        for (i = 0; i < n; i++, count++) {
            nullString(temp);
            fgets(temp, MAXLEN, file);
            slen = strlen(temp);
            trim(temp);
            splitArray = split(temp, slen, ';');
            if (splitArray != NULL) {
                user = makeUserNode();
                if (user != NULL) {
                    fillUserNode(pHead, head, user, splitArray);
                    pushBackUserNode(head, user);
                }
            }
        }
        fclose(file);
    } else {
        perror("Failed to open file");
        makeLog("ERROR", "readUsers", "Failed to open file");
    }

    if (count != n) {
        perror("Failed to read from file");
        freeUserList(head);
    }
}

User* findUserById(UserHead* head, int id) {
    User* q = NULL;
    q = head->first;
    while (q != NULL && q->id != id) {
        q = q->next;
    }
    return q;
}


void filterUsersByName(UserHead* uHead, char* name) {
    User *q;

    printUserHeader();
    q = uHead->first;
    while (q != NULL) {
        if (startsWithIgnoreCase(q->fullName, name) == 1) {
            printUser(q);
        }
        q = q->next;
    }
    printLongLine();
}

void filterUsersByProfessionName(UserHead* uHead, char* professionName) {
    User *q;

    printUserHeader();
    q = uHead->first;
    while (q != NULL) {
        if ((q->profession != NULL && startsWithIgnoreCase(q->profession->name, professionName) == 1) || (q->profession == NULL && startsWithIgnoreCase("undefined", professionName) == 1)) {
            printUser(q);
        }
        q = q->next;
    }
    printLongLine();
}

void filterUsersByAge(UserHead* uHead, int minAge, int maxAge) {
    User *q;

    printUserHeader();
    q = uHead->first;
    while (q != NULL) {
        if (q->age >= minAge && q->age <= maxAge) {
            printUser(q);
        }
        q = q->next;
    }
    printLongLine();
}

void filterUsersByFriendsRating(UserHead* uHead, float minRating, float maxRating) {
    User *q;

    printUserHeader();
    q = uHead->first;
    while (q != NULL) {
        if (q->friendsRating >= minRating && q->friendsRating <= maxRating) {
            printUser(q);
        }
        q = q->next;
    }
    printLongLine();
}

void filterUsersByPublicRating(UserHead* uHead, float minRating, float maxRating) {
    User *q;

    printUserHeader();
    q = uHead->first;
    while (q != NULL) {
        if (q->publicRating >= minRating && q->publicRating <= maxRating) {
            printUser(q);
        }
        q = q->next;
    }
    printLongLine();
}

void filterUsersByFriendsCount(UserHead* uHead, int minCount, int maxCount) {
    User *q;

    printUserHeader();
    q = uHead->first;
    while (q != NULL) {
        if (q->friendsCount >= minCount && q->friendsCount <= maxCount) {
            printUser(q);
        }
        q = q->next;
    }
    printLongLine();
}

void deleteUserNode(UserHead* head, User* user) {
    User* q = NULL;
    int* tempPtr;
    int i, j, check;
    int temp[MAXLEN] = {0};

    q = head->first;
    while (q != NULL) {
        if (q->friendsCount > 0 && q->friendsId != NULL) {
            check = 0;
            j = 0;
            for (i = 0; i < q->friendsCount; i++) {
                if (q->friendsId[i] != user->id) {
                    temp[j++] = q->friendsId[i];
                } else {
                    check = 1;
                }
            }
            if (check) {
                q->friendsCount--;
				if (q->friendsCount != 0) {
					tempPtr = (int*)malloc(q->friendsCount * sizeof(int));
					if (tempPtr != NULL) {
						free(q->friendsId);
						q->friendsId = tempPtr;
						for (i = 0; i < q->friendsCount; i++) {
							q->friendsId[i] = temp[i];
						}
					} else {
						perror("Memory allocation failed");
					}
				} else {
					free(q->friendsId);
					q->friendsId = NULL;
				}
            }
        }
        q = q->next;
    }

    if (head->first == user) {
        head->first = user->next;
        if (user->next != NULL) {
            user->next->prev = user->prev;
        }
    } else if (head->last == user) {
        head->last = user->prev;
        if (user->prev != NULL) {
            user->prev->next = user->next;
        }
    } else {
        if (user->prev != NULL) {
            user->prev->next = user->next;
        }
        if (user->next != NULL) {
            user->next->prev = user->prev;
        }
    }

    freeUserStruct(user);
    head->count--;
}

void sortUsersByField(UserHead* head, int option) {
    User* sorted = NULL;
    User* current = head->first;
    User* next = NULL;
    User* temp = NULL;

    if (head->first != NULL && head->first->next != NULL) {
        while (current != NULL) {
            next = current->next;
            if (sorted == NULL || compareUsers(current, sorted, option) < 0) {
                current->next = sorted;
                if (sorted != NULL) sorted->prev = current;
                sorted = current;
                sorted->prev = NULL;
            } else {
                temp = sorted;
                while (temp->next != NULL && compareUsers(current, temp->next, option) > 0) {
                    temp = temp->next;
                }
                current->next = temp->next;
                if (temp->next != NULL) temp->next->prev = current;
                temp->next = current;
                current->prev = temp;
            }
            current = next;
        }
        head->first = sorted;
        temp = sorted;
        while (temp != NULL && temp->next != NULL) {
            temp = temp->next;
        }
        head->last = temp;
    }
}

int compareUsers(User* a, User* b, int option) {
    int result;

    switch (option) {
        case 1: 
            result =  a->id - b->id;
            break;
        case 2: 
            result = strcmp(a->fullName, b->fullName);
            break;
        case 3: 
            result = a->age - b->age;
            break;
        case 4: 
            result = (a->friendsRating > b->friendsRating) ? 1 : (a->friendsRating < b->friendsRating) ? -1 : 0;
            break;
        case 5: 
            result = (a->publicRating > b->publicRating) ? 1 : (a->publicRating < b->publicRating) ? -1 : 0;
            break;
        case 6: 
            result = a->friendsCount - b->friendsCount;
            break;
        default: 
            result = 0;
            break;
    }

    return result;
}

void writeUsersToFile(UserHead* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    User* current = NULL;
    char* professionName;
    int i;

    if (file != NULL) {
        makeLog("FILE WRITE", "writeUsersToFile", filename);
        current = head->first;
        while (current != NULL) {
            professionName = "undefined";
            if (current->profession != NULL) {
                professionName = current->profession->name;
            }

            fprintf(file, "%s;%d;%s;%.1f;%.1f;%d", current->fullName, current->age, professionName, 
                    current->friendsRating, current->publicRating, current->friendsCount);

            if (current->friendsCount > 0 && current->friendsId != NULL) {
                fprintf(file, ";");
                for (i = 0; i < current->friendsCount; i++) {
                    fprintf(file, "%d", current->friendsId[i]);
                    if (i < current->friendsCount - 1) {
                        fprintf(file, ",");
                    }
                }
            }

            fprintf(file, "\n");

            current = current->next;
        }

        fclose(file);
    } else {
        printf("Failed to open file %s\n", filename);
        makeLog("ERROR", "writeUsersToFile", "Failed to open file");
    }
}
