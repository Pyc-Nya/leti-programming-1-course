#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

int main() {
    glob_t glob_result;
    const char *pattern = "course_work*.c";

    // Поиск файлов по шаблону
    int res = glob(pattern, 0, NULL, &glob_result);
    if (res != 0) {
        printf("No files found matching the pattern: %s\n", pattern);
        return 1;
    }

    // Предположим, что берем первый файл из найденных
    const char *file_to_compile = glob_result.gl_pathv[0];
    printf("Found file: %s\n", file_to_compile);

    // Формируем команду компиляции
    char compile_command[256];
    snprintf(compile_command, sizeof(compile_command), "gcc %s -std=c90 -o main", file_to_compile);

    // Запускаем компиляцию
    printf("Compiling: %s\n", compile_command);
    int compile_result = system(compile_command);

    // Проверяем успешность компиляции
    if (compile_result != 0) {
        printf("Compilation error.\n");
        globfree(&glob_result);
        return 1;
    }

    // Запуск main.exe
    printf("Running main.exe\n");
    int run_result = system("./main");

    globfree(&glob_result);
    return run_result;
}
