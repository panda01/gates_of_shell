#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *_strremovechar(char *str, char ch);
int _strlen(char *str);

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	int num_chars_typed;
	size_t MAX_INPUT_CHARS = 256;
	char *user_raw_input;

	user_raw_input = malloc(MAX_INPUT_CHARS);
	if (user_raw_input == NULL)
	{
		perror("malloc failed");
		return (1);
	}

	num_chars_typed = getline(&user_raw_input, &MAX_INPUT_CHARS, stdin);

	char *clean_input = _strremovechar(user_raw_input, '\n');
	printf("you typed: %s \n", clean_input);
	printf("num characters: %d\n", _strlen(clean_input));
	printf("num characters: %d\n", _strlen("/bin/ls"));


	/*  Runs the ls command!!! */
	char *alltheargs[] = {clean_input, NULL};
	execve(alltheargs[0], alltheargs, NULL);


	free(user_raw_input);
	free(clean_input);
	free(alltheargs);


	/*
	int status;
	pid_t fork_pid;
	
	printf("before fork\n");
	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror("Fork failed: ");
		return (1);
	}
	printf("After fork\n");

	if(fork_pid == 0)
	{
		printf("This is the child\n");
		sleep(1);
	}
	else
	{
		printf("This is the father\n");
		wait(&status);
		printf("this is the father, after waiting, tapping foot aggressively");
	}

	*/


	return (0);
}

int _strlen(char *str)
{
	int idx = 0;
	while(str[idx] != '\0')
	{
		idx++;
	}
	return idx;
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

