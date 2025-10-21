#include "reverse_shell.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"


// void show_menu(ShellTemplate *templates, int count) {
//     printf("\n=== Reverse Shell Generator ===\n");
//     printf("Выберите тип reverse shell:\n\n");
    
//     for (int i = 0; i < count; i++) {
//         printf("%d. %s - %s\n", i + 1, templates[i].name, templates[i].description);
//     }
//     printf("\n0. Выход\n");
//     printf("\nВаш выбор: ");
// }

void clear_screen() {
    printf("\033[2J\033[H"); // ANSI escape codes для очистки экрана
}

void show_header() {
    clear_screen();
    printf("\n");
    printf(COLOR_CYAN "╔══════════════════════════════════════════════════════════════╗\n" COLOR_RESET);
    printf(COLOR_CYAN "║" COLOR_YELLOW "                  REVERSE SHELL GENERATOR" COLOR_CYAN "                     ║\n" COLOR_RESET);
    printf("╠══════════════════════════════════════════════════════════════╣\n");
}

void show_footer() {
    printf("║                                                              ║\n");
    printf("║  0. Exit                                                     ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\nYour choice: ");
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

void show_menu(ShellTemplate *templates, int count) {
    printf("║  Select shell type:                                          ║\n");
    printf("║                                                              ║\n");
    
    char current_category[30] = "";
    int item_number = 1;
    
    for (int i = 0; i < count; i++) {
        // Показываем заголовок категории если она изменилась
        if (strcmp(current_category, templates[i].category) != 0) {
            strcpy(current_category, templates[i].category);
            printf("║  ┌─[ %s ]", current_category);
            
            // Заполняем оставшееся пространство (точный расчет)
            int category_length = strlen(current_category);
            int padding = 52 - category_length; // 58 - 6 (длина "[ ]" и отступы)
            for (int j = 0; j < padding; j++) {
                printf("─");
            }
            printf("┐ ║\n");
        }
        
        // Показываем элемент меню
        printf("║  │ %2d. %-18s %30s   │ ║\n", 
               item_number, 
               templates[i].name, 
               "");
        
        // Показываем описание
        printf("║  │    %-47s      │ ║\n", templates[i].description);
        
        item_number++;
        
        // Если следующая категория другая или это последний элемент, закрываем блок
        if (i == count - 1 || strcmp(templates[i].category, templates[i + 1].category) != 0) {
            printf("║  └─────────────────────────────────────────────────────────┘ ║\n");
            if (i != count - 1) {
                printf("║                                                              ║\n");
            }
        }
    }
    
}