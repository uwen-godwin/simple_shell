#include "shell_functions.h"

/**
 **copy_string - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@num_chars: the amount of characters to be copied
 *Return: the concatenated string
 */
char *copy_string(char *destination, char *source, int num_chars)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < num_chars - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < num_chars)
	{
		j = i;
		while (j < num_chars)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 **concat_strings - concatenates two strings
 *@str1: the first string
 *@str2: the second string
 *@max_chars: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *concat_strings(char *str1, char *str2, int max_chars)
{
	int i, j;
	char *result = str1;
	i = 0;
	j = 0;

	while (str1[i] != '\0')
		i++;
	while (str2[j] != '\0' && j < max_chars)
	{
		str1[i] = str2[j];
		i++;
		j++;
	}
	if (j < max_chars)
		str1[i] = '\0';
	return (result);
}

/**
 **find_character - locates a character in a string
 *@input_str: the string to be parsed
 *@target_char: the character to look for
 *Return: a pointer to the memory area of the input string
 */
char *find_character(char *input_str, char target_char)
{
	do
	{
		if (*input_str == target_char)
			return (input_str);
	}
	while (*input_str++ != '\0');

	return (NULL);
}
