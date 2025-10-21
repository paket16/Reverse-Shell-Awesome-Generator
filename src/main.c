#include "reverse_shell.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    ShellTemplate templates[MAX_SHELL_TYPES];
    int template_count = 0;
    char ip[16];
    int port;
    char payload[BUFFER_SIZE];
    
    initialize_templates(templates, &template_count);
    
    while (1) {
        show_header();
        show_menu(templates, template_count);
        show_footer();
        
        int choice = get_user_choice(template_count);
        
        if (choice == 0) {
            printf("Exiting program. Goodbye!\n");
            break;
        }
        
        // Показываем выбранный вариант
        show_header();
        printf("║  Selected: %-45s     ║\n", templates[choice - 1].name);
        printf("║  Description: %-40s       ║\n", templates[choice - 1].description);
        printf("╠══════════════════════════════════════════════════════════════╣\n");
        
        // Запрашиваем данные для подключения
        printf("║  Enter IP address: ");
        scanf("%15s", ip);
        printf("║  Enter port: ");
        scanf("%d", &port);
        
        // Генерируем payload
        generate_shell(&templates[choice - 1], ip, port, payload);
        
        // Показываем результат
        printf("╠══════════════════════════════════════════════════════════════╣\n");
        printf("║  Generated Payload:                                          ║\n");
        printf("║  %-58s  ║\n", "");
        printf("║  ┌────────────────────────────────────────────────────────┐  ║\n");
        printf("║  │ %-53s  │ ║\n", payload);                                
        printf("║  └────────────────────────────────────────────────────────┘  ║\n");
        printf("║                                                              ║\n");
        
        // Меню экспорта
        printf("║  Export options:                                             ║\n");
        printf("║  1. Save to file                                             ║\n");
        printf("║  2. Copy to clipboard                                        ║\n");
        printf("║  3. Show only                                                ║\n");
        printf("║  4. Start listener                                           ║\n");
        printf("║  Your choice: ");
        
        int export_choice;
        scanf("%d", &export_choice);
        
        switch (export_choice) {
            case 1: {
                char filename[100];
                printf("║  Enter filename: ");
                scanf("%99s", filename);
                save_to_file(filename, payload);
                break;
            }
            case 2:
                copy_to_clipboard(payload);
                break;
            case 3:
                printf("║  Payload displayed above                                ║\n");
                break;
            case 4:
                start_listener(port);
                break;
            default:
                printf("║  Invalid choice                                        ║\n");
        }
        
        printf("║                                                              ║\n");
        printf("║  Press Enter to continue...                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════╝\n");
        getchar(); // Очищаем буфер
        getchar(); // Ждем нажатия Enter
    }
    
    return 0;
}