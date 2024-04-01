#ifndef PROFESSION_H
#define PROFESSION_H

#define MAXLEN 256

typedef struct userHeadStruct UserHead;

#include "user.h"

typedef struct professionStruct {
    int id;
    char name[MAXLEN];
    struct professionStruct* next;
    struct professionStruct* prev;
} Profession;

typedef struct professionHeadStruct {
    Profession* first;
    Profession* last;
    int count;
} ProfessionHead;

ProfessionHead* makeProfessionHead();
Profession* makeProfessionNode(char name[MAXLEN]);
void addProfessionNode(ProfessionHead* head, Profession* profession);
void deleteProfessionNode(ProfessionHead* pHead, UserHead* uHead, Profession* profession);
void freeProfessionList(ProfessionHead* head);
void readProfessions(char* filename, ProfessionHead* head);
Profession* findProfessionById(ProfessionHead* head, int id);
Profession* findProfessionByName(ProfessionHead* head, char name[MAXLEN]);
void writeProfessionsToFile(ProfessionHead* head, const char* filename);

#endif
