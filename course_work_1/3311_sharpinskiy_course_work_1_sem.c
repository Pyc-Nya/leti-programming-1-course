#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 4096

/** @brief Checking if a character is a delimiter.
    @param Character.
    @return 1 if character is delimiter else 0.
*/
int isDelimiter(char c);

/** @brief Checking if a string is invalid (i. e. starts with '\0').
    @param Character.
    @return 1 string is invalid else 0.
*/
int isInvalid(const char *str);

/** @brief Prints error message in console.
    @param String message.
    @return Void.
*/
void consoleError(const char *message);

/** @brief Removes '\n' character from string str. If the string has spaces, it will be cut off to the first of them.
    @param String str.
    @return Void.
*/
void removeNewline(char *str);

/** @brief Replaces oldWord in src string with a newWord and puts the result
           in the dest string.
    @param String src.
    @param String oldWord.
    @param String newWord.
    @param String dest.
    @return Void.
*/
void replaceWord(char *src, char *oldWord, char *newWord, char *dest);

/** @brief Clearing console
    @return Void.
*/
void clearConsole();

int main() {
    char text[MAX_LENGTH] = {0}, oldWord[MAX_LENGTH], newWord[MAX_LENGTH], result[MAX_LENGTH] = {0}, temp[MAX_LENGTH], answer[MAX_LENGTH];
    FILE *file;
    int globalErrorFlag = 0, inputFlag = 1;

    do {
        printf("how do you want to enter the data (file / keyboard): ");
        scanf("%s", answer);
        getchar();
    } while (strcmp(answer, "keyboard") != 0 && strcmp(answer, "file") != 0 && strcmp(answer, "k") != 0 && strcmp(answer, "f") != 0);

    clearConsole();

    if (strcmp(answer, "file") == 0 || strcmp(answer, "f") == 0 ) {
        printf("enter the file name: ");
        scanf("%s", temp);
        getchar();
        file = fopen(temp, "r");
        if (file == NULL) {
            consoleError("no such file or directory ");
            globalErrorFlag = 1;
        } else {
            while (fgets(temp, sizeof(temp), file) && !globalErrorFlag) {
                if (strlen(text) + strlen(temp) < MAX_LENGTH) {
                    strcat(text, temp);
                } else {
                    fprintf(stderr, "exceeded limit of text size\n");
                    globalErrorFlag = 1;
                }
            }
            fclose(file);
        }
    } else {
        clearConsole();
        printf("Enter text (end of text is empty line) and press ENTER:\n");
        while (inputFlag && !globalErrorFlag) {
            if (fgets(temp, MAX_LENGTH, stdin) == NULL) {
                consoleError("failed to input text");
                globalErrorFlag = 1;
            }
            if (strcmp(temp, "\n") == 0 && !globalErrorFlag) {
                inputFlag = 0;
            }
            if (strlen(text) + strlen(temp) >= MAX_LENGTH && !globalErrorFlag && inputFlag) {
                consoleError("exceeded limit of text size");
                globalErrorFlag = 1;
            }
            if (!globalErrorFlag && inputFlag) {
                strcat(text, temp);
            }
        }
    }

    if (!globalErrorFlag) {
        clearConsole();
        printf("Enter the word to replace (1 word without delimiters) and press ENTER:\n");
        if (fgets(oldWord, MAX_LENGTH, stdin) == NULL) {
            consoleError("failed to input word");
        } else {
            removeNewline(oldWord);
            if (isInvalid(oldWord)) {
                consoleError("invalid word");
            } else {
                printf("Enter the word for replacement and press ENTER:\n");
                if (fgets(newWord, MAX_LENGTH, stdin) == NULL) {
                    consoleError("failed to input word");
                } else {
                    removeNewline(newWord);

                    replaceWord(text, oldWord, newWord, result);

                    clearConsole();
                    printf("Original text:\n%s\n", text);
                    printf("\nProcessed text:\n%s\n", result);
                }
            }
        }
    }

    return 0;
}

int isDelimiter(char c) {
    return !(
             c >= 'a' && c <= 'z' ||
             c >= '0' && c <= '9' ||
             c >= 'A' && c <= 'Z'
    );
}

int isInvalid(const char *str) {
    return str[0] == '\0';
}

void consoleError(const char *message) {
    printf("Error: %s\n", message);
}

void removeNewline(char *str) {
    int i;

    for (i = 0; i < MAX_LENGTH; i++) {
        if (str[i] == '\n' || str[i] == ' ') {
            str[i] = '\0';
            i = MAX_LENGTH;
        }
    }
}

void replaceWord(char *src, char *oldWord, char *newWord, char *dest) {
    char *pos; /* current position of oldWorld in src */
    int len = 0, oldLen = strlen(oldWord); /* len - length of destination string */
    char *firstSrc = src;

    while ((pos = strstr(src, oldWord)) != NULL) {

        /* checking full word matching */
        if ((pos == firstSrc || isDelimiter(*(pos - 1))) && isDelimiter(*(pos + oldLen))) { /* it may be start of the string, so i added pos == src */
            /* i check current position in dest using dest + len and
            add substring from src with pos - src length */
            strncpy(dest + len, src, pos - src);
            len += pos - src; /* updating length */
            strcpy(dest + len, newWord);
            len += strlen(newWord);
            src = pos + oldLen; /* update src to position pos + oldLen */
        } else {
            strncpy(dest + len, src, pos - src + 1);
            len += pos - src + 1;
            src = pos + 1; /* +1 bc i don't need infinite cycle */
        }
    }
    strcpy(dest + len, src); /* adding the rest of the src */
}

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}
