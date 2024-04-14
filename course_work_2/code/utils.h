#ifndef UTILS_H
#define UTILS_H

#include "user.h"

#define MAXLEN 256


void nullString(char str[MAXLEN]);
void trim(char str[MAXLEN]);
char **split(char *str, int length, char sep);
void inputIntrray(UserHead* uHead, User* user, char *str, char sep, int isManual);
void getUsersIdList(UserHead* uHead, int* dest);
int cmp(const void *a, const void *b);
int binarySearch(const int arr[], int start, int end, int target);
int startsWithIgnoreCase(const char *str, const char *prefix);
void clearStdin();
void makeLog(const char* title, const char* funcName, const char* log);

#endif
