#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "user.h"
#include "profession.h"
#include "gui.h"
#include "utils.h"
#include "output.h"

#define MAXLEN 256


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
        makeLog("ERROR", "split", "Memory allocation failed (result)");
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

void inputIntrray(UserHead* uHead, User* user, char *str, char sep, int isManual) {
    int enteredIdCount = 0, sepCount = 0, unicIdCount = 0, actualIdCount = 0, startIndex, foundIndex;
    int start = 0;
    int i, len, isInputValid, n;
    char tempStr[MAXLEN];
    int enteredIds[MAXLEN];
    int unicEnteredIds[MAXLEN];
    int actualIds[MAXLEN];
    int idList[MAXLEN];

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == sep) sepCount++;
    }
    sepCount++;

    if (sepCount > MAXLEN) {
        printf("It seems that the number of entered IDs is too big -> updating friends count: %d\n", MAXLEN);
        sepCount = MAXLEN - 1;
    }

    if (user->friendsCount != sepCount) {
        printf("It seems that the number of entered IDs does not correspond to the specified number of friends\n");
        sepCount = user->friendsCount;
    }

    isInputValid = 1;
    for (i = 0; str[i] != '\0' && isInputValid && enteredIdCount < sepCount; i++) {
        if (str[i] == ',' || str[i + 1] == '\0') {
            len = (str[i] == ',') ? (i - start) : (i - start + 1);
            strncpy(tempStr, str + start, len);
            tempStr[len] = '\0';

            n = atoi(tempStr);
            if (n != 0) {
                enteredIds[enteredIdCount++] = n;
                start = i + 1;
            } else {
                printf("It seems that your input is not valid. Please check your input and try again\n");
                isInputValid = 0;
            }
        }
    }

    if (!isManual) {
        user->friendsId = malloc(sepCount * sizeof(int));
        if (user->friendsId == NULL) {
            perror("Memory allocation failed");
        } else {
            for (i = 0; i < sepCount; i++) {
                user->friendsId[i] = enteredIds[i];
            }
        }
    }

    if (isInputValid && isManual) {
        getUsersIdList(uHead, idList);
        qsort(idList, uHead->count, sizeof(int), cmp);

        qsort(enteredIds, enteredIdCount, sizeof(int), cmp);
        unicIdCount = 1;
        unicEnteredIds[0] = enteredIds[0];
        for (i = 1; i < enteredIdCount; i++) {
            if (enteredIds[i] != enteredIds[i - 1]) {
                unicEnteredIds[unicIdCount++] = enteredIds[i];
            } else {
                printf("Duplicated ID: %d\n", enteredIds[i]);
            }
        }

        if (unicIdCount != user->friendsCount) {
            printf("It seems that some IDs are entered more than once -> updating friends count: %d\n", unicIdCount);
            user->friendsCount = unicIdCount;
        }

        startIndex = 0;
        actualIdCount = 0;
        for (i = 0; i < unicIdCount; i++) {
            foundIndex = binarySearch(idList, startIndex, uHead->count - 1, unicEnteredIds[i]);
            if (foundIndex != -1) {
                startIndex = foundIndex;
                actualIds[actualIdCount++] = unicEnteredIds[i];
            } else {
                printf("ID not found: %d\n", unicEnteredIds[i]);
            }
        }

        if (actualIdCount != unicIdCount) {
            printf("It seems that list of users does not contain some of entered IDs -> updating friends count: %d\n", actualIdCount);
            user->friendsCount = actualIdCount;
        }
        if (user->friendsId != NULL) {
            free(user->friendsId);
        }
        user->friendsId = malloc(actualIdCount * sizeof(int));
        if (user->friendsId == NULL) {
            perror("Memory allocation failed");
            makeLog("ERROR", "inpuIntArray", "Memory allocation failed (user->friendsId)");
        } else {
            for (i = 0; i < actualIdCount; i++) {
                user->friendsId[i] = actualIds[i];
            }
            printf("Success: friends ids specified\n\n");
        }
    }
}

void getUsersIdList(UserHead* uHead, int* dest) {
    User* tempUser = uHead->first;
    int i = 0;

    while (tempUser != NULL) {
        dest[i++] = tempUser->id;
        tempUser = tempUser->next;
    }
}

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int binarySearch(const int arr[], int start, int end, int target) {
    int result, isFound;

    result = -1;
    isFound = 0;
    while (start <= end && !isFound) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            isFound = 1;
            result = mid;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return result; 
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

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void makeLog(const char* title, const char* funcName, const char* log) {
    FILE* file = fopen("program.log", "a"); 
    struct tm* timeinfo;
    char timeStr[80];
    time_t rawtime;

    if (file == NULL) {
        perror("Error opening log file");
    } else {
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(timeStr, sizeof(timeStr), "%Y-%m-%dT%H:%M:%S", timeinfo);

        fprintf(file, "%-19s | FROM %-30s: %-15s %s\n", timeStr, funcName, title, log);

        fclose(file); 
    }
}
