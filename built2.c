#include "main.h"

/*===========================================================*/
/*FORK CMD*/

/**
 * fkCommand - forks a an exec thread to run cmd
 * @shellInfo: add descr
 *
 * Return: void
 */
void fkCommand(commandInfo *shellInfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shellInfo->executable_path, shellInfo->command_arguments
		, retEnviron(shellInfo)) == -1)
		{
			freeCommandInfo(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(shellInfo->commandExecStatus));
		if (WIFEXITED(shellInfo->commandExecStatus))
		{
			shellInfo->commandExecStatus = WEXITSTATUS(shellInfo->commandExecStatus);
			if (shellInfo->commandExecStatus == 126)
				print_error(shellInfo, "Permission denied\n");
		}
	}
}

/**
 * retEnviron - add descr
 * @shellInfo: add descr
 * Return: Always 0
 */
char **retEnviron(commandInfo *shellInfo)
{
	if (!shellInfo->environment || shellInfo->environment_changed_flag)
	{
		shellInfo->environment = toStrFrmList(shellInfo->environment_variables);
		shellInfo->environment_changed_flag = 0;
	}

	return (shellInfo->environment);
}



/**
 * toStrFrmList - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **toStrFrmList(listNode *head)
{
	listNode *node = head;
	size_t i = listLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->value) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = stringCopy(str, node->value);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/*==================linked list func*/
/**
 * listLength - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t listLength(const listNode *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
