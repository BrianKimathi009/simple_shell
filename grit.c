#include "shell.h"

/**
 * s_intrctive - this function returns true if shell is interactive mode
 * @info: the struct address
 *
 * Return: 1 on interactive mode, 0 if not
 */
int s_intrctive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * s_delimtr - tihis function checks if character is a delimeter
 * @c: char to be checked
 * @delim: the delimeter string
 * Return: 1 if true, 0 if not
 */
int s_delimtr(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *s_isalphabt - this function checks for alphabets
 *@c: input character
 *Return: 1 if c is an alphabet, 0 if not
 */

int s_isalphabt(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *s_atoi - this function converts a char string to an int
 *@s: string to convert
 *Return: 0 if string has no converted numbers
 */

int s_atoi(char *s)
{
	int j, rsgn = 1, rflag = 0, yield;
	unsigned int res = 0;

	for (j = 0;  s[j] != '\0' && rflag != 2; j++)
	{
		if (s[j] == '-')
			rsgn *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			rflag = 1;
			res *= 10;
			res += (s[j] - '0');
		}
		else if (rflag == 1)
			rflag = 2;
	}

	if (rsgn == -1)
		yield = -res;
	else
		yield = res;

	return (yield);
}
