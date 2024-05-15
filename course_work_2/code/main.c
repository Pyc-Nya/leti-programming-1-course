#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 256

#include "user.h"
#include "profession.h"
#include "gui.h"
#include "utils.h"

int main() {
    UserHead* userHead = NULL;
    ProfessionHead* professionHead = NULL;

    makeLog("APP START", "main", "App started work");
    userHead = makeUserHead();
    professionHead = makeProfessionHead();

    if (userHead != NULL && professionHead != NULL) {
        appGUI(professionHead, userHead);
    } else {
        printf("Error: memory allocation error\n");
    }

    makeLog("APP FINISH", "main", "App finished work\n");
    return 0;
}
