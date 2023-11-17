#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

#include <unistd.h>
#include <stddef.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_TOKENS 1024
#define BUF_FLUSH '\0'
#define CMD_NORM 1
#define READ_BUF_SIZE 1024 

int isDelimiter(char ch, char *delimiters);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
void freeTokens(char **array, int count);
void executeCommand(char **array);

/* Define the structure to hold information needed for the shell */
typedef struct {
    int readfd;
    char username[50];
    int linecount_flag;
    int histcount;
    char **cmd_buf;
    
} info_t;

/* Function prototypes for shell functions */
ssize_t custom_input_buf(info_t *info, char **buffer, size_t *length);
ssize_t custom_get_input(info_t *info);
ssize_t custom_read_buf(info_t *info, char *buffer, size_t *size);
int custom_getline(info_t *info, char **ptr, size_t *length);
void custom_sigintHandler(__attribute__((unused)) int sig_num);

void custom_puts(const char *str);
void custom_putchar(char c);
size_t custom_strlen(const char *s);
char *custom_strncpy(char *dest, const char *src, size_t n);
char *custom_strncat(char *dest, const char *src, size_t n);
char *custom_strchr(const char *s, int c);
void custom_remove_comments(char *buffer);
void custom_build_history_list(info_t *info, char *buffer, int histcount);
void custom_check_chain(info_t *info, char *buffer, size_t *j, size_t i, size_t len);
int custom_is_chain(info_t *info, char *buffer, size_t *j);

#endif /* SHELL_FUNCTIONS_H */
