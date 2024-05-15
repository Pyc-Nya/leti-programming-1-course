#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "profession.h"
#include "gui.h"
#include "utils.h"
#include "output.h"

#define MAXLEN 256


ProfessionHead* makeProfessionHead() {
    ProfessionHead* head = NULL;

    head = (ProfessionHead*)malloc(sizeof(ProfessionHead));
    if (head != NULL) {
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
    } else {
        perror("Memory allocation failed");
        makeLog("ERROR", "makeProfessionHead", "Memory allocation failed (head)");
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

void pushBackProfessionNode(ProfessionHead* head, Profession* profession) {
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

void deleteProfessionNode(ProfessionHead* pHead, UserHead* uHead, Profession* profession) {
    if (pHead->first == profession) {
        pHead->first = profession->next;
    } else if (pHead->last == profession) {
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

void readProfessions(char* filename, ProfessionHead* head) {
    FILE* file;
    Profession* profession;
    int n, count, i;
    char temp[MAXLEN];

            profession = NULL;
        n = count = 0;
        file = fopen(filename, "r");

        if (file != NULL) {
            makeLog("FILE READ", "readProfessions", filename);
            while ((fgets(temp, MAXLEN, file)) != NULL) n++;
            rewind(file);

            for (i = 0; i < n; i++) {
                nullString(temp);
                fgets(temp, MAXLEN, file);
                trim(temp);
                profession = makeProfessionNode(temp);
                if (profession != NULL) {
                    pushBackProfessionNode(head, profession);
                    count++;
                }
            }
            fclose(file);
        } else {
            perror("Failed to open file");
            makeLog("ERROR", "readProfessions", "Failed to open file");
        }

        if (count != n) {
            perror("Failed to read from file");
            freeProfessionList(head);
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

void writeProfessionsToFile(ProfessionHead* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    Profession* current = NULL;

    if (file != NULL) {
        makeLog("FILE WRITE", "writeProfessionsToFile", filename);
        current = head->first;
        while (current != NULL) {
            fprintf(file, "%s\n", current->name);

            current = current->next;
        }

        fclose(file);
    } else {
        makeLog("ERROR", "writeProfessionsToFile", "Failed to open file");
        perror("Failed to open file");
    }
}
