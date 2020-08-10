#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <adev.h>

void split (
	float *x, float **y, unsigned int n_cluster, unsigned int size
){
	unsigned int i, j;
	for (i=0; i<n_cluster; i++)
	{
		for (j=0; j<size; j++)
		{
			y[i][j] = x[i*size+j];
		}
	}

}

float mean (float *x, unsigned int size)
{
	unsigned int i;
	float acc = 0.f;
	for (i=0; i<size; i++)
	{
		acc += x[i];
	}
	return acc / (float)size;
}

float stdvar (float *x, unsigned int size)
{
	unsigned int i;
	float m = mean(x, size);
	float acc = 0.f;
	for (i=0; i<size; i++)
	{
		acc += powf(x[i] - m, 2);
	}
	return acc / (float)size;
}

float stddev (float *x, unsigned int size)
{
	return sqrtf(stdvar(x,size));
}

float avar_calc (float **x, 
		unsigned int n_clusters, 
		unsigned int clust_size,
		uint8_t is_fractionnal
){
	int i, max;
	float acc;
	float xn, xnp1; //xnp2;

	//if (is_fractionnal)
	//	max = n_clusters-2;
	//else
		max = n_clusters-1;
	
	acc = 0.f;
	for (i=0; i<max; i++) 
	{
	//	if (is_fractionnal)
	//		xnp2 = mean(x[i+2], clust_size);
		
		//xnp1 = mean(x[i+1], clust_size);
		//xn   = mean(x[i],	  clust_size);

	//	if (is_fractionnal)
	//		acc += powf(xnp2  -2*xnp1 + xn, 2);
	//	else
			acc += powf(x[i+1] - x[i], 2);
	}

	//if (is_fractionnal)
	//	return acc /((float)max+1.0) /(float)n_clusters /2.0;
	//else
		return acc /(float)n_clusters /2.0;
}

void avar (float *x, float *y, unsigned int size, uint8_t is_fractionnal) 
{
	unsigned int n_clusters, clusters_size;
	float **clusters;
	
	// y[k] index
	// starts from last tau offset and decrement to index=0
	// only works for power of 2 axis
	unsigned int index = (int)log2(size/2)+1; 

	clusters = (float**)malloc(size*size*sizeof(float)); // max. nb of clusters
	for (n_clusters=0; n_clusters < size; n_clusters++)
	{
		// max. cluster size
		clusters[n_clusters] = (float*)malloc(size*sizeof(float)); 
	}
	
	y[0] = stdvar(x, size); // 1st tau offset is always std var
	
	// populate other tau offsets
	// starting from largest value (=log2(n/2)+1)
	// to smallest value (=1)
	for (n_clusters=1; n_clusters <= size/2; n_clusters *= 2)
	{
		clusters_size = size / n_clusters;
		split(x, clusters, n_clusters, clusters_size);
		y[index] = avar_calc(clusters, n_clusters, clusters_size, is_fractionnal);
		index--;
	}

	// free work structs
	for (n_clusters=0; n_clusters < size; n_clusters++)
		free(clusters[n_clusters]);

	free(clusters);
}

void adev (float *x, float *y, unsigned int size, uint8_t is_fractionnal)
{
	unsigned i;
	avar (x, y, size, is_fractionnal);
	for (i=0; i < size/2; i *= 2)
		y[i] = sqrtf(y[i]);
}
