#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdbool.h>

#include <string.h>

#define BUF_SIZE 1024

extern char **environ;

/**
 * struct BuiltInCommand - Represents a built-in shell command
 * @name: The name of the built-in command.
 * @CommandFunction: A function pointer to handle the command.
 */
struct BuiltInCommand
{
	/* Name of the built-in command */
	const char *name;
	/* Function pointer for handling the command */
	void (*CommandFunction)(int argc, char *argv[]);
};
typedef struct BuiltInCommand commandStruct;

char *argChecker(int argc, char *cmd);
bool flagChecker(const char *token);

void executeLS(int argc, char *argv[]);
void executeCD(int argc, char *argv[]);
void handleEnvCommand(int argc, char *argv[]);
char *_strtok(char *str, const char *delim);

int print_str(const char *format, ...);
size_t _strlen(const char *s);
char *_strpbrk(char *s, const char *accept);
int _strcmp(const char *s1, const char *s2);
size_t _strspn(const char *s, const char *accept);
int _strncmp(const char *s1, const char *s2, int n);
int _atoi(char *s);

#endif /* _MAIN_H_ */
