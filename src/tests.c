#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "adev.h"
#include "tools.h"

int main (int argc, char **argv)
{
	float *x, **clusters;
	float *avar;
	unsigned int i, j;
	unsigned int tau;
	float xn, xnp1;
	float acc;

	x = (float*)malloc(128*sizeof(float));
	avar = (float*)malloc(128*sizeof(float));

	clusters = (float**)malloc(128*128*sizeof(float));
	for (i=0; i<128; i++){
		clusters[i] = (float*)malloc(128*sizeof(float));
	}

	randnf(x, 128);
	array2csv("input.csv", x, 128);

	/*  AVAR              */
	// tau >= 1
	for (tau=1; tau<128; tau++) // n_cluster 
	{
		split(x, clusters, tau, 128/tau);
		acc = 0.f;
		for (j=0; j<128/tau-1; j++) // clust_size: j+1 must exist!
		{
			xn = mean(clusters[j], 128/tau);
			xnp1 = mean(clusters[j+1], 128/tau);
			acc += powf(xnp1-xn, 2);
		}

		acc /= (float)tau;
		avar[tau] = 0.5 * acc;
	}

	array2csv("output.csv", avar, 128);

	return 0;
}
