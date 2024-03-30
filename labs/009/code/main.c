#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAXLEN 256

#include "user.h"
#include "profession.h"
#include "gui.h"

int main() {
    UserHead* userHead = NULL;
    ProfessionHead* professionHead = NULL;

    userHead = makeUserHead();
    professionHead = makeProfessionHead();

    if (userHead != NULL && professionHead != NULL) {
        appGUI(professionHead, userHead);
    } else {
        printf("Error: memory allocation error\n");
    }

    return 0;
}
