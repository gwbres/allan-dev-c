#ifndef __ADEV_H__
#define __ADEV_H__

/*
	splits *x into **y:
	n clusters of cluster_size=n_cluster/size size;
	returns cluster_size
*/
void split (float *x, float **y, unsigned int n_clust, unsigned int clust_size);

void randnf (float *x, unsigned int size);

/*
	computes statistic mean of data set
*/
float mean (float *x, unsigned int size);

/*
	AVAR
*/
float avar (float **x, unsigned int size, unsigned int clust_size);

/*
	ADEV.
*/
float adev (float *x, int size, int *tau, int n_cluster);

#endif
