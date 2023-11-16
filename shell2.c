#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS 1024

int main(void) {
    size_t buf_size = 0;
    char *buf = NULL;
    char *token;
    int j, i = 0;
    int status;
    char **array;
    pid_t child_pid;

    while (1) {
        write(1, "#cisfun$ ", 9);

        if (getline(&buf, &buf_size, stdin) == -1)
	{
            if (feof(stdin)) {
                free(buf);
                exit(EXIT_SUCCESS);
            }

            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        array = malloc(MAX_TOKENS * sizeof(char *));
        if (!array)
	{
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        token = strtok(buf, " \t\n");
        while (token && i < MAX_TOKENS - 1)
	{
            array[i] = strdup(token);
            if (!array[i])
	    {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " \t\n");
            i++;
        }
        array[i] = NULL;

        child_pid = fork();
        if (child_pid == -1)
	{
            perror("Error forking");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
	{
            if (execvp(array[0], array) == -1)
	    {
                perror("Error executing command");
                exit(EXIT_FAILURE);
            }
        }
	else
	{
            waitpid(child_pid, &status, 0);
            for (j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
        }
    }

    free(buf);

    return 0;
}
