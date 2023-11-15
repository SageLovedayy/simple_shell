#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

#include <stdbool.h>
#include <errno.h>

#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include <string.h>

#define BUF_SIZE 1024
#define FLUSH_BUFFER -1
#define CUSTOM_FD_OFFSET 9 /*For adjusting fd offset*/

extern char **environ;

/**
* struct Node - singly linked list node
* @index: numerical index/ identifier
* @value: string value
* @next: pointer to next node
*/
typedef struct Node
{
	int index;
	char *value;
	struct Node *next;
} listNode;

/**
* struct pseudoArgs - struct of pseudo arguments to pass into a function
* @current_argument: add descr
* @command_arguments: add descr
* @executable_path: add descr
* @argument_count: add descr
* @current_line_number: add descr
* @error_number: add descr
* @line_count_flag: add descr
* @file_name: add descr
* @environment_variables: add descr
* @environment: add descr
* @command_history: add descr
* @alias_list: add descr
* @environment_changed_flag: add descr
* @commandExecStatus: add descr
* @command_buffer: add descr
* @command_buffer_type: add descr
* @input_file_descriptor: add descr
* @history_count: add descr
*/
typedef struct pseudoArgs
{
	char *current_argument;
	char **command_arguments;
	char *executable_path;
	char *file_name;
	listNode *environment_variables;
	listNode *command_history;
	listNode *alias_list;
	char **environment;
	char **command_buffer;
	int argument_count;
	unsigned int current_line_number;
	int error_number;
	int line_count_flag;
	int environment_changed_flag;
	int commandExecStatus;
	int command_buffer_type;
	int input_file_descriptor;
	int history_count;
} commandInfo;

/*Init commandInfo pseudoArg vals to NULL for ptrs, 0 for other data types*/
#define COMMAND_INFO_INIT \
{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
		0, 0, 0, 0, 0, 0, 0, 0, 0}


/**
 * struct BuiltInCommand - Represents a built-in shell command
 * @name: The name of the built-in command.
 * @CommandFunction: A function pointer to handle the command.
 */
typedef struct BuiltInCommand
{
	/* Name of the built-in command */
	const char *name;
	/* Function pointer for handling the command */
	int (*CommandFunction)(commandInfo *);
} commandStruct;

/*=========ENTRY FUNCTION===================*/
int main(int argc, char **argv);
int runShell(commandInfo *shellInfo, char **argv);

/*==========WRITE FUNCTIONS=================*/
int _fprintf(int fd, const char *format, ...);
int print_str(const char *format, ...);
int _putchar(char c);
/*===========ERROR WRITE FUNCTIONS=========*/
int print_error_char(char character);

/*===========UTILITY FUNCTIONS==============*/
char *_strdup(const char *str);
int _strlen(char *s);

/*=========ENVIRONMENT LIST FUNCTIONS=======*/
int populateEnvironmentList(commandInfo *shellInfo);

/*=========LINKED LIST FUNCTIONS============*/
listNode *addNodeEnd(listNode **head, const char *str, int num);

/*=========MEMORY AND REALLOC================*/
char *_memset(char *dest, char byteVal, unsigned int numBytes);


/*=================================================================*/


char *argChecker(int argc, char *cmd);
bool flagChecker(const char *token);

void executeLS(int argc, char *argv[]);
void executeCD(int argc, char *argv[]);
void handleEnvCommand(int argc, char *argv[]);
char *_strtok(char *str, const char *delim);

int print_str(const char *format, ...);
char *_strpbrk(char *s, const char *accept);
int _strcmp(const char *s1, const char *s2);
size_t _strspn(const char *s, const char *accept);
int _strncmp(const char *s1, const char *s2, int n);
int _atoi(char *s);

#endif /* _MAIN_H_ */
