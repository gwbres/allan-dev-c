#include <stdlib.h>
#include <stdio.h>
#include "tools.h"

void print_array (float *array, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size-1; i++)
	{
		printf("%f, ", array[i]);
	} 
	printf("%f\n", array[size-1]);
}

void print_clusters (float **array, unsigned int n_clusters, unsigned int size)
{
	unsigned int i, j;
	for (i=0; i<n_clusters; i++)
	{
		for (j=0; j<size-1; j++)
		{
			printf("%f, ", array[i][j]);
		} 
		printf("%f\n", array[i][size-1]);
	}
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
		fprintf(fd, "%.6e,",array[i]);
	}
	fprintf(fd, "%.6e", array[i]);

	fclose(fd);
	return 0;
}

void randnf (float *x, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size; i++)
	{
		x[i] = (float)rand()/RAND_MAX; 
	}
}
