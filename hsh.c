#include "hsh.h"


/**
 * main - run our shell!!!
 * @argc: the arguments count
 * @argv: the arguments passed in
 * @env: the environment variables
 * Return: depends, but it does the thing
 */
int main(int argc, char *argv[], char **env)
{
	int history_count = 0;
	int status;
	pid_t fork_pid;
	char *tokenized_input[MAX_ARGS];
	char *stdoutval = malloc(256);
	int char_count;

	if (argc == 0)
		exit(1);

	do {
		if (isatty(STDIN_FILENO))
			promptuser(tokenized_input);
		if (!isatty(STDIN_FILENO))
		{
			char_count = read(STDIN_FILENO, stdoutval, 256);
			if (char_count > 0)
				tokenize_str(tokenized_input, stdoutval, " ");
		}

		if (_strsareequal(tokenized_input[0], "exit"))
			exit(0);

		history_count++;
		fork_pid = fork();
		if (fork_pid == -1)
		{
			exit(1);
		}


		if (fork_pid == 0)
			handleinput(argv[0], tokenized_input, env, history_count);
		else
			wait(&status);
	} while (isatty(STDIN_FILENO));

	return (0);
}
/**
 * promptuser - Prompt the user for input!
 * @tokenized_input: the char** to place the tokenized input
 */
void promptuser(char **tokenized_input)
{
	size_t BUFF_SIZE = 256;
	char *buffer = malloc(BUFF_SIZE);
	char *PROMPT = "$ ";
	int char_input_count;

	write(1, PROMPT, _strlen(PROMPT));
	char_input_count = read(STDIN_FILENO, buffer, BUFF_SIZE);
	if (char_input_count == -1)
	{
		printf("Bad input");
		exit(1);
	}

	/* let's split the arguments into an array */
	tokenize_str(tokenized_input, buffer, " ");
}

/**
 * handleinput - Take the commands and environ and act on it!
 * @command: The command entered to run this shell
 * @input: A tokenized array of the user input
 * @environ: the environment variables
 * @h_count: the history count so far
 */
void handleinput(char *command, char *input[], char *environ[], int h_count)
{
	char *tokenized_paths[256] = {NULL};
	char *found_path = NULL;
	int idx = 0;
	struct stat filestatus;
	char *path_vars;

	if (input[0][0] == '/' || input[0][0] == '.')
	{
		if (execve(input[0], input, environ) == -1)
			perror(_strmcat(4, "-", command, ": ", input[0]));
	}
	if (_strsareequal(input[0], "env"))
	{
		for (idx = 0; environ[idx] != NULL; idx++)
		{
			printf("%s\n", environ[idx]);
		}
		exit(0);
	}

	/* otherwise it must be a command */
	/* try and run through the path and see if the command can be run */
	path_vars = _findkeyvalue("PATH", environ);
	tokenize_str(tokenized_paths, path_vars, ":");

	while (tokenized_paths[idx] != NULL)
	{
		
		found_path = _strmcat(3, tokenized_paths[idx], "/", input[0]);
		if (stat(found_path, &filestatus) == 0) /* file found!! */
			if (execve(found_path, input, environ) == -1)
				perror(_strmcat(4, "-", command, ": ", input[0]));
		idx++;
	}
	printf("%s: %d: %s: not found\n", command, h_count, input[0]);
}


/**
 * tokenize_str - takes a string and splits it on some char into and array
 * @ret: The place to put the tokenized strings
 * @input: the string to tokenize
 * @needle: the char we split the string on
 */
void tokenize_str(char *ret[], char *input, char *needle)
{
	char *token;
	int idx;

	idx = 0;
	while (idx < MAX_ARGS)
	{
		ret[idx] = NULL;
		idx++;
	}

	token = strtok(input, needle);
	ret[0] = _strremovechar(token, '\n');

	token = strtok(NULL, needle);
	idx = 1;
	while (token != NULL)
	{
		ret[idx] = _strremovechar(token, '\n');
		token = strtok(NULL, needle);
		idx++;
	}
}

