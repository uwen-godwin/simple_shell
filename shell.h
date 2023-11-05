#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

void f(int condition) {
    if (condition) {
        printf("\n");
        exit(0);
    }
}
char** parseInput(char* input);
void executeCommand(char** args);

#endif
