#include <math.h>
#include <stdlib.h>
#include "adev.h"

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
		acc += x[i];
	return acc / size;
}

void randnf (float *x, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size; i++)
	{
		x[i] = (float)rand()/RAND_MAX; 
	}
}

float avar (float **x, unsigned int size, unsigned int clust_size)
{
	// to get the variance v(tau) for a given tau
	//  compute mean of cluster & adjacent cluster
	//  compute difference^2
	//  avarage for all cluster of idnetical size
	unsigned int i;
	unsigned int n_clusters = size/clust_size;
	float acc, xn, xnp1;

	acc = 0.f;
	for (i=0; i<n_clusters-1; i++) // n_clusters+1!
	{
		xnp1 = mean(x[n_clusters+1], clust_size);
		xn = mean(x[n_clusters], clust_size);
		acc += powf(xnp1 - xn,2);
	}
	acc = acc / (float)n_clusters;
	
	return 0.5*acc;
}

float adev (float *data, int size, int *tau, int n_cluster)
{
//	return sqrtf(avar(data,size,tau,n_cluster));
	return 0.f;
}
