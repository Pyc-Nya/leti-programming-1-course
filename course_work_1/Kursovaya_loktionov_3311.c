#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MS 1000

void InputToFileFromKeyboard(const char *mainFilename, int numOfStrings, const char *sep_string);
void outputFromFile(const char *filename, int numOfStrings);

int isDelimiter(char symbol, const char *separations);
int isTarget(const char *string, const char *separations, const char *targetWord);
int countWords(const char *line, const char *separations);

void sortLinesByWordCount(char lines[][MS], int numberOfStringsInNew, const char *separations);
void processText(const char *mainFilename, const char *newFilename, const char *targetWord, const char *delimiters, int numberOfStringsInMain, int *numberOfStringsInNew);

void clearScreen();
void askToRepeat();


int main() {

    int numberOfStringsInMain = 0;
    int numberOfStringsInNew = 0;

    char sep_string[MS] = {'\0'};
    char targetWord[MS] = {'\0'};
    char OwnFile[MS] = {'\0'};
    char answer[MS] = {'\0'};

    int len = 0;

    const char *mainFilename = "mainText.txt";
    const char *newFilename = "newText.txt";

    printf("Enter number of strings in your text: "); /*Reading the number of lines in text*/
    scanf("%d", &numberOfStringsInMain);

    while(strcmp(answer, "file") != 0 && strcmp(answer, "keyboard") != 0) {

        printf("How would you like to enter your text? (file / keyboard): "); /*Ask about the way to enter the text*/
        scanf("%s", answer);
        if (strcmp(answer, "keyboard") == 0) {

            clearScreen();
            InputToFileFromKeyboard(mainFilename, numberOfStringsInMain, sep_string); /*if "keyboard" user enters the text himself*/
        } else if (strcmp(answer, "file") == 0) {

            clearScreen();
            printf("Please, enter the name of your file like this 'myfile.txt': ");
            scanf("%s", OwnFile);
            getchar();
            mainFilename = OwnFile; /*if "file" name of users file assign to var mainFile*/
        }
    }

    printf("Please, enter delimiter string: "); /*Enter delimiter string*/
    fgets(sep_string, MS, stdin);
    sep_string[strlen(sep_string) - 1] = '\0';

    printf("Enter target word: "); /*Enter target word*/
    fgets(targetWord, MS, stdin);
    len = strlen(targetWord);
    if (targetWord[len - 1] == '\n') targetWord[len - 1] = '\0';

    processText(mainFilename, newFilename, targetWord, sep_string, numberOfStringsInMain, &numberOfStringsInNew); /*text processing*/

    /*Below, output both texts*/
    printf("\nYour main text:\n");
    outputFromFile(mainFilename, numberOfStringsInMain);

    printf("\nYour new text:\n");
    outputFromFile(newFilename, numberOfStringsInNew);

    askToRepeat();

    return 0;
}

void InputToFileFromKeyboard(const char *mainFilename, int numOfStrings, const char *sep_string) {

    int i = 0;
    int len = 0;
    char inputString[MS];

    FILE *file = fopen(mainFilename, "w");

    if (file != NULL) {

        printf("Enter the text:\n");
        getchar();

        while (i < numOfStrings) {

            fgets(inputString, MS, stdin);
            len = strlen(inputString);
            fprintf(file, "%s", inputString); /*Enter text to file*/
            if (inputString[len - 1] == '\n') inputString[len - 1] = '\0';
            i++;
        }


    } else perror("Error opening file\n");

    fclose(file);
}

void outputFromFile(const char *filename, int numOfStrings) {

    int i = 0;
    char outputString[MS];

    FILE *file = fopen(filename, "r");

    if (file != NULL) {

        while (i < numOfStrings) { /*Different files have different numbers of string, so extra check is the easiest way to avoid an error*/

            fgets(outputString, MS, file);
            printf("%s", outputString);
            i++;
        }
    } else perror("Error opening file\n");

    fclose(file);
}

int isDelimiter(char symbol, const char *separations) {
    return strchr(separations, symbol) != NULL;
}

int isTarget(const char *string, const char *separations, const char *targetWord) {
    const char *word_start = NULL;
    size_t word_length;
    int flag = 0;

    while (*string) { /*Check every symbol in string*/
        while (isDelimiter(*string, separations)) { /*Skip all delimiters*/
            string++;
        }
        word_start = string; /*If we here, it means that current symbol is not in separations string ==> this is a begin of a word*/
        while (*string && !isDelimiter(*string, separations)) { /*Move on until meet a delimiter*/
            string++;
        }

        word_length = string - word_start; /*Len of our word is index of current position - index the beggining of the word */
        if (word_length == strlen(targetWord) && strncmp(word_start, targetWord, word_length) == 0) { /*Because of using pointers we can check similarity of the target word and current word*/
            flag = 1;
        }
    }

    return flag;
}

int countWords(const char *line, const char *separations) {
    int count = 0;
    int isWord = 0;
    int i = 0;

    for (i = 0; line[i] != '\0'; i++) {
        if (isDelimiter(line[i], separations)) { /*Skip all delimiters (if we skipping delimiters it means that we are not in word, so isWord = 0)*/
            isWord = 0;
        } else if (!isWord) { /*If we here, it means that current symbol is not in separations string ==> we are in Word, so isWord = 1*/
            count++;
            isWord = 1; /*This condition will no longer be fulfilled because isWord != 0.(Of course until we meet a separation)*/
        }
    }

    return count;
}

void sortLinesByWordCount(char lines[][MS], int numberOfStringsInNew, const char *separations) {
    int i, j;
    char temp[MS];

    for (i = 0; i < numberOfStringsInNew - 1; i++) {
        for (j = 0; j < numberOfStringsInNew - i - 1; j++) {
            if (countWords(lines[j], separations) > countWords(lines[j + 1], separations)) {
                strcpy(temp, lines[j]); /*standard sorting by using auxiliary var*/
                strcpy(lines[j], lines[j + 1]);
                strcpy(lines[j + 1], temp);
            }
        }
    }
}

void processText(const char *mainFilename, const char *newFilename, const char *targetWord, const char *separations, int numberOfStringsInMain, int *numberOfStringsInNew) {
    char lines[MS][MS];
    char buffer[MS];

    int len = 0;

    int i = 0, k = 0;

    FILE *mainFile = fopen(mainFilename, "r");
    FILE *newFile = fopen(newFilename, "w");

    if (mainFile != NULL && newFile != NULL) {
        while (fgets(buffer, MS, mainFile) != NULL && k < numberOfStringsInMain) {
            len = strlen(buffer);
            if (buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            if (!isTarget(buffer, separations, targetWord)) { /*The string will add to newFile only if it will not have a target word*/
                strcpy(lines[*numberOfStringsInNew], buffer); /*Use two-dimensional array, because it is easy to sort*/
                (*numberOfStringsInNew)++;
            }
            k++;
        }

        sortLinesByWordCount(lines, *numberOfStringsInNew, separations);
        for (i = 0; i < *numberOfStringsInNew; i++) {
            fprintf(newFile, "%s\n", lines[i]);
        }
    } else perror("Error opening file\n");
    fclose(mainFile);
    fclose(newFile);
}
void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}


void askToRepeat() {
    char answer[MS];

    printf("\nDo you want to repeat the program? (yes/no): ");
    scanf("%s", answer);
    getchar();

    if (strcmp(answer, "yes") == 0 || strcmp(answer, "YES") == 0) {
        clearScreen();
        main();
    } else printf("\nBye!\n");
}
