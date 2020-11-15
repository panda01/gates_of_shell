#include "khalah_shell.h"


int main(int argc, char *argv[], char **env)
{
	int history_count = 0;
	int status;
	pid_t fork_pid;
	char *tokenized_input[MAX_ARGS];
	char *stdoutval = malloc(256);
	int char_count;

	if(stdoutval == NULL)
	{
		exit(1);
	}

	if(argc == 0)
	{
		exit(1);
	}

	do
	{
		if(isatty(STDIN_FILENO)) {
			promptuser(tokenized_input);
		} else {
			char_count = read(STDIN_FILENO, stdoutval, 256);
			if(char_count > 0)
			{
				getargs(tokenized_input, stdoutval, " ");
			} else {
				printf("error");
			}
		}

		if(_strsareequal(tokenized_input[0], "exit"))
		{
			exit(0);
		}

		history_count++;
		fork_pid = fork();
		if(fork_pid == -1)
		{
			perror("Error Forking");
			exit(1);
		}


		if(fork_pid == 0)
		{
			/* finally let's try and run it */
			handleinput(argv[0], tokenized_input, env, history_count);
		} else {
			wait(&status);
		}
	}
	while(isatty(STDIN_FILENO));

	return (0);
}
void promptuser(char **tokenized_input)
{
	size_t BUFF_SIZE = 256;
	char *buffer = malloc(BUFF_SIZE);
	char *PROMPT = "$ ";
	int char_input_count;

	write(1, PROMPT, _strlen(PROMPT));
	char_input_count = getline(&buffer, &BUFF_SIZE, stdin);
	if(char_input_count == -1)
	{
		printf("Bad input");
		exit(1);
	}

	/* let's split the arguments into an array */
	getargs(tokenized_input, buffer, " ");
}
void handleinput(char *command, char *tokenized_input[], char *environ[], int history_count)
{
	char *tokenized_paths[256] = {NULL};
	char *found_path = NULL;
	int idx;
	struct stat filestatus;
	char *path_vars;

	if(tokenized_input[0][0] == '/' || tokenized_input[0][0] == '.')
	{
		/* try and run a file */
		if(execve(tokenized_input[0], tokenized_input, NULL) == -1)
		{
			perror(_strmcat(4, "-", command, ": ", tokenized_input[0]));
		}
	} else if(_strsareequal(tokenized_input[0], "env")) {
		/* print the environment */
		for(idx = 0; environ[idx] != NULL; idx++)
		{
			printf("%s\n", environ[idx]);
		}
		exit(0);
	} else {
		/* otherwise it must be a command */
		/* try and run through the path and see if the command can be run */
		path_vars = _findkeyvalue("PATH", environ);
		getargs(tokenized_paths, path_vars, ":");

		idx = 0;

		while(tokenized_paths[idx] != NULL)
		{
			found_path = _strmcat(3, tokenized_paths[idx], "/", tokenized_input[0]);
			if(stat(found_path, &filestatus) == 0)
			{
				if(execve(found_path, tokenized_input, NULL) == -1)
				{
					perror(_strmcat(4, "-", command, ": ", tokenized_input[0]));
				}
			}
			idx++;
		}
		printf("%s: %d: %s: not found\n",command, history_count, tokenized_input[0]);
	}
}


void getargs(char *ret[], char *input, char *needle)
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

