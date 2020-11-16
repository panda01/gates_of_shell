#include <stdlib.h>
#include <stdarg.h>
#include "../khalah_shell.h"

int _strlen(char *str);
char *_strremovechar(char *str, char ch);
char *_findkeyvalue(char *needle, char **haystack);
char *_substr(char *str, int start, int count);
int _strsareequal(char *stra, char *strb);
char *_strcat(char *stra, char *strb);
char *_strmcat(int count, ...);

/**
 * _strlen - Returns the length of a string
 * @str: the string to get the length of
 * Return: the amount of characters not including the \0
 */
int _strlen(char *str)
{
	int idx = 0;

	while (str[idx] != '\0')
	{
		idx++;
	}
	return (idx);
}

/**
 * _strremovechar - Removes all occurences of any character from a string
 * @str: The string we're remove characters from
 * @ch: the character to remove
 * Return: the new string with the removed character
 */
char *_strremovechar(char *str, char ch)
{
	int strl = _strlen(str);
	int charcount = 0;
	int idx;
	int jdx;
	char *newstr;

	while (str[idx++] != '\0')
	{
		charcount++;
	}
	newstr = malloc(strl - charcount);

	for (idx = 0, jdx = 0; str[idx] != '\0'; idx++)
	{
		if (str[idx] != ch)
		{
			newstr[jdx] = str[idx];
			jdx++;
		}
	}

	return (newstr);
}

/**
 * _strsareequal - Checks to if two strings have the exact same chars
 * @stra: the first string to compare
 * @strb: the second string to compare
 * Return: 1 if the strings are equal, 0 otherwise
 */
int _strsareequal(char *stra, char *strb)
{
	int stralen = _strlen(stra);
	int strblen = _strlen(strb);
	int idx;

	if (stralen != strblen)
	{
		return (0);
	}

	for (idx = 0; stra[idx] != '\0'; idx++)
	{
		if (stra[idx] != strb[idx])
		{
			return (0);
		}
	}

	return (1);
}
/**
 * _substr - Returns a new shortened string starting at start until the end
 * @str: the string to shorten
 * @start: where to start the cut
 * @count: number of elements to get use -1 to get the rest of the str
 * Return: the shortened string
 */
char *_substr(char *str, int start, int count)
{
	int strlen = _strlen(str);
	char *retstr;
	int idx;

	if (count == -1)
	{
		count = strlen - start;
	}
	retstr = malloc(count + 1);

	for (idx = 0; idx < count && str[idx] != '\0'; idx++)
	{
		retstr[idx] = str[idx + start];
	}

	retstr[idx] = '\0';

	return (retstr);
}

/**
 * _findkeyvalue - With an array of strings get the value for key
 * @needle: the key to look for
 * @haystack: the [] of string with a structure like "key=value"
 * Return: the value from the match
 */
char *_findkeyvalue(char *needle, char **haystack)
{
	int n_len;
	int idx;

	n_len = _strlen(needle);

	for (idx = 0; haystack[idx] != NULL; idx++)
	{
		if (_strsareequal(needle, _substr(haystack[idx], 0, n_len)))
		{
			return (_substr(haystack[idx], n_len + 1, -1));
		}
	}

	return (NULL);
}

/**
 * _strcat - concatenate 2 strings
 * @stra: the first string
 * @strb: the second string
 * Return: the newly concatenated string
 */
char *_strcat(char *stra, char *strb)
{
	int idx;
	int jdx;
	int stralen;
	int strblen;
	char *retstr;

	stralen = _strlen(stra);
	strblen = _strlen(strb);

	retstr = malloc(stralen + strblen + 1);
	for (idx = 0, jdx = 0; jdx < stralen; idx++, jdx++)
	{
		retstr[idx] = stra[jdx];
	}

	for (jdx = 0; jdx < strblen; idx++, jdx++)
	{
		retstr[idx] = strb[jdx];
	}

	return (retstr);
}

/**
 * _strmcat - concatenate any number of strings
 * @count: the number of strings we're concatenating
 * Return: the newly concatenated string
 */
char *_strmcat(int count, ...)
{
	int idx;
	char *retstr = "";
	va_list str_args;

	va_start(str_args, count);

	for (idx = 0; idx < count; idx++)
	{
		retstr = _strcat(retstr, va_arg(str_args, char *));
	}

	return (retstr);
}
