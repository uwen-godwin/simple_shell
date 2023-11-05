#include "shell.h"

/**
 * parseInput - Tokenizes the input string
 * @input: The input string to be tokenized
 * This function tokenizes the input string
 * based on space, tab, or newline characters.
 * It dynamically allocates memory for an array
 * of strings to hold the tokens.
 * Return: Array of tokens obtained from the input string
 */

char **parseInput(char *input)
{
		char **tokens = malloc(MAX_INPUT_LENGTH * sizeof(char *));
		char *token;
		int i = 0;

		if (!tokens)
		{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
		}

		token = strtok(input, " \t\r\n\a");
		while (token != NULL)
		{
		tokens[i] = token;
		i++;

		token = strtok(NULL, " \t\r\n\a");
		}
		tokens[i] = NULL;
		return (tokens);
}

/**
 * executeCommand - Executes the command provided in the arguments
 * @args: Array of strings containing the command and its arguments
 * This function forks a child process and
 * executes the command specified in the args array.
 * Return: No explicit return value; the command is
 * executed within a child process.
 */
void executeCommand(char **args)
{
		pid_t pid = fork();

		if (pid < 0)
		{
		perror("Fork error");
		exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
		if (execvp(args[0], args) == -1)
		{
		printf("Command not found\n");
		exit(EXIT_FAILURE);
		}
		}
		else
		{
		int status;

		waitpid(pid, &status, 0);
		}
}
/**
 * main - The main shell function
 *
 * This function represents the entry point
 * of the Gshell program. It runs a shell interface
 * that continuously prompts the user for commands,
 * processes these commands, and executes them.
 * Return: Returns 0 upon successful execution.
 */

int main(void)
{
		char input[MAX_INPUT_LENGTH];
		char **arguments;

		while (1)
		{
		printf("root@Gshell$ ");
		f(fgets(input, sizeof(input), stdin) == NULL);
		{
		printf("\n");
		break;
		}

		input[strcspn(input, "\n")] = 0;

		arguments = parseInput(input);
		executeCommand(arguments);
		free(arguments);
		}
		return (0);
}
