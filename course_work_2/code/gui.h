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
void specifyUserNameGUI(User* user);
void specifyUserAgeGUI(User* user);
void specifyUserFriendsRatingGUI(User* user);
void specifyUserPublicRatingGUI(User* user);
void specifyUserProfessionGUI(ProfessionHead* pHead, User* user);
void specifyUserFriendsGUI(UserHead* uHead, User* user);
void updateUserDataGUI(ProfessionHead* pHead, UserHead* uHead);
void addUserGUI(ProfessionHead* pHead, UserHead* uHead);
void filterUsersByFieldGUI(ProfessionHead* pHead, UserHead* uHead);
void deleteUserGUI(UserHead* head);
void clearProfessionListGUI(ProfessionHead* pHead, UserHead* uHead);
void sortUsersByFieldGUI(UserHead* uHead);
void clearUserListGUI(UserHead* head);

#endif
