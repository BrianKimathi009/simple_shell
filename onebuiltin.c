#include "shell.h"

/**
 * _theexit - function that exits the shell
 * @info: maintains constant function prototype as a Structure
 * containing potential args
 *  Return: 0 if info.argv[0] is not 'exit'
 */
int _theexit(info_t *info)
{
	int exchck;

	if (info->argv[1])
	{
		exchck = s_erroratoi(info->argv[1]);
		if (exchck == -1)
		{
			info->status = 2;
			output_error(info, "Illegal number: ");
			_sputs(info->argv[1]);
			_sputchar('\n');
			return (1);
		}
		info->err_num = s_erroratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _thecd - changes the current directory of the process
 * @info: maintains constant function prototype as a Structure
 *  containing potential args
 *
 *  Return: 0
 */
int _thecd(info_t *info)
{
	char *t, *dirct, buffer[1024];
	int chdir_sret;

	t = getcwd(buffer, 1024);
	if (!t)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirct = s_getenv(info, "HOME=");
		if (!dirct)
			chdir_sret =
				chdir((dirct = s_getenv(info, "PWD=")) ? dirct : "/");
		else
			chdir_sret = chdir(dirct);
	}
	else if (s_strcmp(info->argv[1], "-") == 0)
	{
		if (!s_getenv(info, "OLDPWD="))
		{
			_puts(t);
			_putchar('\n');
			return (1);
		}
		_puts(s_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_sret =
			chdir((dirct = s_getenv(info, "OLDPWD=")) ? dirct : "/");
	}
	else
		chdir_sret = chdir(info->argv[1]);
	if (chdir_sret == -1)
	{
		output_error(info, "can't cd to ");
		_sputs(info->argv[1]), _sputchar('\n');
	}
	else
	{
		s_setenv(info, "OLDPWD", s_getenv(info, "PWD="));
		s_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _theassist - this function changes the current dir of the process
 * @info:  maintains constant function prototype as a Structure
 * containing potential args
 *  Return: 0
 */
int _theassist(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("assist call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
