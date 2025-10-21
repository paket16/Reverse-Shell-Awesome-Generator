#ifndef REVERSE_SHELL_H
#define REVERSE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_SHELL_TYPES 100  // увеличим для всех шаблонов
#define BUFFER_SIZE 4096     // увеличим для длинных payload'ов
#define CLIPBOARD_CMD "xclip -selection clipboard"

typedef struct {
    char name[50];
    char description[100];
    char template[512];
    char category[30];  // Новая поле для категории
} ShellTemplate;

typedef enum {
    MODE_FILE,
    MODE_CLIPBOARD,
    MODE_EXECUTE
} OutputMode;

// Прототипы функций
void initialize_templates(ShellTemplate *templates, int *count);
void show_menu(ShellTemplate *templates, int count);
int get_user_choice(int max);
void generate_shell(ShellTemplate *template, char *ip, int port, char *output);
void save_to_file(const char *filename, const char *content);
void copy_to_clipboard(const char *content);
int execute_listener(int port);
void shell_upgrade(int sockfd);
void interactive_shell(int sockfd);

#endif