#include "tools.h"
#include <stdio.h>

void print_array (float *array, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size-1; i++)
	{
		printf("%f, ", array[i]);
	} 
	printf("%f\n", array[size-1]);
}

int array2csv (const char *fp, float *array, unsigned int size)
{
	FILE *fd;
	unsigned int i;

	fd = fopen(fp, "w");
	if (fd == NULL)
	{
		return -1;
	}

	for (i=0; i<size; i++)
	{
		fprintf(fd, "%f,",array[i]);
	}
	fprintf(fd, "%f", array[i]);

	fclose(fd);
	return 0;
}
