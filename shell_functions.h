#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_TOKENS 1024


int isDelimiter(char ch, char *delimiters);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
void freeTokens(char **array, int count);
void executeCommand(char **array);


#endif /* SHELL_FUNCTIONS_H */
