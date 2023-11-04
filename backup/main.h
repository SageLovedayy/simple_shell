#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>

#define BUF_SIZE 1024

typedef void (*CommandFunction)(int argc, char *argv[]);

typedef struct
{
	/* Name of the built-in command */
	const char *name;
	/* Function pointer for handling the command */
	CommandFunction func;
} BuiltInCommand;

void argChecker(int argc, char *cmd);
char *flagChecker(char **args);

void executeLS(int argc, char *argv[]);
void handleEnvCommand(int argc, char *argv[]);

size_t print_str(const char *str);
size_t _strlen(const char *s);
char *_strpbrk(char *s, const char *accept);
char *_strtok(char *str, const char *delim);
int _strcmp(char *s1, const char *s2);

#endif /* _MAIN_H_ */