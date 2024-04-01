#ifndef GUI_H
#define GUI_H

#include "profession.h"
#include "output.h"
#include "user.h"
#include "utils.h"

#define MAXLEN 256

void appOption(ProfessionHead* professionHead, UserHead* userHead, int option);
void appGUI(ProfessionHead* pHead, UserHead* uHead);
void deleteProfessionGUI(ProfessionHead* head, UserHead* userHead);
void addProfessionGUI(ProfessionHead* head);
void specifyUserNameGUI(User* user, int isStrict);
void specifyUserAgeGUI(User* user, int isStrict);
void specifyUserFriendsRatingGUI(User* user, int isStrict);
void specifyUserPublicRatingGUI(User* user, int isStrict);
void specifyUserProfessionGUI(ProfessionHead* pHead, User* user, int isStrict);
void specifyUserFriendsGUI(UserHead* uHead, User* user, int isStrict);
void updateUserDataGUI(ProfessionHead* pHead, UserHead* uHead);
void addUserGUI(ProfessionHead* pHead, UserHead* uHead);
void filterUsersByFieldGUI(UserHead* uHead);
void deleteUserGUI(UserHead* head);
void clearProfessionListGUI(ProfessionHead* pHead, UserHead* uHead);
void printFullUser(UserHead* uHead);
void sortUsersByFieldGUI(UserHead* uHead);
void clearUserListGUI(UserHead* head);

#endif
