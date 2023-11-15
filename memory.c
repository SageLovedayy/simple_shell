#include "main.h"

/**
 * _memset - fills memory with a constant byte
 * @dest: descr
 * @byteVal: descr
 * @numBytes: descr
 * Return: pointer dest to memory housing dest
 */
char *_memset(char *dest, char byteVal, unsigned int numBytes)
{
	unsigned int i;

	for (i = 0; i < numBytes; i++)
		dest[i] = byteVal;

	return (dest);
}
