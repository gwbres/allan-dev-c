#ifndef __TOOLS_H__
#define __TOOLS_H__

void randnf (float *x, unsigned int size);

void print_array (float *array, unsigned int size);
void print_clusters (float **array, unsigned int n_clusters, unsigned int size);
int array2csv (const char *fp, float *array, unsigned int size);

#endif
