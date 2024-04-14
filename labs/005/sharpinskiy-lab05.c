#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 500

int is_delimiter(char ch, const char *delimiters);

int count_words(const char *s, const char *delimiters);

int main() {
    char s[MAX_LENGTH], d[MAX_LENGTH];
    int n, count;

    printf("enter the string and press key ENTER\n");
    if (fgets(s, MAX_LENGTH, stdin) != NULL) {
        printf("enter the number of delimiter characters\n");
        if (scanf("%d", &n) && n > 0) {
            getchar();
            printf("enter the delimiter characters and press key ENTER\n");
            if (fgets(d, n + 1, stdin) != NULL) {
                printf("your delimiter characters (between ||): |%s|\n", d);
                count = count_words(s, d);
                printf("number of words of maximum length: %d\n", count);
            } else {
                printf("error: failed to input string\n");
            }
        } else {
            printf("error: wrong number");
        }
    } else {
        printf("error: failed to input string\n");
    }

    return 0;
}

int is_delimiter(char ch, const char *delimiters) {
    int result = 0, i;

    for (i = 0; delimiters[i] != '\0' && !result; i++) {
        if (ch == delimiters[i]) {
            result = 1;
        }
    }
    return result;
}

int count_words(const char *s, const char *delimiters) {
    int max_length = 0, current_length = 0, count = 0, check = 0, i;

    for (i = 0; s[i] != '\n' && !check; i++) {
        check = !is_delimiter(s[i], delimiters);
    }

    if (check) {
        for (i = 0; s[i] != '\n'; i++) {
            check = is_delimiter(s[i], delimiters);
            if (!check) {
                current_length++;
            } else {
                if (current_length > max_length) {
                    max_length = current_length;
                    count = 1;
                } else if (current_length == max_length) {
                    count++;
                }
                current_length = 0;
            }
        }
        if (current_length > max_length) {
            count = 1;
        } else if (current_length == max_length && current_length > 0) {
            count++;
        }
    }

    return count;
}
