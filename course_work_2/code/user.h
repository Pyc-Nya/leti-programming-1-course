#ifndef USER_H
#define USER_H

typedef struct professionHeadStruct ProfessionHead;

#include "profession.h"

#define MAXLEN 256

typedef struct userStruct {
    int id;
    char *fullName;
    int age;
    float friendsRating;
    float publicRating;
    int friendsCount;
    int* friendsId;
    Profession* profession; 
    struct userStruct* next;
    struct userStruct* prev;
} User;

typedef struct userHeadStruct {
    User* first;
    User* last;
    int count;
} UserHead;

UserHead* makeUserHead();
User* makeUserNode(ProfessionHead* pHead, UserHead* uHead, char** str);
void pushBackUserNode(UserHead* head, User* user);
void freeUserStruct(User* user);
void freeUserList(UserHead* head);
void clearUsersProfessionById(UserHead* head, int id);
void readUsers(char* filename, UserHead* head, ProfessionHead* pHead);
User* findUserById(UserHead* head, int id);
void filterUsersByPublicRating(UserHead* uHead, float minRating, float maxRating);
void filterUsersByFriendsRating(UserHead* uHead, float minRating, float maxRating);
void filterUsersByAge(UserHead* uHead, int minAge, int maxAge);
void filterUsersByFriendsCount(UserHead* uHead, int minCount, int maxCount);
void filterUsersByProfessionName(UserHead* uHead, char* professionName);
void filterUsersByName(UserHead* uHead, char* name);
void deleteUserNode(UserHead* head, User* user);
int compareUsers(User* a, User* b, int option);
void sortUsersByField(UserHead* uHead, int option);
void writeUsersToFile(UserHead* head, const char* filename);

#endif
