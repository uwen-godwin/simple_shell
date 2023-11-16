#include "shell_functions.h"

/**
 * freeTokens - Frees the memory allocated
 * @array: Pointer to the array of strings
 * @count: Number of strings in the array
 */
void freeTokens(char **array, int count)
{
	int j;

	for (j = 0; j < count; j++)
	{
	free(array[j]);
	}
	free(array);
}
/**
 * executeCommand - Executes a command
 * in a child process
 * @array: Pointer to an array of strings
 * representing the command and its arguments
 */
void executeCommand(char **array)
{
	if (execvp(array[0], array) == -1)
	{
	perror("Error executing command");
	exit(EXIT_FAILURE);
	}
}
/**
 * main - Entry point for the shell program and
 * executes the command in a child process.
 * It waits for the child process to
 * complete and then repeats the process.
 * Return: Always returns 0.
 */
int main(void)
{
	size_t buf_size = 0;
	char *buf = NULL;
	char *token;
	int i = 0;
	int status;
	char **array;
	pid_t child_pid;

	while (1)
	{
	write(1, "#cisfun$ ", 9);
	if (getline(&buf, &buf_size, stdin) == -1)
	{
	if (feof(stdin))
	{
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
	executeCommand(array);
	}
	else
	{
	waitpid(child_pid, &status, 0);
	freeTokens(array, i);
	}
	}
	free(buf);
	return (0);
}
