#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "user.h"
#include "profession.h"
#include "output.h"
#include "utils.h"
#include "gui.h"

#define MAXLEN 256

void appGUI(ProfessionHead* professionHead, UserHead* userHead) {
    int option, doYouWantToSave;

    readProfessions("professions.csv", professionHead);
    readUsers("users.csv", userHead, professionHead);

    do {
        clearConsole();
        printMenu();
        scanf("%d", &option);
        getchar();
        if (option != 0) {
            appOption(professionHead, userHead, option);
        } else {
            doYouWantToSave = -1;
            printf("\nDo you want to save changes? (1 - yes, 0 - no): ");
            scanf("%d", &doYouWantToSave);
            getchar();
            if (doYouWantToSave == 1) {
                writeUsersToFile(userHead, "users.csv");
                writeProfessionsToFile(professionHead, "professions.csv");
                printf("\nSuccess: changes saved!\n");
                printf("\nBye!\n");
            } else if (doYouWantToSave != 0) {
                option = -1;
                printf("\nFailed: option must be 0 or 1\n");
            } else if (doYouWantToSave == 0) {
                printf("\nBye!\n");
            }
            pressEnterToContinue();
            clearConsole();
        }
    } while (option != 0);

    freeProfessionList(professionHead);
    freeUserList(userHead);
}

void appOption(ProfessionHead* professionHead, UserHead* userHead, int option) {
    clearConsole();
    switch (option) {
        case 1:
            printOptionHeader("Print all users");
            printAllUsers(userHead);
            break;
        case 2:
            printOptionHeader("Print all professions");
            printAllProfessions(professionHead);
            break;
        case 3:
            printOptionHeader("Print full user data");
            printFullUser(userHead);
            break;
        case 4:
            printOptionHeader("Add new profession");
            addProfessionGUI(professionHead);
            break;
        case 5:
            printOptionHeader("Add new user");
            addUserGUI(professionHead, userHead);
            break;
        case 6:
            printOptionHeader("Update user data");
            updateUserDataGUI(professionHead, userHead);
            break;
        case 7:
            printOptionHeader("Filter users");
            filterUsersByFieldGUI(userHead);
            break;
        case 8:
            printOptionHeader("Sort users");
            sortUsersByFieldGUI(userHead);
            break;
        case 9:
            printOptionHeader("Delete profession before id");
            deleteProfessionGUI(professionHead, userHead);
            break;
        case 10:
            printOptionHeader("Delete user");
            deleteUserGUI(userHead);
            break;
        case 11:
            printOptionHeader("Clear user list");
            clearUserListGUI(userHead);
            break;
        case 12:
            printOptionHeader("Clear profession list");
            clearProfessionListGUI(professionHead, userHead);
            break;
        default:
            clearConsole();
            printf("\nFailed: invalid option\n");
            break;
    }
    pressEnterToContinue();
}

void deleteProfessionGUI(ProfessionHead* pHead, UserHead* uHead) {
    int id;
    Profession* profession = NULL;

    if (pHead->first != NULL) {
        printAllProfessions(pHead);
        printf("\nEnter profession id to delete profession before it (or 0 to return to menu): ");
        scanf("%d", &id);
        getchar();
        if (id > 0) {
            id--;
            profession = findProfessionById(pHead, id);
            if (profession == NULL) {
                printf("\nFailed: there is no profession with id %d\n", id);
            } else {
                printf("\nProfession with id %d:\n", id);
                printProfessionHeader();
                printProfession(profession);
                printShortLine();
                deleteProfessionNode(pHead, uHead, profession);
                printf("\nSuccess: profession with id %d has been removed!\n", id);
            }
        } else if (id != 0) {
            printf("\nFailed: ID must be always positive\n");
        }
    } else {
        printf("The list of professions is empty\n");
        printf("You can add new profession in menu with option 4\n");
    }
}

void addUserGUI(ProfessionHead* pHead, UserHead* uHead) {
    User* user = NULL;

    user = (User*)malloc(sizeof(User));
    if (user != NULL) {
        printf("Enter information for new user:\n");

        specifyUserNameGUI(user, 1);
        specifyUserAgeGUI(user, 1);
        specifyUserFriendsRatingGUI(user, 1);
        specifyUserPublicRatingGUI(user, 1);
        specifyUserFriendsGUI(uHead, user, 1);
        specifyUserProfessionGUI(pHead, user, 1);
        
        addUserNode(uHead, user);
        printf("\nSuccess: user has been added!\n");
        printUserHeader();
        printUser(user);
        printLongLine();
    }
}

void deleteUserGUI(UserHead* head) {
    int id;
    User* user = NULL;

    if (head->first != NULL) {
        printAllUsers(head);
        printf("\nEnter user id to delete user (or 0 to return to menu): ");
        scanf("%d", &id);
        getchar();
        if (id > 0) {
            user = findUserById(head, id);
            if (user == NULL) {
                printf("\nFailed: there is no user with id %d\n", id);
            } else {
                printf("\nUser with id %d:\n", id);
                printUserHeader();
                printUser(user);
                printLongLine();
                deleteUserNode(head, user);
                printf("\nSuccess: user with id %d has been removed!\n", id);
            }
        } else if (id != 0) {
            printf("\nFailed: ID must be always positive\n");
        }
    } else {
        printf("The list of users is empty\n");
        printf("You can add new user in menu with option 0\n");
    }
}

void clearProfessionListGUI(ProfessionHead* pHead, UserHead* uHead) {
    Profession *q, *q1;
    User* user;

    q = pHead->first;
    if (q == NULL) {
        printf("There are no profession in the list\n");
    } else {
        while (q != NULL) {
            q1 = q->next;
            free(q);
            q = q1;
        }
        user = uHead->first;
        while (user != NULL) {
            user->profession = NULL;
            user = user->next;
        }
        pHead->first = NULL;
        pHead->last = NULL;
        pHead->count = 0;
        printf("Success: list cleared!\n");
    }
}

void clearUserListGUI(UserHead* head) {
    User* q, *q1;

    if (head->first != NULL) {
        q = head->first;
        while (q != NULL) {
            q1 = q->next;
            freeUserStruct(q);
            q = q1;
        }
        head->last = NULL;
        head->first = NULL;
        head->count = 0;
        printf("Success: list cleared!\n");
    } else {
        printf("The list of users is empty\n");
        printf("You can add new user in menu with option 0\n");
    }
}

void addProfessionGUI(ProfessionHead* head) {
    char temp[MAXLEN];
    Profession* profession = NULL;

    printf("Enter profession name: ");
    if (fgets(temp, MAXLEN, stdin) != NULL) {
        trim(temp);
        profession = makeProfessionNode(temp);
        if (profession != NULL) {
            addProfessionNode(head, profession);
            printf("\nSuccess: profession added\n");
            printProfessionHeader();
            printProfession(profession);
            printShortLine();
        } else {
            printf("\nFailed: memory error\n");
        }
    } else {
        printf("\nFailed: memory error\n");
    }
}

void updateUserDataGUI(ProfessionHead* pHead, UserHead* uHead) {
    User* user;
    int userId, option;

    printAllUsers(uHead);
    printf("Enter user id: ");
    scanf("%d", &userId);
    getchar();
    user = findUserById(uHead, userId);
    if (user != NULL) {
        clearConsole();
        printUserHeader();
        printUser(user);
        printLongLine();

        printf("Which field do you want to edit?\n");
        printf("1. full name\n");
        printf("2. age\n");
        printf("3. friends rating\n");
        printf("4. public rating\n");
        printf("6. friends\n");
        printf("7. profession\n");
        printf("8. all fields\n");
        scanf("%d", &option);
        getchar();
        switch (option) {
            case 1:
                printOptionHeader("Specify user name");
                specifyUserNameGUI(user, 0);
                break;
            case 2:
                printOptionHeader("Specify user age");
                specifyUserAgeGUI(user, 0);
                break;
            case 3:
                printOptionHeader("Specify user friends rating");
                specifyUserFriendsRatingGUI(user, 0);
                break;
            case 4:
                printOptionHeader("Specify user public rating");
                specifyUserPublicRatingGUI(user, 0);
                break;
            case 6:
                printOptionHeader("Specify user friends");
                specifyUserFriendsGUI(uHead, user, 0);
                break;
            case 7:
                printOptionHeader("Specify user profession");
                specifyUserProfessionGUI(pHead, user, 0);
                break;
            case 8:
                printOptionHeader("Specify all fields");
                specifyUserNameGUI(user, 0);
                specifyUserAgeGUI(user, 0);
                specifyUserFriendsRatingGUI(user, 0);
                specifyUserPublicRatingGUI(user, 0);
                specifyUserFriendsGUI(uHead, user, 0);
                specifyUserProfessionGUI(pHead, user, 0);
                break;
        }
        printf("\nUpdated user:\n");
        printUserHeader();
        printUser(user);
        printLongLine();
        printf("\nSuccess: user data updated\n");
    } else {
        printf("\nFailed: user not found\n");
    }
}

void specifyUserNameGUI(User* user, int isStrict) { 
    char temp[MAXLEN];

    printf("Enter user name: ");
    if (fgets(temp, MAXLEN, stdin) != NULL) {
        trim(temp);
        user->fullName = (char*)malloc(strlen(temp) + 1);
        if (user->fullName != NULL) {
            strcpy(user->fullName, temp);
            printf("Success: name specified\n\n");
        } else {
            printf("Failed: memory error\n\n");
        }
    } else {
        printf("Failed: memory error\n\n");
    }
}

void specifyUserAgeGUI(User* user, int isStrict) {
    int age;
    int success;

    printf("Enter user age: ");
    success = scanf("%d", &age);
    getchar();
    if (age < 0 || age > 200 || success != 1) {
        if (isStrict) {
            user->age = 0;
        }
        printf("Failed: invalid or impossible age\n\n");
    } else {
        user->age = age;
        printf("Success: age specified\n\n");
    }
}

void specifyUserFriendsRatingGUI(User* user, int isStrict) {
    float rating;
    int success;

    printf("Enter user friends rating: ");
    success = scanf("%f", &rating);
    getchar();
    if (rating < 0 || rating > 5 || success != 1) {
        if (isStrict) {
            user->friendsRating = 0;
        }
        printf("Failed: invalid or impossible rating\n\n");
    } else {
        user->friendsRating = rating;
        printf("Success: friends rating specified\n\n");
    }
}

void specifyUserPublicRatingGUI(User* user, int isStrict) {
    float rating;
    int success;

    printf("Enter user public rating: ");
    success = scanf("%f", &rating);
    getchar();
    if (rating < 0 || rating > 5 || success != 1) {
        printf("Failed: invalid or impossible rating\n\n");
        if (isStrict) {
            user->publicRating = 0;
        }
    } else {
        user->publicRating = rating;
        printf("Success: public rating specified\n\n");
    }
}

void specifyUserFriendsGUI(UserHead* uHead, User* user, int isStrict) {
    int friendsCount;
    int success;
    char temp[MAXLEN];
    
    printf("Enter user friends count (less than %d): ", uHead->count);
    success = scanf("%d", &friendsCount);
    getchar();
    if (friendsCount < 0 || friendsCount > uHead->count || success != 1) {
        if (isStrict) {
            user->friendsCount = 0;
        }
        printf("Failed: invalid or impossible friends count\n\n");
    } else if (friendsCount == 0) {
        user->friendsCount = 0;
        if (user->friendsId != NULL) {
            free(user->friendsId);
            user->friendsId = NULL;
        }
        printf("Success: friends count specified\n\n");
    } else {
        printAllUsers(uHead);
        user->friendsCount = friendsCount;
        printf("Success: friends count specified\n");
        printf("Enter user friends ids\n");
        printf("Example: 1,2,3,4,5\n");
        printf("Enter friends ids: ");
        if (fgets(temp, MAXLEN, stdin) != NULL) {
            trim(temp);
            inputIntrray(uHead, user, temp, ',', 1);
        } else {
            printf("Failed: memory error\n\n");
        }
    }
}

void specifyUserProfessionGUI(ProfessionHead* pHead, User* user, int isStrict) {
    Profession* profession;
    int success;
    int professionId;
    
    if (pHead->first == NULL) {
        printf("The list of professions is empty\n");
        printf("You can add new profession in menu with option 4\n");
    } else {
        printAllProfessions(pHead);
        printf("Enter profession id: ");
        success = scanf("%d", &professionId);
        getchar();
        if (success != 1) {
            professionId = 0;
        }
        profession = findProfessionById(pHead, professionId);
        if (profession != NULL) {
            user->profession = profession;
            printf("Success: profession specified\n\n");
        } else {
            printf("Failed: profession not found\n\n");
            if (isStrict) {
                user->profession = NULL;
            }
        }
    }
}

void filterUsersByFieldGUI(UserHead* uHead) {
    int option;
    char temp[MAXLEN];
    int tempInt;
    float tempFloat1, tempFloat2;

    printf("1. Name\n");
    printf("2. Profession\n");
    printf("3. Age\n");
    printf("4. Friends Rating\n");
    printf("5. Public Rating\n");
    printf("6. Friends Count\n");
    printf("Enter option: ");
    scanf("%d", &option);
    getchar();
    switch (option) {
        case 1:
            printf("Enter name: ");
            if (fgets(temp, MAXLEN, stdin) != NULL) {
                trim(temp);
                filterUsersByName(uHead, temp);
            }
            break;
        case 2:
            printf("Enter profession name: ");
            if (fgets(temp, MAXLEN, stdin) != NULL) {
                trim(temp);
                filterUsersByProfessionName(uHead, temp);
            }
            break;
        case 3:
            printf("Enter age: ");
            scanf("%d", &tempInt);
            getchar();
            filterUsersByAge(uHead, tempInt, tempInt);
            break;
        case 4:
            printf("Enter min friends rating: ");
            scanf("%f", &tempFloat1);
            getchar();
            printf("Enter max friends rating: ");
            scanf("%f", &tempFloat2);
            getchar();
            filterUsersByFriendsRating(uHead, tempFloat1, tempFloat2);
            break;
        case 5:
            printf("Enter min public rating: ");
            scanf("%f", &tempFloat1);
            getchar();
            printf("Enter max public rating: ");
            scanf("%f", &tempFloat2);
            getchar();
            filterUsersByPublicRating(uHead, tempFloat1, tempFloat2);
            break;
        case 6:
            printf("Enter min friends count: ");
            scanf("%d", &tempInt);
            getchar();
            printf("Enter max friends count: ");
            scanf("%d", &tempInt);
            getchar();
            filterUsersByFriendsCount(uHead, tempInt, tempInt);
            break;
        default:
            printf("Wrong option\n");
            break;
    }
}

void printFullUser(UserHead* uHead) {
    User* user;
    int i, id;

    printAllUsers(uHead);
    printf("Enter user id: ");
    scanf("%d", &id);
    getchar();
    user = findUserById(uHead, id);
    if (user == NULL) {
        printf("User not found\n");
    } else {
        printf("User ID: %d\n", user->id);
        printf("Name: %s\n", user->fullName);
        printf("Age: %d\n", user->age);
        printf("Profession: %s\n", user->profession ? user->profession->name : "undefined");
        printf("Friends Count: %d\n", user->friendsCount);
        printf("Friends Rating: %.1f\n", user->friendsRating);
        printf("Public Rating: %.1f\n", user->publicRating);

        printf("Friends IDs: ");
        for (i = 0; i < user->friendsCount; i++) {
            printf("%d", user->friendsId[i]);
            if (i < user->friendsCount - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void sortUsersByFieldGUI(UserHead* uHead) {
    int option;

    if (uHead->first != NULL) {
        printf("1. Sort by id\n");
        printf("2. Sort by name\n");
        printf("3. Sort by age\n");
        printf("4. Sort by friends rating\n");
        printf("5. Sort by public rating\n");
        printf("6. Sort by friends count\n");
        printf("Enter option: ");
        scanf("%d", &option);
        getchar();
        if (option > 0 && option <= 6) {
            sortUsersByField(uHead, option);
            printf("Success: users sorted\n");
        } else {
            printf("Wrong option\n");
        }
    } else {
        printf("The list of users is empty\n");
        printf("You can add new user in menu with option 5\n");
    }
}
