#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void compile_and_run(const char* filename) {
    char compile_command[256];
    snprintf(compile_command, sizeof(compile_command), "gcc %s -std=c90 -o main.exe", filename);
    
    printf("Compiling: %s\n", compile_command);
    int compile_result = system(compile_command);

    if (compile_result != 0) {
        printf("Compilation error.\n");
    } else {
        printf("Running main.exe\n");
        system("main.exe");
    }
}

int main() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("sharpinskiy*.c", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No files found matching the pattern: sharpinskiy*.c\n");
        return 1;
    } else {
        printf("Found file: %s\n", findFileData.cFileName);
        compile_and_run(findFileData.cFileName);
    }

    FindClose(hFind);
    return 0;
}
