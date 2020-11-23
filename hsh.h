#ifndef KHALAH
#define KHALAH

#define MAX_ARGS 8

#include "utils/str_utils.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


void promptuser(char **tokenized_input);
void handleinput(char *command, char *tokenized_input[], char *environ[], int history_count);
void tokenize_str(char *ret[], char *input, char *needle);


#endif
