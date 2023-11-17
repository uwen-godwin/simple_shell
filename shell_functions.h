#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

#include <unistd.h>
#include "info_struct.h"
#include <stddef.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_TOKENS 1024
#define BUF_FLUSH '\0'
#define CMD_NORM  0
#define READ_BUF_SIZE 1024

/* Define the structure to hold information needed for the shell */
typedef struct {
    int readfd;
    char username[50];
    int linecount_flag;
    int histcount;
    char **cmd_buf;
    char **args;
    int error_number;
  
} info_t;


int isInteractive(info_t *info);
int isDelimiter(char c, char *delimiters);
int isAlphabetic(int c);
int customAtoi(char *s);

int isDelimiter(char ch, char *delimiters);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
void freeTokens(char **array, int count);
void executeCommand(char **array);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/* Function prototypes for shell functions */
ssize_t custom_input_buf(info_t *info, char **buffer, size_t *length);
ssize_t custom_get_input(info_t *info);
ssize_t custom_read_buf(info_t *info, char *buffer, size_t *size);
int custom_getline(info_t *info, char **ptr, size_t *length);
void custom_sigintHandler(__attribute__((unused)) int sig_num);
void custom_remove_comments(char *buffer);

#endif /* SHELL_FUNCTIONS_H */
