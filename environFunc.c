#include "main.h"

/*=====================================================*/
/*ENVIRONMENT LIST FUNCTIONS*/

/**
 * populateEnvironmentList - add descr
 * @shellInfo: add descr
 * Return: Always 0
 */
int populateEnvironmentList(commandInfo *shellInfo)
{
	listNode *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	shellInfo->environment_variables = node;
	return (0);
}

/**
 * retEnv - add descr
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * @name: env var name
 * Return: add descr
 */
char *retEnv(commandInfo *shellInfo, const char *name)
{
	listNode *node = shellInfo->environment_variables;
	char *p;

	while (node)
	{
		p = string_starts_with(node->value, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/*========================================================*/
/*LINKED LIST FUNCTIONS*/

/**
 * addNodeEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
listNode *addNodeEnd(listNode **head, const char *str, int num)
{
	listNode *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(listNode));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(listNode));
	new_node->index = num;
	if (str)
	{
		new_node->value = _strdup(str);
		if (!new_node->value)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
