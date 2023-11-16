#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <errno.h>

#include <string.h>
#include <fcntl.h>

#include <sys/stat.h>

#include <signal.h>

#define BUF_SIZE 1024
#define FLUSH_BUFFER -1


#define CD_OR		1
#define CD_AND		2
#define CD_CH	3

extern char **environ;


/**
 * struct Node - singly linked list node
 * @index: numerical index or identifier
 * @value: string value
 * @next: points to the next node
 */
typedef struct Node
{
	int index;
	char *value;
	struct Node *next;
} listNode;


/**
 * struct pseudoArgs- contains pseudo-arguements to pass into a function,
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


/**
 * struct BuiltInCommand - Represents a built-in shell command
 * @name: The name of the built-in command.
 * @CommandFunction: A function pointer to handle the command.
 */
typedef struct BuiltInCommand
{
	const char *name;
	int (*CommandFunction)(commandInfo *);
} commandStruct;

/*initialize commandInfo values to NULL for pointers & 0 for others*/
#define COMMAND_INFO_INIT \
{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
		0, 0, 0, 0, 0, 0, 0, 0, 0}

int runShell(commandInfo *shellInfo, char **argv);
int main(int argc, char **argv);

int print_str(const char *format, ...);
int _putchar(char c);
char *charDup(char *pathstr, int start, int stop);

void print_error(commandInfo *shellInfo, char *errorStr);
int print_error_char(char character);
int _fprintf(int fd, const char *format, ...);
void errorPuts(char *str);
int custPrint(int input, int fd);
int _eputchar(char c);

listNode *addNodeEnd(listNode **head, const char *str, int num);

int populateEnvironmentList(commandInfo *shellInfo);
char *retEnv(commandInfo *shellInfo, const char *name);
char **retEnviron(commandInfo *shellInfo);

char *findPath(commandInfo *shellInfo, char *pathstr, char *cmd);
void executeExternalCmd(commandInfo *shellInfo);

char *_strdup(const char *str);
int _strlen(char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *string_concatenate(char *destination, char *source);
char *string_starts_with(const char *haystack, const char *needle);

char *_memset(char *s, char b, unsigned int n);

void clearCommandInfo(commandInfo *shellInfo);
void setInfo(commandInfo *shellInfo, char **argv);

ssize_t getInput(commandInfo *shellInfo);
int findBuiltinCmd(commandInfo *shellInfo);

int exitCommand(commandInfo *shellInfo);
int envCommand(commandInfo *shellInfo);
int cdCommand(commandInfo *shellInfo);

char *_strtok(char *str, const char *delim);
char *_strpbrk(char *s, const char *accept);
size_t _strspn(const char *s, const char *accept);
int checkDelim(char c, char *delim);
char **strtow(char *str, char *d);

int fdWrite(char c, int fd);
int fdWrites(char *str, int fd);

int checkReg(const char *path);
int isCmd(commandInfo *shellInfo, char *path);

int replaceAlias(commandInfo *shellInfo);
void replaceVars(commandInfo *shellInfo);
char *findReplacementValue(commandInfo *shellInfo, const char *variable);
void replaceVars(commandInfo *shellInfo);
char *stCr(char *s, char c);

char *itoa1(long int num, int base, int flags);

void rmStringComment(char *buffer);
void sigintHandler(__attribute__((unused)) int sig_num);
ssize_t inputBuf(commandInfo *shellInfo, char **buf, size_t *bufferLen);

int isChn(commandInfo *shellInfo, char *buf, size_t *p);
void chkChain(commandInfo *shellInfo, char *buf, size_t *p
, size_t i, size_t len);
int getLine(commandInfo *shellInfo, char **ptr, size_t *length);

char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);


ssize_t readBuffer(commandInfo *shellInfo, char *buf, size_t *i);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

void fkCommand(commandInfo *shellInfo);
char **toStrFrmList(listNode *head);

size_t listLength(const listNode *h);
char *stringCopy(char *destination, const char *source);

void freeCommandInfo(commandInfo *shellInfo, int all);

int buffFree(void **ptr);
void stringFree(char **pp);
void freeList(listNode **head_ptr);

#endif /*main.h*/
