#ifndef OUTPUT_H
#define OUTPUT_H

#include "user.h"
#include "profession.h"

#define MAXLEN 256

void printMenu();
void printProfessionHeader();
void printAllProfessions(ProfessionHead* head);
void printUserHeader();
void printAllUsers(UserHead* uHead);
void printOptionHeader(const char* optionDescription);
void pressEnterToContinue();
void clearConsole();
void trimForDisplay(char *output, const char *input, int maxLength);
void printUser(User *user);
void printProfession(Profession *profession);
void printLongLine();
void printShortLine();


#endif
