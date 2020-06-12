#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "adev.h"

void tau_axis_pow2 (int *x, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size; i++)
	{
		x[i] = (int)roundf(powf(2,i));
	}
}

void tau_axis_pow10 (int *x, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size; i++)
	{
		x[i] = (int)roundf(powf(10,i));
	}
}

void tau_axis (int *x, unsigned size, uint8_t is_pow)
{
	unsigned int i;
	if (is_pow & POWER2_TAU_AXIS)
		tau_axis_pow2(x, size);

	else if (is_pow & POWER10_TAU_AXIS)
		tau_axis_pow10(x, size);
	
	else {
		for (i=0; i<size; i++)
			x[i] = i;
	}
}

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
		acc += powf(x[i] - m,2);
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
	float xn, xnp1, xnp2;

	if (is_fractionnal)
		max = n_clusters-2;
	else
		max = n_clusters-1;
	
	acc = 0.f;
	for (i=0; i<max; i++) 
	{
		if (is_fractionnal)
		xnp2 = mean(x[i+2], clust_size);
		xnp1 = mean(x[i+1], clust_size);
		xn   = mean(x[i],	  clust_size);

		if (is_fractionnal)
			acc += powf(xnp2  -2*xnp1 + xn, 2);
		else
			acc += powf(xnp1 - xn, 2);
	}

	if (is_fractionnal)
		return acc /2.0 /((float)max+1.0) /(float)n_clusters;
	else
		return acc /(float)n_clusters /2.0;
}

void avar_tau_pow2 (float *x, float *y, unsigned int size, uint8_t is_fractionnal) 
{
	unsigned int n_clusters, clusters_size;
	unsigned int index = (int)log2(size/2)+1; // last tau offset

	float **clusters;

	clusters = (float**)malloc(size*size*sizeof(float)); // max. nb of clusters
	for (n_clusters=0; n_clusters < size; n_clusters++)
	{
		// max. cluster size
		clusters[n_clusters] = (float*)malloc(size*sizeof(float)); 
	}

	for (n_clusters=1; n_clusters <= size/2; n_clusters *= 2)
	{
		clusters_size = size / n_clusters;
		split(x, clusters, n_clusters, clusters_size);
		y[index] = avar_calc(clusters, n_clusters, clusters_size, is_fractionnal);
		index--;
	}

	y[0] = stdvar(x, size); // 1st tau offset is always std var
	
	for (n_clusters=0; n_clusters < size; n_clusters++)
		free(clusters[n_clusters]);
	free(clusters);
}

void adev_tau_pow2 (float *x, float *y, unsigned int size, uint8_t is_fractionnal)
{
	unsigned int i;
	avar_tau_pow2(x, y, size, is_fractionnal);
	for (i=0; i<size; i++)
		y[i] = sqrtf(y[i]);
}
