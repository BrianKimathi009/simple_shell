#include "shell.h"

/**
 * s_erroratoi - converts a char string to an int
 * @s: string to convert
 * Return: 0 if string has no numbers, converted num otherwise
 *       -1 on error
 */
int s_erroratoi(char *s)
{
	int j = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			res *= 10;
			res += (s[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * output_error - prints an error message
 * @info: the structure parameter
 * @estr: string with the declared error type
 * Return: 0 string has no numbers and -1 on error
 */
void output_error(info_t *info, char *estr)
{
	_sputs(info->fname);
	_sputs(": ");
	output_d(info->line_count, STDERR_FILENO);
	_sputs(": ");
	_sputs(info->argv[0]);
	_sputs(": ");
	_sputs(estr);
}

/**
 * output_d - this function prints an int to base 10
 * @input: int input
 * @fd: fildes to write to
 *
 * Return: num of chars created
 */
int output_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, score = 0;
	unsigned int _abs_, prsnt;

	if (fd == STDERR_FILENO)
		__putchar = _sputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		score++;
	}
	else
		_abs_ = input;
	prsnt = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + prsnt / j);
			score++;
		}
		prsnt %= j;
	}
	__putchar('0' + prsnt);
	score++;

	return (score);
}

/**
 * change_num - this is a converter function(itoa clone)
 * @num: the nuber
 * @base: the base
 * @flags: arg flags
 *
 * Return: the strn
 */
char *change_num(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char clu = 0;
	char *pointr;
	unsigned long numb = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		numb = -num;
		clu = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointr = &buffer[49];
	*pointr = '\0';

	do	{
		*--pointr = arr[numb % base];
		numb /= base;
	} while (numb != 0);

	if (clu)
		*--pointr = clu;
	return (pointr);
}

/**
 * erase_com - this function replaces '#' with '\0'
 * @buf: string address to be modified
 *
 * Return: 0;
 */
void erase_com(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
