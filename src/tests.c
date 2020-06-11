#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "adev.h"
#include "tools.h"

int main (int argc, char **argv)
{
	const unsigned int N = 8192;
	float *x, **clusters;
	float *avar;
	unsigned int i, j;
	unsigned int index = 0;
	unsigned int n_clusters, clusters_size;
	float xn, xnp1;
	float acc;

	x = (float*)malloc(N*sizeof(float));
	
	avar = (float*)malloc(log2(N)*sizeof(float));

	clusters = (float**)malloc(N/2*sizeof(float)); // max. nb of cluster
	for (i=0; i<N/2; i++) // max nb. of cluster
	{
		clusters[i] = (float*)malloc(N*sizeof(float)); // largest cluster
	}

	randnf(x, N);
	array2csv("input.csv", x, N);

	index = 0;

	for (n_clusters=1; n_clusters < N/2; n_clusters *= 2)
	{
		clusters_size = N/n_clusters;
		split(x, clusters, n_clusters, clusters_size); 
		printf("n clusters: %d of size %d index %d\n", n_clusters, clusters_size, index);

		acc = 0.f;
		for (j=0; j<n_clusters-1; j++) 
		{
			printf("%d, ", j);
			xn   = mean(clusters[j], clusters_size); 
			xnp1 = mean(clusters[j+1], clusters_size); // adjacent cluster 
			acc += powf(xnp1-xn, 2);
		} printf("%d\n", n_clusters-1);

		acc /= (float)n_clusters;
		avar[index] = acc /2.0; 
		index++;
	}

	array2csv("output.csv", avar, log2(N/2)-1);
	return 0;
}
