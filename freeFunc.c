#include "main.h"


/**
 * freeCommandInfo - add descr
 * @shellInfo: add descr
 * @freeAll: add descr
 */
void freeCommandInfo(commandInfo *shellInfo, int freeAll)
{
	stringFree(shellInfo->command_arguments);
	shellInfo->command_arguments = NULL;

	shellInfo->executable_path = NULL;

	if (freeAll)
	{
		if (!shellInfo->command_buffer)
			free(shellInfo->current_argument);

		if (shellInfo->environment_variables)
			freeList(&(shellInfo->environment_variables));

		if (shellInfo->command_history)
			freeList(&(shellInfo->command_history));

		if (shellInfo->alias_list)
			freeList(&(shellInfo->alias_list));

		stringFree(shellInfo->environment);
		shellInfo->environment = NULL;

		buffFree((void **)shellInfo->command_buffer);

		if (shellInfo->input_file_descriptor > 2)
			close(shellInfo->input_file_descriptor);

		_putchar(FLUSH_BUFFER);
	}
}


/**
 * stringFree - add descr
 * @pp: add descr
 */
void stringFree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * buffFree - add descr
 * @ptr: add descr
 * Return: add descr
 */
int buffFree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


/**
 * freeList - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void freeList(listNode **head_ptr)
{
	listNode *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->value);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
