#include "shell__functions.h"
/**
 * isInteractive - checks if the shell is in interactive mode
 * @info: Pointer to the info_t structure containing program information.
 * 
 * Return: 1 if interactive mode, 0 otherwise
 */
int isInteractive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * isDelimiter - checks if a character is a delimiter
 * @c: The character to check
 * @delimiters: The delimiter string
 * 
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char c, char *delimiters)
{
    while (*delimiters)
    {
        if (*delimiters++ == c)
	{
            return (1);
        }
    }
    return (0);
}
/**
 * isAlphabetic - checks for an alphabetic character
 * @c: The character to check
 * 
 * Return: 1 if 'c' is alphabetic, 0 otherwise
 */
int isAlphabetic(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/**
 * customAtoi - converts a string to an integer
 * @s: The string to be converted
 * 
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int customAtoi(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
	{
            sign *= -1;
        }

        if (s[i] >= '0' && s[i] <= '9')
	{
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        }
	else if (flag == 1)
	{
            flag = 2;
        }
    }

    if (sign == -1)
    {
        output = -result;
    }
    else
    {
        output = result;
    }

    return (output);
}
