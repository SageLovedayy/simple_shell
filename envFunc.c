#include "main.h"

/*=====ENVIRONMENT LIST FUNCTIONS===========*/

/**
 * populateEnvironmentList - create linked list of environment variables
 * @shellInfo: add descr
 * Return: Always 0
*/
int populateEnvironmentList(commandInfo *shellInfo)
{
	listNode *node = NULL;
	listNode *current;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);

	shellInfo->environment_variables = node;

	current = shellInfo->environment_variables;

	while (current) { /*Just a test to check env print. Do not forget to take out this while block*/
		printf("Debug inside loop\n");
		printf("Environment variables: %s\n", current->value ? current->value : "(nil)");
		current = current->next;
	}

	return (0);
}

/**
 * addNodeEnd - add node to end of linked list
 * @head: add descr
 * @str: add descr
 * @num: add descr
 * Return: new node
*/
listNode *addNodeEnd(listNode **head, const char *str, int num)
{
	listNode *newNode, *node;

	if (!head || !(*head))
		return (NULL);

	node = *head;

	newNode = malloc(sizeof(listNode));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(listNode));
	newNode->index = num;
	newNode->next = NULL;

	if (str)
	{
		newNode->value = _strdup(str);
		if (!newNode->value)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}
