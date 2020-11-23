#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "khalah_shell.h"

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	int status;
	int num_chars_typed;
	size_t MAX_INPUT_CHARS = 256;
	char *user_raw_input = malloc(MAX_INPUT_CHARS);
	char *alltheargs[2] = {NULL, NULL};
	char *clean_input = malloc(MAX_INPUT_CHARS);
	pid_t fork_id;


	do {

		num_chars_typed = getline(&user_raw_input, &MAX_INPUT_CHARS, stdin);
		clean_input = _strremovechar(user_raw_input, '\n');


		alltheargs[0] = clean_input;

		fork_id = fork();
		if(fork_id == 0)
		{
			if (execve(alltheargs[0], alltheargs, NULL) == -1)
			{
				perror("command not found");
			}
		}

		wait(&status);

	} while (1);

	/*
	int status;
	pid_t fork_id;
	printf("before execve\n");
	char *alltheargs[] = {"/bin/ls", NULL};

	printf("before fork\n");
	fork_id = fork();
	printf("after fork\n");
	/* are we in the child process??? */
	/*
	if(fork_id == 0)
	{
		execve(alltheargs[0], alltheargs, NULL);
	}
	printf("before wait\n");
	wait(&status);
	printf("after execve\n");
	/*

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
	/*
	char *alltheargs[] = {clean_input, NULL};
	execve(alltheargs[0], alltheargs, NULL);


	free(user_raw_input);
	free(clean_input);


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
